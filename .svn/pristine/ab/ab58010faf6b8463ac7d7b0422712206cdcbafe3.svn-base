/*
 * ChipE1Logic.cpp
 *
 *  Created on: 2013-12-17
 *      Author: Administrator
 */

#include "ChipE1Logic.h"

#include "RegisterAccess.h"
#include <iostream>
#include "CBaseSlot.h"
#include <string>
#include <stdio.h>
#include "os.h"

static const std::string chipName = "E1Logic";



ChipE1Logic::ChipE1Logic(CBaseSlot* slt) : FPGAChip(chipName, slt) {

}

ChipE1Logic::ChipE1Logic(const std::string& name, CBaseSlot* slt) : FPGAChip(name, slt) {

}

ChipE1Logic::~ChipE1Logic() {
    // TODO Auto-generated destructor stub
}

void ChipE1Logic::initRegs(void) {
    regAccess->writeReg(0x0101, 0xA0A0, false);
    os_dly_wait(1);
    regAccess->writeReg(0x0101, 0xA1A1, false);
    os_dly_wait(1);
    regAccess->writeReg(0x8000+0x0014, 0x0014); //RC7883 map
//    regAccess->writeReg(0xa000+0x0014, 0x0014);
    regAccess->writeReg(REG_LED_CTRL, 0x0e);
}


Chip_INIT_RESULT ChipE1Logic::ChipInit(void) {
    Chip_INIT_RESULT rtn = updataFPGA();
    if( rtn == succeed ) {
        initRegs();//temp test
    }
    return rtn;

}

void ChipE1Logic::ledWorkOn(bool on) {
    ledOn(LED_WRK, on);
}
void ChipE1Logic::ledAlmkOn(bool on) {
    ledOn(LED_ALM, on);
}
void ChipE1Logic::ledConnectOn(bool on) {
    ledOn(LED_CON, on);
}
void ChipE1Logic::ledDropOn(bool on) {
    ledOn(LED_DRP, on);
}


void ChipE1Logic::ledOn(E1_LED_E led, bool on) {
    uint16 temp = regAccess->readReg(REG_LED_CTRL);
    if( on ) {
        temp &= ~(1 << led);
    }
    else {
        temp |= (1 << led);
    }
    regAccess->writeReg(REG_LED_CTRL, temp);
}
