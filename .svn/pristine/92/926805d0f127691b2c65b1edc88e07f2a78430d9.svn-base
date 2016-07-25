/*
 * ChipXCCPLD.cpp
 *
 *  Created on: 2014Äê6ÔÂ26ÈÕ
 *      Author: Administrator
 */

#include "ChipXCCPLD.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "CPPTools.h"

static const std::string chipName = "XCCPLD";


ChipXCCPLD::ChipXCCPLD(CBaseSlot* slt) :
		BaseChip(chipName) {
	// TODO Auto-generated constructor stub
	ra = slt->getRegisterAccess();
}

ChipXCCPLD::~ChipXCCPLD() {
	// TODO Auto-generated destructor stub
}

std::string ChipXCCPLD::GetChipVerInfo(const std::string ChipName,
		const uint16 Reg_Ver_Addr) {
	if (Reg_Ver_Addr != 0x0011)
		ChipVerInfo = ChipName + "V"
				+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 12 & 0xf)
				+ "."
				+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 8 & 0x7)
				+ "."
				+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) & 0xff);
	else if (Reg_Ver_Addr == 0x0011)
		ChipVerInfo = ChipName + "V"
				+ CPPTools::number2string(
						(*(uint32*) (0xe2000000 + Reg_Ver_Addr - 1)) >> 4 & 0xf)
				+ "."\

				+ CPPTools::number2string(
						(*(uint32*) (0xe2000000 + Reg_Ver_Addr - 1)) & 0xf)
				+ "."\

				+ CPPTools::number2string(
						(*(uint32*) (0xe2000000 + Reg_Ver_Addr)) & 0xff);
	return ChipVerInfo;
}

std::string  ChipXCCPLD::GetVerInfo(){
	return 	(GetChipVerInfo("PCB-1:",REG_VER_CPLD_GENERALLOGIC_Z)).erase(10,2)+","\
    		+GetChipVerInfo("CPLD-1:",REG_VER_CPLD_GENERALLOGIC_Z)+","\
    		+(GetChipVerInfo("PCB-2:",REG_VER_CPLD_UOPTLOGIC)).erase(10,2)+","\
    		+GetChipVerInfo("CPLD-2:",REG_VER_CPLD_UOPTLOGIC)+","\
    		+GetChipVerInfo("FPGA-1:",REG_VER_FPGA_PCMLOGIC)+","\
    		+GetChipVerInfo("FPGA-2:",REG_VER_FPGA_SDHLOGIC)\
    		;
}

void ChipXCCPLD::turnLedOn(XC_LED_NAME name, bool on) {
    uint16 temp = ra->readReg(REG_XC_LEDS);
    if( on ) {
        temp &= ~(1 << name);
    }
    else {
        temp |= (1 << name);
    }
    ra->writeReg(REG_XC_LEDS, temp);
}

void ChipXCCPLD::turnLedWorkOn(bool on) {
    turnLedOn(LED_WRK, on);
}
void ChipXCCPLD::turnLedMajOn(bool on) {
    turnLedOn(LED_MAJ, on);
}
void ChipXCCPLD::turnLedMinOn(bool on) {
    turnLedOn(LED_MIN, on);
}
void ChipXCCPLD::turnLedLosAOn(bool on) {
    turnLedOn(LED_LOSA, on);
}
void ChipXCCPLD::turnLedAlmAOn(bool on) {
    turnLedOn(LED_ALMA, on);
}
void ChipXCCPLD::turnLedLosBOn(bool on) {
    turnLedOn(LED_LOSB, on);
}
void ChipXCCPLD::turnLedAlmBOn(bool on) {
    turnLedOn(LED_ALMB, on);
}
