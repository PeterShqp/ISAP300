/*
 * XcLocalClockSource.cpp
 *
 *  Created on: 2014-3-1
 *      Author: Administrator
 */

#include "XcLocalClockSource.h"
#include <string>
#include "DriverPCM.h"

XcLocalClockSource::XcLocalClockSource(int index, DriverPCM* c) : ClockSource(index, true) {
    // TODO Auto-generated constructor stub
    chip = c;
}

XcLocalClockSource::~XcLocalClockSource() {
    // TODO Auto-generated destructor stub
}

CLOCK_STATUS_E XcLocalClockSource::getStatus(void) {
    return clock_ok;
}

bool XcLocalClockSource::active(void) {
    chip->selectClockSource(RCLKLocal);
    return true;
}
