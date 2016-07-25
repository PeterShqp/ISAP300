/*
 * E1Card16AlarmModule.cpp
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#include "E1Card16AlarmModule.h"
#include "Card16E1.h"
#include "SrcAlarm16E1.h"

E1Card16AlarmModule::E1Card16AlarmModule(Card16E1* c) : BAlarmModule(c) {
    card = c;

}

E1Card16AlarmModule::~E1Card16AlarmModule() {
    // TODO Auto-generated destructor stub
}

void E1Card16AlarmModule::creatAlarmSource() {
    for (int i = 0; i < 16; ++i) {
        addAlmSrc( new SrcAlarm16E1(this, card->e1port_obj[i], &(card->ConfigData.E1AlmData[i]), card->cpld, card->chipE1) );
    }
}
