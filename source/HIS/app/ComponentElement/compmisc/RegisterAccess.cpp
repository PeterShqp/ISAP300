/*
 * RegisterAccess.cpp
 *
 *  Created on: 2013-12-1
 *      Author: Administrator
 */

#include "RegisterAccess.h"

RegisterAccess::RegisterAccess() {
    // TODO Auto-generated constructor stub

}

RegisterAccess::~RegisterAccess() {
    // TODO Auto-generated destructor stub
}

bool RegisterAccess::readRegCheck(uint16 regAddr, uint16* regValue, int retry) {
    while( retry > 0 ) {
        --retry;
        if( readRegCheck3(regAddr, regValue) ) {
            return true;
        }
    }
    return false;
}

bool RegisterAccess::readRegCheck3(uint16 regAddr, uint16* regValue, uint16 bitmask) {
    uint16 vArray[3] = {0};
    for (int i = 0; i < sizeof(vArray)/sizeof(vArray[0]); ++i) {
        vArray[i] = readReg(regAddr) & bitmask;
        if(vArray[0] != vArray[i]) {
            return false;
        }
    }
    *regValue = vArray[0];
    return true;

}
