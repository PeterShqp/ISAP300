/*
 * E1LEDAis.cpp
 *
 *  Created on: 2014Äê10ÔÂ23ÈÕ
 *      Author: Administrator
 */

#include "E1LEDAis.h"
#include "Chip16E1Logic.h"

E1LEDAis::E1LEDAis(uint8 sn, Chip16E1Logic& d) : DisplayMultiSignalOR("E1_LED_AIS"), Driver(d) {
    ItsSn = sn;
    Driver.ledAlarmOn(ItsSn, false);
}

E1LEDAis::~E1LEDAis() {
    // TODO Auto-generated destructor stub
}

void E1LEDAis::display(bool alarm) {
    Driver.ledAlarmOn(ItsSn, alarm);
}
