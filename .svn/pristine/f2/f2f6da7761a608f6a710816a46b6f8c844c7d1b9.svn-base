/*
 * Chip16DATACPLD.cpp
 *
 *  Created on: 2015Äê1ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "Chip16DATACPLD.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "CPPTools.h"
static const std::string chipName = "16DATACPLD";

Chip16DATACPLD::Chip16DATACPLD(CBaseSlot* slt) :
        BaseChip(chipName){
	// TODO Auto-generated constructor stub
    ra = slt->getRegisterAccess();
}

Chip16DATACPLD::~Chip16DATACPLD() {
	// TODO Auto-generated destructor stub
}
std::string Chip16DATACPLD::GetChipVerInfo(const std::string ChipName,
		const uint16 Reg_Ver_Addr) {
	ChipVerInfo = ChipName + "V"
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 12 & 0xf)
			+ "."
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 8 & 0x7)
			+ "." + CPPTools::number2string(ra->readReg(Reg_Ver_Addr) & 0xff);
	return ChipVerInfo;
}
std::string  Chip16DATACPLD::GetVerInfo(){
    return  (GetChipVerInfo("PCB:",REG_VER_CPLD)).erase(8,2)+","+\
             GetChipVerInfo("CPLD-1:",REG_VER_CPLD);
}
