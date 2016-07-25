/*
 * SrcAlarm16E1.cpp
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#include "SrcAlarm16E1.h"
#include "PortE1.h"

SrcAlarm16E1::SrcAlarm16E1(BAlarmModule* m, PortE1* p, SrcE1Alarm_Data* d, Chip16E1CPLD& cpld, Chip16E1Logic& fpga) :
                                    SrcAlarmE1(m, p, d, led), led(p->getPortSn(), cpld), LedAis(p->getPortSn(), fpga) {
    // TODO Auto-generated constructor stub

}

SrcAlarm16E1::~SrcAlarm16E1() {
    // TODO Auto-generated destructor stub
}

