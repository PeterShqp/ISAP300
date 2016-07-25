/*
 * F16E1PCMClockSource.h
 *
 *  Created on: 2015年10月27日
 *      Author: Administrator
 */

#ifndef F16E1PCMCLOCKSOURCE_H_
#define F16E1PCMCLOCKSOURCE_H_

#include "ClockSource.h"

class DriverPCM;
class ChipE1Port16Logic;

class F16E1PCMClockSource: public ClockSource {
public:
    F16E1PCMClockSource(uint32 uid, uint8 sn, DriverPCM& pcm, ChipE1Port16Logic& fe1);
    virtual ~F16E1PCMClockSource();

    virtual CLOCK_STATUS_E getStatus(void);
    virtual bool active(void);
    virtual bool deActive(void);

//    virtual std::string& getPortName(void);
private:
    DriverPCM& DriPCM;
    ChipE1Port16Logic& DriFE1;
    uint8 itsSn; //0~15 port1~16
};

#endif /* F16E1PCMCLOCKSOURCE_H_ */
