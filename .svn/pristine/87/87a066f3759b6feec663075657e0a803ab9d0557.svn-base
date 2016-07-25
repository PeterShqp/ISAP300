/*
 * XcOPTClockSource.cpp
 *
 *  Created on: 2014-1-20
 *      Author: Administrator
 */

#include "XcOPTClockSource.h"
#include "DriverPCM.h"
#include "ChipCP1121A.h"
#include "ClockZarlink30122.h"

XcOPTClockSource::XcOPTClockSource(uint32 index, DriverPCM* cpcm, ChipCP1121A* c1121, ClockZarlink30122* c2, bool paired)
        : ClockSource(index, paired) {
    // TODO Auto-generated constructor stub
    xsc = cpcm;
    state = c1121;
    clockChip = c2;
}

XcOPTClockSource::~XcOPTClockSource() {
    // TODO Auto-generated destructor stub
}

CLOCK_STATUS_E XcOPTClockSource::getStatus(void) {
    if( state->getLOS(getUID() & 0xff) ) {
        return clock_failed;
    }
    return clock_ok;
}

bool XcOPTClockSource::active(void) {
    int sn = getUID() & 0xff;
    USEABLE_RCLOCK c;
    if( sn == 0 ) {
        c = RCLKA;
    }
    else {
        c = RCLKB;
    }
    xsc->selectClockSource(c);
    clockChip->selectFref(FrefChannel1);
    return true;
}

