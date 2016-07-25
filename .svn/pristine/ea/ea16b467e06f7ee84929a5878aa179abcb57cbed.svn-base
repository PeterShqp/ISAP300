/*
 * E1LEDWork.h
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef E1LEDWORK_H_
#define E1LEDWORK_H_

#include "DisplayMultiSignalOR.h"
#include "EZ_types.h"

class Chip16E1CPLD;
class E1LEDWork: public DisplayMultiSignalOR {
public:
    E1LEDWork(uint8 sn, Chip16E1CPLD& d);
    virtual ~E1LEDWork();

    virtual void display(bool alarm);
private:
    uint8 ItsSn;
    Chip16E1CPLD& Driver;
};

#endif /* E1LEDWORK_H_ */
