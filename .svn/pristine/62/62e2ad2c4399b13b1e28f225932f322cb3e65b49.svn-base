/*
 * XCAlarmModule.h
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#ifndef XCALARMMODULE_H_
#define XCALARMMODULE_H_

#include "BAlarmModule.h"
#include "os.h"

class CardXC;

class XCAlarmModule: public BAlarmModule {
public:
    XCAlarmModule(CardXC*);
    virtual ~XCAlarmModule();

    virtual void creatAlarmSource();

    virtual bool ifMCUModule(void) {
        return true;
    };

    void turnLedMajOn(bool on);
    void turnLedMinOn(bool on);

private:
    CardXC* XCCard;
    OS_TID xc_alarm;

};

#endif /* XCALARMMODULE_H_ */
