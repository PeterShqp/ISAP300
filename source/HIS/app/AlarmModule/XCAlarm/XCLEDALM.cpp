/*
 * XCLEDALM.cpp
 *
 *  Created on: 2014Äê8ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "XCLEDALM.h"
#include "ISAP100LED.h"
#include "ChipXCCPLD.h"

XCLEDALM::XCLEDALM(int sn, ChipXCCPLD& d) : DisplayMultiSignalOR("XC_LED_ALM"), Driver(d) {
    itsSn = sn;
    led_sfpalm_a_off();
    led_sfpalm_b_off();
    Driver.turnLedAlmAOn(false);
    Driver.turnLedAlmBOn(false);
}

XCLEDALM::~XCLEDALM() {
    // TODO Auto-generated destructor stub
}

void XCLEDALM::display(bool alarm) {
    if( itsSn == 0 ) {
        if( alarm )
            led_sfpalm_a_on();
        else
            led_sfpalm_a_off();
        Driver.turnLedAlmAOn(alarm);
    }
    else {
        if( alarm )
            led_sfpalm_b_on();
        else
            led_sfpalm_b_off();
        Driver.turnLedAlmBOn(alarm);
    }
}
