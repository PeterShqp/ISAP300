/*
 * UpE1LEDWork.cpp
 *
 *  Created on: 2015年6月9日
 *      Author: Administrator
 */

#include "UpE1LEDWork.h"
#include "DriverPCM.h"

UpE1LEDWork::UpE1LEDWork(uint8 sn, DriverPCM& chip) : DisplayMultiSignalOR("E1_LED_WORK"), driver(chip) {

    hid = sn;

}

UpE1LEDWork::~UpE1LEDWork() {
    // TODO Auto-generated destructor stub
}

void UpE1LEDWork::display(bool alarm) {
    driver.turnOnLedWork(hid, !alarm);
}
