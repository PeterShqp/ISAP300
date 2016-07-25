/*
 * Chip8STM1CPLD.cpp
 *
 *  Created on: 2014-5-16
 *      Author: Administrator
 */

#include "Chip8STM1CPLD.h"
#include "RegisterAccess.h"
#include <iostream>
#include "s1l_line_input.h"
#include "CBaseSlot.h"
#include <stdio.h>
#include "os.h"
#include "CPPTools.h"
#include "GeneralLogic.h"

static const std::string chipName = "STM8CPLD";

const char stmlgc1Fname[] = "stmlogic1.bit";
const char stmlgc2Fname[] = "stmlogic2.bit";

extern char fileBuf[340736];

Chip8STM1CPLD::Chip8STM1CPLD(CBaseSlot* slt) :
		BaseChip(chipName) {
	regAccess = slt->getRegisterAccess();

}

Chip8STM1CPLD::~Chip8STM1CPLD() {
	// TODO Auto-generated destructor stub
}

Chip_INIT_RESULT Chip8STM1CPLD::updataTwoFPGA(bool force, const char* fpga1Fname,
		const char* fpga2Fname) {
    if( !GeneralLogic::instance().ifColdStart() ) {
        if ( ifSucceed()) {
            std::cout << "FPGAs have been running" << std::endl;
            display_prompt();
            return donothing;
        }
    }
	FILE* fpga1 = 0;
	FILE* fpga2 = 0;
	if (fpga1Fname) {
		fpga1 = fopen(fpga1Fname, "rb");
	} else {
		fpga1 = fopen(stmlgc1Fname, "rb");
	}
	if (fpga2Fname) {
		fpga2 = fopen(fpga2Fname, "rb");
	} else {
		fpga2 = fopen(stmlgc2Fname, "rb");
	}

	if (!fpga1 && !fpga2) {
		std::cout << "!!!No update file exist!!!" << std::endl;
	} else if (!fpga1) {
		fclose(fpga2);
		std::cout << "!!!No stmlogic1 upload file exist!!!" << std::endl;
	} else if (!fpga2) {
		fclose(fpga1);
		std::cout << "!!!No stmlogic2 upload file exist!!!" << std::endl;
	} else { //all file is ok
		if (prepareUpdata()) {
			uint32 readCount = 0;

			std::cout << "Loading stmlogic1 first." << std::endl;
			readCount = fread(fileBuf, 1, sizeof(fileBuf), fpga1);
			fclose(fpga1);

			if (readCount > 0) {
				for (int i = 0; i < sizeof(fileBuf); i += 2) {
					regAccess->writeReg(REG_LOAD_BUF_STMLGC1,
							(fileBuf[i] << 8) | fileBuf[i + 1], 0);
				}
			}
			std::cout << std::endl;

			std::cout << "Loading stmlogic2 second." << std::endl;
//			tsk_lock();
			readCount = fread(fileBuf, 1, sizeof(fileBuf), fpga2);
//			tsk_unlock();
			fclose(fpga2);

			if (readCount > 0) {
				for (int i = 0; i < sizeof(fileBuf); i += 2) {
					regAccess->writeReg(REG_LOAD_BUF_STMLGC2,
							(fileBuf[i] << 8) | fileBuf[i + 1], 0);
				}
			}

			std::cout << std::endl;
			bool rtn = ifSucceed();
			if (rtn) {
				std::cout << "update FPGAs succeed!" << std::endl;
	            display_prompt();
	            return succeed;
			} else {
				std::cout << "!!!update FPGAs failed!!!" << std::endl;
			}
			display_prompt();
		} else {
			std::cout << "!!!Prog & init PINs error.!!!" << std::endl;

		}

	}
	return failed;
}

bool Chip8STM1CPLD::prepareUpdata(void) {
	/* program pin pull down */
	uint16 regData = regAccess->readReg(REG_LOAD_OPTION);
	regData &= ~0x7f;
	regAccess->writeReg(REG_LOAD_OPTION, regData);

	/* delay 10ms */
	os_dly_wait(1);

	/* check if INIT is low */
	regData = regAccess->readReg(REG_LOAD_OPTION);
	if ((regData & 6) != 0) {
		return false;
	}

	/* program pin pull up */
	regData = regAccess->readReg(REG_LOAD_OPTION);
	regData |= 1;
	regAccess->writeReg(REG_LOAD_OPTION, regData);

	/* delay 10ms */
	os_dly_wait(1);

	/* check if INIT is high */
	regData = regAccess->readReg(REG_LOAD_OPTION);
	if ((regData & 6) != 6) {
		return false;
	}

	/* enter load mode */
	regData &= ~(1 << 15);
	regAccess->writeReg(REG_LOAD_OPTION, regData);

	return true;

}

bool Chip8STM1CPLD::ifSucceed(void) {
	/* exit load mode */
	uint16 regData = regAccess->readReg(REG_LOAD_OPTION);
	regData |= (1 << 15);
	regAccess->writeReg(REG_LOAD_OPTION, regData);

	/* check if DONE is HIGH */
	regData = regAccess->readReg(REG_LOAD_OPTION);
	if ((regData & 0x18) != 0x18) {
		return false;
	}
	return true;
}

Chip_INIT_RESULT Chip8STM1CPLD::ChipInit(void) {
	disableDCC();
    Chip_INIT_RESULT r = updataTwoFPGA();
    if( r != donothing ) {
        resetRC7883();
    }
	return r;
}

void Chip8STM1CPLD::resetRC7883() {
	regAccess->writeReg(REG_RST_RC7883, 0);
	os_dly_wait(1);
	regAccess->writeReg(REG_RST_RC7883, 0xf);
	os_dly_wait(2);
}

void Chip8STM1CPLD::enableDCC(void) {
	regAccess->writeReg(REG_DCC_INTR_EN, 0xE000);
}

void Chip8STM1CPLD::disableDCC(void) {
	regAccess->writeReg(REG_DCC_INTR_EN, 0);
}

void Chip8STM1CPLD::portLEDAlarmOn(uint8 ch, bool sel) {
	uint16 PortLedPosition;
	PortLedPosition = regAccess->readReg(REG_LED_2);
	if (!sel) {
		PortLedPosition |= (1 << ch);
		regAccess->writeReg(REG_LED_2, PortLedPosition, 0);
	} else {
		PortLedPosition &= ~(1 << ch);
		regAccess->writeReg(REG_LED_2, PortLedPosition, 0);
	}

}
std::string Chip8STM1CPLD::GetChipVerInfo(const std::string ChipName,
		const uint16 Reg_Ver_Addr) {
	ChipVerInfo = ChipName + "V"
			+ CPPTools::number2string(
					regAccess->readReg(Reg_Ver_Addr) >> 12 & 0xf) + "."
			+ CPPTools::number2string(
					regAccess->readReg(Reg_Ver_Addr) >> 8 & 0x7) + "."
			+ CPPTools::number2string(regAccess->readReg(Reg_Ver_Addr) & 0xff);
	return ChipVerInfo;
}
std::string  Chip8STM1CPLD::GetVerInfo(){
	return 	(GetChipVerInfo("PCB:",REG_VER_CPLD)).erase(8,2)+","+\
    		GetChipVerInfo("CPLD:",REG_VER_CPLD)+","+\
    		GetChipVerInfo("FPGA-1:",REG_VER_CPLD_STMLOGIC_1)+","+\
    		GetChipVerInfo("FPGA-2:",REG_VER_CPLD_STMLOGIC_2);
}
