/*
 * F16E1PCMClockSource.cpp
 *
 *  Created on: 2015年10月27日
 *      Author: Administrator
 */

#include "F16E1PCMClockSource.h"
#include "ChipE1Port16Logic.h"

F16E1PCMClockSource::F16E1PCMClockSource(uint32 uid, uint8 sn, DriverPCM& pcm, ChipE1Port16Logic& fe1)
    : ClockSource(uid, false), DriPCM(pcm), DriFE1(fe1) {

    itsSn = sn;

}

F16E1PCMClockSource::~F16E1PCMClockSource() {
    // TODO Auto-generated destructor stub
}

CLOCK_STATUS_E F16E1PCMClockSource::getStatus(void) {
    if( DriFE1.itsLOS(itsSn) ) {
        return clock_failed;
    }
    return clock_ok;
}

bool F16E1PCMClockSource::active(void) {
    DriPCM.selectPCMClock(5);
    DriFE1.selectPCMClock(itsSn | 0x10);
    return true;
}

bool F16E1PCMClockSource::deActive(void) {
    DriFE1.selectPCMClock(0);
    return true;
}

//std::string& F16E1PCMClockSource::getPortName(void) {
//
//}
