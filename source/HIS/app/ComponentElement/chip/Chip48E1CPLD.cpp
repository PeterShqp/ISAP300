/*
 * Chip48E1CPLD.cpp
 *
 *  Created on: 2014Äê6ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "Chip48E1CPLD.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "CPPTools.h"
static const std::string chipName = "48E1CPLD";
Chip48E1CPLD::Chip48E1CPLD(CBaseSlot* slt) :
		BaseChip(chipName) {
	// TODO Auto-generated constructor stub
	ra = slt->getRegisterAccess();
}

Chip48E1CPLD::~Chip48E1CPLD() {
	// TODO Auto-generated destructor stub
}

std::string Chip48E1CPLD::GetChipVerInfo(const std::string ChipName,
		const uint16 Reg_Ver_Addr) {
	ChipVerInfo = ChipName + "V"
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 12 & 0xf)
			+ "."
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 8 & 0x7)
			+ "." + CPPTools::number2string(ra->readReg(Reg_Ver_Addr) & 0xff);
	return ChipVerInfo;
}
std::string  Chip48E1CPLD::GetVerInfo(){
	return 	(GetChipVerInfo("PCB:",REG_VER_CPLD)).erase(8,2)+","+\
			GetChipVerInfo("CPLD-1:",REG_VER_CPLD)+","+\
			GetChipVerInfo("CPLD-2:",REG_VER_CPLD_E1PORTLOGIC_1)+","+\
			GetChipVerInfo("CPLD-3:",REG_VER_CPLD_E1PORTLOGIC_2)+","+\
			GetChipVerInfo("CPLD-4:",REG_VER_CPLD_E1PORTLOGIC_3)+","+\
			GetChipVerInfo("FPGA:",REG_VER_FPGA_E1LOGIC);
}
