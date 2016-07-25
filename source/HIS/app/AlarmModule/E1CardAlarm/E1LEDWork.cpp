/*
 * E1LEDWork.cpp
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#include "E1LEDWork.h"
#include "Chip16E1CPLD.h"

E1LEDWork::E1LEDWork(uint8 sn, Chip16E1CPLD& d) : DisplayMultiSignalOR("E1_LED_WORK"), Driver(d) {
    ItsSn = sn;
    Driver.ledWorkOn(ItsSn, false);

}

E1LEDWork::~E1LEDWork() {
    // TODO Auto-generated destructor stub
}

void E1LEDWork::display(bool alarm) {
    Driver.ledWorkOn(ItsSn, !alarm);
}
