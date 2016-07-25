/*
 * E1LEDs.cpp
 *
 *  Created on: 2014Äê10ÔÂ16ÈÕ
 *      Author: Administrator
 */

#include "E1LEDs.h"
#include "ChipE1Logic.h"
#include "SysError.h"

TASK void e1_multi_leds(void* E1LEDs);

E1LEDs::E1LEDs(ChipE1Logic& d) : DisplayEverySignal("E1_LED_Drop_Link"), Driver(d) {
    DropSt = false;
    ConnSt = false;
    Driver.ledDropOn(false);
    Driver.ledConnectOn(false);
    Driver.ledAlmkOn(false);
    Driver.ledWorkOn(true);
}

E1LEDs::~E1LEDs() {
}

void E1LEDs::display(bool alarm) {
    if( alarm ) {
        flashLEDDrop();
    }
    else {
        flashLEDLink();
    }
}


void E1LEDs::flashLEDDrop(void) {
    if( DropSt ) {
        return;
    }
    DropSt = true;
    taske1led = os_tsk_create_ex(e1_multi_leds, P_LED, this);



}
void E1LEDs::flashLEDLink(void) {
    if( ConnSt ) {
        return;
    }
    ConnSt = true;
    taske1led = os_tsk_create_ex(e1_multi_leds, P_LED, this);
}

TASK void e1_multi_leds(void* module) {
    if( module == 0 ) {
        throw SysError("!!!No LED Object!!!");
    }
    E1LEDs* led = (E1LEDs*)module;

    if( led->DropSt ) {
       for (int i = 0; i < 3; ++i) {

            led->Driver.ledDropOn(true);
            os_dly_wait(50);
            led->Driver.ledDropOn(false);
            os_dly_wait(50);
       }
       led->DropSt = false;
    }
    if( led->ConnSt ) {
        for (int i = 0; i < 3; ++i) {

             led->Driver.ledConnectOn(true);
             os_dly_wait(50);
             led->Driver.ledConnectOn(false);
             os_dly_wait(50);
        }
        led->ConnSt = false;
    }

    os_tsk_delete_self();
}
