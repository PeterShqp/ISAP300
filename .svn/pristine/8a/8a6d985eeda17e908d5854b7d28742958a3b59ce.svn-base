/*
 * SrcAlarm16E1.h
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef SRCALARM16E1_H_
#define SRCALARM16E1_H_

#include "SrcAlarmE1.h"
#include "E1LEDWork.h"
#include "E1LEDAis.h"

class SrcAlarm16E1: public SrcAlarmE1 {
public:
    SrcAlarm16E1(BAlarmModule*, PortE1*, SrcE1Alarm_Data*, Chip16E1CPLD&, Chip16E1Logic&);
    virtual ~SrcAlarm16E1();

private:
    E1LEDWork led;
    E1LEDAis LedAis;
};

#endif /* SRCALARM16E1_H_ */
