/*
 * Chip8EOSCPLD.cpp
 *
 *  Created on: 2014-5-23
 *      Author: Administrator
 */

#include "Chip8EOSCPLD.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "os.h"
#include "CPPTools.h"

static const std::string chipName = "EOS8CPLD";

Chip8EOSCPLD::Chip8EOSCPLD(CBaseSlot* slt) :
		BaseChip(chipName) {

	ra = slt->getRegisterAccess();
}

Chip8EOSCPLD::~Chip8EOSCPLD() {
	// TODO Auto-generated destructor stub
}

Chip_INIT_RESULT Chip8EOSCPLD::ChipInit(void) {

//	for (int i = 0; i < 8; ++i) {
//		uint16 temp = smiRead(i | 0x18, 0);
//		temp |= 0x8000;
//		smiWrite(i | 0x18, 0, temp);
//	}

    //�л�������ʱ��
/*
    ra->writeReg(REG_CLOCK_SWITCH, 0x00);
    //�����ʼ״̬������PLL����λIP108
    uint16 value = ra->readReg(REG_PLL_ENABLE);
    value &= ~0x8001;
    ra->writeReg(REG_PLL_ENABLE, value);
    os_dly_wait(1);

    //ʹ��PLL
    value = ra->readReg(REG_PLL_ENABLE);
    value |= 1;
    ra->writeReg(REG_PLL_ENABLE, value);

    //�ȴ�PLL��
    while( (ra->readReg(REG_PLL_ENABLE) & 2) == 0 );

    //��λIP108
    value = ra->readReg(REG_PLL_ENABLE);
    value |= 0x8000;
    ra->writeReg(REG_PLL_ENABLE, value);
    os_dly_wait(50);

    //�л�����ʱ��
    ra->writeReg(REG_CLOCK_SWITCH, 1);
*/



	return donothing;
}

uint16 Chip8EOSCPLD::smiRead(uint16 phy, uint16 reg) {
	ra->writeReg(REG_SMI_Reg_ADDR, reg);
	ra->writeReg(REG_SMI_Phy_ADDR, phy, 0);
	while ((ra->readReg(REG_SMI_Phy_ADDR) >> 15) == 0)
		;
	return ra->readReg(REG_SMI_RDATA);
}
bool Chip8EOSCPLD::smiWrite(uint16 phy, uint16 reg, uint16 data) {
	ra->writeReg(REG_SMI_WDATA, data);
	ra->writeReg(REG_SMI_Reg_ADDR, reg);
	ra->writeReg(REG_SMI_Phy_ADDR, phy | 0x8000, 0);
	while ((ra->readReg(REG_SMI_Phy_ADDR) >> 15) == 0)
		;
	return true;
}
std::string Chip8EOSCPLD::GetChipVerInfo(const std::string ChipName,
		const uint16 Reg_Ver_Addr) {
	ChipVerInfo = ChipName + "V"
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 12 & 0xf)
			+ "."
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 8 & 0x7)
			+ "." + CPPTools::number2string(ra->readReg(Reg_Ver_Addr) & 0xff);
	return ChipVerInfo;
}
std::string  Chip8EOSCPLD::GetVerInfo(){
	return 	(GetChipVerInfo("PCB:",REG_VER_CPLD)).erase(8,2)+","+\
    		GetChipVerInfo("CPLD:",REG_VER_CPLD)+","+\
    		GetChipVerInfo("FPGA:",REG_VER_FPGA_ETHLOGIC);
}
