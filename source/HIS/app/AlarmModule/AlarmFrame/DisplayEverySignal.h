/*
 * DisplayEverySignal.h
 *
 *  Created on: 2014Äê10ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef DISPLAYEVERYSIGNAL_H_
#define DISPLAYEVERYSIGNAL_H_

#include "BAlarmDisplay.h"

class DisplayEverySignal: public BAlarmDisplay {
public:
    DisplayEverySignal(const char* name);
    virtual ~DisplayEverySignal();

    virtual void update(AlarmInstance*);
    virtual void display(bool alarm) = 0;
};

#endif /* DISPLAYEVERYSIGNAL_H_ */
