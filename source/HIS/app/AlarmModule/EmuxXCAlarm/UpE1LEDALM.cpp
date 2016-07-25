/*
 * UpE1LEDALM.cpp
 *
 *  Created on: 2015年6月9日
 *      Author: Administrator
 */

#include "UpE1LEDALM.h"
#include "DriverPCM.h"

UpE1LEDALM::UpE1LEDALM(uint8 sn, DriverPCM& chip) : DisplayMultiSignalOR("E1_LED_ALM"), driver(chip) {

    hid = sn;

}

UpE1LEDALM::~UpE1LEDALM() {
    // TODO Auto-generated destructor stub
}

void UpE1LEDALM::display(bool alarm) {
    driver.turnOnLedAlm(hid, alarm);
}
