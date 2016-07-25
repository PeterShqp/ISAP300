/*
 * TribSTMLEDLOS.cpp
 *
 *  Created on: 2014Äê9ÔÂ17ÈÕ
 *      Author: Administrator
 */

#include "TribSTMLEDLOS.h"
#include "Chip8STM1Logic2.h"

TribSTMLEDLOS::TribSTMLEDLOS(int sn, Chip8STM1Logic2& d) : DisplayMultiSignalOR("TribSTM_LED_LOS"), Driver(d) {
    Sn = sn;
    Driver.portLEDLosOn(Sn, false);
}

TribSTMLEDLOS::~TribSTMLEDLOS() {
    // TODO Auto-generated destructor stub
}

void TribSTMLEDLOS::display(bool alarm) {
    Driver.portLEDLosOn(Sn, alarm);
}
