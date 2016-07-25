/*
 * XcPCMClockSource.h
 *
 *  Created on: 2014��12��16��
 *      Author: Administrator
 */

#ifndef XCPCMCLOCKSOURCE_H_
#define XCPCMCLOCKSOURCE_H_

#include "ClockSource.h"

class DriverPCM;
class XcPCMClockSource : public ClockSource {
public:
    XcPCMClockSource(uint32 uid, uint8 sn, DriverPCM&);
    virtual ~XcPCMClockSource();

//    bool selectPCMClock(uint8 mode);
    virtual CLOCK_STATUS_E getStatus(void);
    virtual bool active(void);
private:
    DriverPCM& driver;
    uint8 itsSn; //0 local 1~8 recover
};

#endif /* XCPCMCLOCKSOURCE_H_ */
