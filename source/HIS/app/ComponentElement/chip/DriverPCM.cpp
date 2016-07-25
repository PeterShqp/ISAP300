/*
 * DriverPCM.cpp
 *
 *  Created on: 2015年6月4日
 *      Author: Administrator
 */

#include "DriverPCM.h"
#include <stdio.h>

DriverPCM::DriverPCM() {
    // TODO Auto-generated constructor stub

}

DriverPCM::~DriverPCM() {
    // TODO Auto-generated destructor stub
}

bool DriverPCM::ifSaHavePacket(uint8 ch) {
    if( ifSaHavePacket() ) {
        if( getSourceCh() == ch ) {
            return true;
        }
    }
    return false;
}
