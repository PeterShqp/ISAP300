/*
 * XcExtClockSource.h
 *
 *  Created on: 2014-1-20
 *      Author: Administrator
 */

#ifndef XCEXTCLOCKSOURCE_H_
#define XCEXTCLOCKSOURCE_H_

#include "ClockSource.h"
#include "DriverPCM.h"
#include "ClockZarlink30122.h"



class XcExtClockSource : public ClockSource {
public:
    XcExtClockSource(uint32 index, DriverPCM*, ClockZarlink30122*, bool paired = false);
    virtual ~XcExtClockSource();

    virtual CLOCK_STATUS_E getStatus(void);
    virtual bool active(void);
private:
    DriverPCM* xsc;
    ClockZarlink30122* clockChip;
    ExtClock_type_E type;
    USEABLE_RCLOCK hid;

};

#endif /* XCEXTCLOCKSOURCE_H_ */
