/*
 * E1CardAlarmModule.cpp
 *
 *  Created on: 2014Äê9ÔÂ9ÈÕ
 *      Author: Administrator
 */

#include "E1CardAlarmModule.h"
#include "SrcAlarmE1.h"
#include "Card24E1.h"

E1CardAlarmModule::E1CardAlarmModule(Card24E1* c) : BAlarmModule(c), led(c->chipE1) {

    card = c;

}

E1CardAlarmModule::~E1CardAlarmModule() {
    // TODO Auto-generated destructor stub
}

void E1CardAlarmModule::creatAlarmSource() {
    for (int i = 0; i < 24; ++i) {
        addAlmSrc( new SrcAlarmE1(this, card->e1port_obj[i], &(card->ConfigData.E1AlmData[i]), led) );
    }
}
