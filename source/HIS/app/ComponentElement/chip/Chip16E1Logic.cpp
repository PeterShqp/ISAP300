/*
 * Chip16E1Logic.cpp
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#include "Chip16E1Logic.h"
#include "RegisterAccess.h"

static const std::string chipName = "E1Logic16";

Chip16E1Logic::Chip16E1Logic(CBaseSlot* slt) : ChipE1Logic(chipName, slt) {

}

Chip16E1Logic::~Chip16E1Logic() {
    // TODO Auto-generated destructor stub
}



void Chip16E1Logic::ledAlarmOn(uint8 sn, bool on) {
    uint16 temp = regAccess->readReg(REG_LED_ALM);
    if( on ) {
        temp &= ~(1 << sn);
    }
    else {
        temp |= (1 << sn);
    }
    regAccess->writeReg(REG_LED_ALM, temp);
}


