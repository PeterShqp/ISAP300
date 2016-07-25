/*
 * Trib4STM1AlarmModule.h
 *
 *  Created on: 2014��9��16��
 *      Author: Administrator
 */

#ifndef TRIB4STM1ALARMMODULE_H_
#define TRIB4STM1ALARMMODULE_H_

#include "BAlarmModule.h"
#include "os.h"

class Card4STM1;

class Trib4STM1AlarmModule: public BAlarmModule {
public:
    Trib4STM1AlarmModule(Card4STM1*);
    virtual ~Trib4STM1AlarmModule();

    virtual void creatAlarmSource();

    void turnLedAlarmOn(bool on);



private:
    Card4STM1* card;
    OS_TID led_alarm;

};

#endif /* TRIB4STM1ALARMMODULE_H_ */
