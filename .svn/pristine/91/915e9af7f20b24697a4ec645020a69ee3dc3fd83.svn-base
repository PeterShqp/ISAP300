/*
 * E1Card48AlarmModule.cpp
 *
 *  Created on: 2014Äê10ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "E1Card48AlarmModule.h"
#include "Card48E1.h"
#include "SrcAlarmE1.h"

E1Card48AlarmModule::E1Card48AlarmModule(Card48E1* c) : BAlarmModule(c), led(c->chipE1) {
    card = c;

}

E1Card48AlarmModule::~E1Card48AlarmModule() {
    // TODO Auto-generated destructor stub
}

void E1Card48AlarmModule::creatAlarmSource() {
    for (int i = 0; i < 48; ++i) {
        addAlmSrc( new SrcAlarmE1(this, card->e1port_obj[i], &(card->ConfigData.E1AlmData[i]), led) );
    }
}
