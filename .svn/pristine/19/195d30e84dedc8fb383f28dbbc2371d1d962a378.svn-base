/*
 * XcExtClockSource.cpp
 *
 *  Created on: 2014-1-20
 *      Author: Administrator
 */

#include "XcExtClockSource.h"

XcExtClockSource::XcExtClockSource(uint32 index,  DriverPCM* c, ClockZarlink30122* c2, bool paired)
        : ClockSource(index, paired)  {
    // TODO Auto-generated constructor stub
    xsc = c;
    clockChip = c2;
    /*�̶���һ����ʱ�ӽӿ�Ϊ2MHz �ڶ���Ϊ2MBit*/
    if( index & 0xff == 0 ) {
        type = type_2MHz;
        hid = RCLK2MA;
        xsc->setExtClockMode(RCLK2MA, type);
    }
    else {
        type = type_2Mbit;
        hid = RCLK2MB;
        xsc->setExtClockMode(RCLK2MB, type);
    }

}

XcExtClockSource::~XcExtClockSource() {
    // TODO Auto-generated destructor stub
}

CLOCK_STATUS_E XcExtClockSource::getStatus(void) {
    bool sta;
    if( hid  == RCLK2MA ) {
        sta = xsc->itsLOS(2);
    }
    else {
        sta = xsc->itsLOS(3);
    }
    if( sta ) {
        return clock_failed;
    }
    return clock_ok;
}
bool XcExtClockSource::active(void) {
    xsc->selectClockSource(hid);
    clockChip->selectFref(FrefChannel2);
    return true;
}
