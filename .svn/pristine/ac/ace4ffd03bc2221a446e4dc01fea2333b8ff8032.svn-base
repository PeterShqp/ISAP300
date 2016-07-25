/*
 * E1Card48AlarmModule.h
 *
 *  Created on: 2014Äê10ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef E1CARD48ALARMMODULE_H_
#define E1CARD48ALARMMODULE_H_

#include "BAlarmModule.h"
#include "E1LEDs.h"

class Card48E1;
class E1Card48AlarmModule : public BAlarmModule {
public:
    E1Card48AlarmModule(Card48E1*);
    virtual ~E1Card48AlarmModule();

    virtual void creatAlarmSource();

private:
    Card48E1* card;
    E1LEDs led;
};

#endif /* E1CARD48ALARMMODULE_H_ */
