/*
 * XcPCMClockSource.cpp
 *
 *  Created on: 2014��12��16��
 *      Author: Administrator
 */

#include "XcPCMClockSource.h"
#include "DriverPCM.h"

XcPCMClockSource::XcPCMClockSource(uint32 uid, uint8 sn, DriverPCM& pcm) : ClockSource(uid, true), driver(pcm){
    itsSn = sn;

}

XcPCMClockSource::~XcPCMClockSource() {
    // TODO Auto-generated destructor stub
}

//bool XcPCMClockSource::selectPCMClock(uint8 mode) {
//    driver.selectPCMClock(mode);
//    return true;
//}

CLOCK_STATUS_E XcPCMClockSource::getStatus(void) {
    if( itsSn != 0 ) {
        if( driver.itsLOS(itsSn-1) ) {
            return clock_failed;
        }
    }
    return clock_ok;
}
bool XcPCMClockSource::active(void) {
    driver.selectPCMClock(itsSn);
    return true;
}
