/*
 * Chip16E1CPLD.cpp
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#include "Chip16E1CPLD.h"
#include "RegisterAccess.h"

static const std::string chipName = "16E1CPLD";

Chip16E1CPLD::Chip16E1CPLD(CBaseSlot* slt) : Chip24E1CPLD(slt, chipName) {
    // TODO Auto-generated constructor stub

}

Chip16E1CPLD::~Chip16E1CPLD() {
    // TODO Auto-generated destructor stub
}

void Chip16E1CPLD::ledWorkOn(uint8 sn, bool on) {
    uint16 temp = ra->readReg(REG_LED_WRK);
    if( on ) {
        temp &= ~(1 << sn);
    }
    else {
        temp |= (1 << sn);
    }
    ra->writeReg(REG_LED_WRK, temp);
}

std::string  Chip16E1CPLD::GetVerInfo(){
    return  (GetChipVerInfo("PCB:",REG_VER_CPLD)).erase(8,2)+","+\
             GetChipVerInfo("CPLD-1:",REG_VER_CPLD)+","+\
             GetChipVerInfo("CPLD-2:",REG_VER_CPLD_E1PORTLOGIC_1)+","+\
             GetChipVerInfo("FPGA:",REG_VER_FPGA_E1LOGIC);
}
