/*
 * XCLEDLOS.cpp
 *
 *  Created on: 2014Äê8ÔÂ15ÈÕ
 *      Author: Administrator
 */

#include "XCLEDLOS.h"
#include "ISAP100LED.h"
#include "ChipXCCPLD.h"

XCLEDLOS::XCLEDLOS(int sn, ChipXCCPLD& d) : DisplayMultiSignalOR("XC_LED_LOS"), Driver(d) {

    itsSn = sn;
    turn_led_sfplos_a(false);
    turn_led_sfplos_b(false);
    Driver.turnLedLosAOn(false);
    Driver.turnLedLosBOn(false);
}

XCLEDLOS::~XCLEDLOS() {
    // TODO Auto-generated destructor stub
}

void XCLEDLOS::display(bool alarm) {
    if( itsSn == 0 ) {
        turn_led_sfplos_a(!alarm);
        Driver.turnLedLosAOn(alarm);
    }
    else {
        turn_led_sfplos_b(!alarm);
        Driver.turnLedLosBOn(alarm);
    }

}
