/*
 * DXCAlarmModule.h
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */

#ifndef DXCALARMMODULE_H_
#define DXCALARMMODULE_H_

#include "BAlarmModule.h"
#include "os.h"

class CardDXC;

class DXCAlarmModule: public BAlarmModule {
public:
    DXCAlarmModule(CardDXC*);
    virtual ~DXCAlarmModule();

    virtual void creatAlarmSource();

    void turnLedMajOn(bool on);
    void turnLedMinOn(bool on);
private:
    CardDXC* XCCard;
    OS_TID dxc_alarm;
};

#endif /* DXCALARMMODULE_H_ */
