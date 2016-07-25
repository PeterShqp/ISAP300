/*
 * Trib8STM1AlarmModule.h
 *
 *  Created on: 2014Äê9ÔÂ16ÈÕ
 *      Author: Administrator
 */

#ifndef TRIB8STM1ALARMMODULE_H_
#define TRIB8STM1ALARMMODULE_H_

#include "BAlarmModule.h"

class Card8STM1;

class Trib8STM1AlarmModule: public BAlarmModule {
public:
    Trib8STM1AlarmModule(Card8STM1*);
    virtual ~Trib8STM1AlarmModule();

    virtual void creatAlarmSource();
private:
    Card8STM1* card;
};

#endif /* TRIB8STM1ALARMMODULE_H_ */
