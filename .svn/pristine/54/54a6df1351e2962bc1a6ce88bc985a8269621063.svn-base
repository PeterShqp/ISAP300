/*
 * E1LEDs.h
 *
 *  Created on: 2014Äê10ÔÂ16ÈÕ
 *      Author: Administrator
 */

#ifndef E1LEDS_H_
#define E1LEDS_H_

#include "DisplayEverySignal.h"
#include "os.h"

class ChipE1Logic;
class E1LEDs: public DisplayEverySignal {
public:
    E1LEDs(ChipE1Logic& d);
    virtual ~E1LEDs();

    virtual void display(bool alarm);

private:
    friend TASK void e1_multi_leds(void* module);
    void flashLEDDrop(void);
    void flashLEDLink(void);
    ChipE1Logic& Driver;
    OS_TID taske1led;
    bool DropSt;
    bool ConnSt;
};

#endif /* E1LEDS_H_ */
