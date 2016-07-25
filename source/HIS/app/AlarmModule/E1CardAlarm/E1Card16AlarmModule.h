/*
 * E1Card16AlarmModule.h
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef E1CARD16ALARMMODULE_H_
#define E1CARD16ALARMMODULE_H_

#include "BAlarmModule.h"

class Card16E1;

class E1Card16AlarmModule: public BAlarmModule {
public:
    E1Card16AlarmModule(Card16E1*);
    virtual ~E1Card16AlarmModule();

    virtual void creatAlarmSource();

private:
    Card16E1* card;
};

#endif /* E1CARD16ALARMMODULE_H_ */
