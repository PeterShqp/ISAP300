/*
 * Chip30VFCPLD.cpp
 *
 *  Created on: 2014��6��26��
 *      Author: Administrator
 */

#include "Chip30VFCPLD.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "CPPTools.h"
#include <rtl.h>
static const std::string chipName = "VFCPLD";
Chip30VFCPLD::Chip30VFCPLD(CBaseSlot* slt) :
		BaseChip(chipName) {
	// TODO Auto-generated constructor stub
	ra = slt->getRegisterAccess(); //�L�����Q��base���ϣ�������Ҫ��ʼ����A��
}

Chip30VFCPLD::~Chip30VFCPLD() {
	// TODO Auto-generated destructor stub
}

std::string Chip30VFCPLD::GetChipVerInfo(const std::string ChipName,
		const uint16 Reg_Ver_Addr) {
	ChipVerInfo = ChipName + "V"
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 12 & 0xf)
			+ "."
			+ CPPTools::number2string(ra->readReg(Reg_Ver_Addr) >> 8 & 0x7)
			+ "." + CPPTools::number2string(ra->readReg(Reg_Ver_Addr) & 0xff);
	return ChipVerInfo;
}
std::string Chip30VFCPLD:: GetVerInfo(void){
	return  (GetChipVerInfo("PCB:", REG_VER_CPLD)).erase(8,2)+","+\
            GetChipVerInfo("CPLD:", REG_VER_CPLD);
}

bool Chip30VFCPLD::Resetchip(void) {

	ra->writeReg(REG_RST_CPLD, ra->readReg(REG_RST_CPLD) | 0x01);
	os_dly_wait(1);
	ra->writeReg(REG_RST_CPLD, ra->readReg(REG_RST_CPLD) & (~0x01));
	return true;
}
