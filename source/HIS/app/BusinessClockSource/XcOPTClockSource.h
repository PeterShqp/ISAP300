/*
 * XcOPTClockSource.h
 *
 *  Created on: 2014-1-20
 *      Author: Administrator
 */

#ifndef XCOPTCLOCKSOURCE_H_
#define XCOPTCLOCKSOURCE_H_

#include "ClockSource.h"

class DriverPCM;
class ChipCP1121A;
class ClockZarlink30122;

class XcOPTClockSource : public ClockSource {
public:
    XcOPTClockSource(uint32 index, DriverPCM*, ChipCP1121A*, ClockZarlink30122* , bool paired = false);
    virtual ~XcOPTClockSource();

    virtual CLOCK_STATUS_E getStatus(void);
    virtual bool active(void);
private:
    DriverPCM* xsc;
    ClockZarlink30122* clockChip;
    ChipCP1121A* state;
};

#endif /* XCOPTCLOCKSOURCE_H_ */
