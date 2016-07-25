/*
 * Chip24E1CPLD.cpp
 *
 *  Created on: 2014Äê6ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "Chip24E1CPLD.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "CPPTools.h"
static const std::string chipName = "24E1CPLD";
Chip24E1CPLD::Chip24E1CPLD(CBaseSlot* slt) :
		BaseChip(chipName) {
	// TODO Auto-generated constructor stub
	ra = slt->getRegisterAccess();
}

Chip24E1CPLD::Chip24E1CPLD(CBaseSlot* slt, const std::string& name) : BaseChip(name) {
    ra = slt->getRegisterAccess();
}

Chip24E1CPLD::~Chip24E1CPLD() {
	// TODO Auto-generated destructor stub
}

std::string Chip24E1CPLD::GetChipVerInfo(const std::string ChipName,
		const uint16 Reg_Ver_Addr) {
	ChipVerInfo = ChipName + "V"
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 12 & 0xf)
			+ "."
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 8 & 0x7)
			+ "." + CPPTools::number2string(ra->readReg(Reg_Ver_Addr) & 0xff);
	return ChipVerInfo;
}
std::string  Chip24E1CPLD::GetVerInfo(){
	return 	(GetChipVerInfo("PCB:",REG_VER_CPLD)).erase(8,2)+","+\
			 GetChipVerInfo("CPLD-1:",REG_VER_CPLD)+","+\
			 GetChipVerInfo("CPLD-2:",REG_VER_CPLD_E1PORTLOGIC_1)+","+\
			 GetChipVerInfo("CPLD-3:",REG_VER_CPLD_E1PORTLOGIC_2)+","+\
			 GetChipVerInfo("FPGA:",REG_VER_FPGA_E1LOGIC);
}
