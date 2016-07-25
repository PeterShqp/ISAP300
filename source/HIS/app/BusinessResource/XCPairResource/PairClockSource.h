/*
 * PairClockSource.h
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRCLOCKSOURCE_H_
#define PAIRCLOCKSOURCE_H_

#include "ClockSource.h"
#include <string>
#include "PairResource.h"

class PairClockSource : public ClockSource {
public:
    PairClockSource(uint32 uid, PairResource*);
    virtual ~PairClockSource();

    virtual CLOCK_STATUS_E getStatus(void);
    virtual bool active(void);
    virtual std::string& getPortName(void);
private:
    PairResource PairTool;
    PairResource* Port;
};

#endif /* PAIRCLOCKSOURCE_H_ */
