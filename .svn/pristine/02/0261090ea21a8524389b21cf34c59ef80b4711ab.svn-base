/*
 * XcLocalClockSource.h
 *
 *  Created on: 2014-3-1
 *      Author: Administrator
 */

#ifndef XCLOCALCLOCKSOURCE_H_
#define XCLOCALCLOCKSOURCE_H_

#include "ClockSource.h"

class DriverPCM;
class XcLocalClockSource : public ClockSource {
public:
    XcLocalClockSource(int index, DriverPCM*);
    virtual ~XcLocalClockSource();


    virtual CLOCK_STATUS_E getStatus(void);
    virtual bool active(void);
private:
    DriverPCM* chip;
};

#endif /* XCLOCALCLOCKSOURCE_H_ */
