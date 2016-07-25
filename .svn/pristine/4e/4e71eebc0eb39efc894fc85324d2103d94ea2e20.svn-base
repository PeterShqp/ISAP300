/*
 * Trib4STM1AlarmModule.cpp
 *
 *  Created on: 2014��9��16��
 *      Author: Administrator
 */

#include "Trib4STM1AlarmModule.h"
#include "SrcTribSTMPort.h"
#include "Card4STM1.h"

TASK void Do_4STM1_LED(void* pxc);

Trib4STM1AlarmModule::Trib4STM1AlarmModule(Card4STM1* c) : BAlarmModule(c) {
    card = c;
    led_alarm = os_tsk_create_ex(Do_4STM1_LED, P_LED, this);

}

Trib4STM1AlarmModule::~Trib4STM1AlarmModule() {
    // TODO Auto-generated destructor stub
}

void Trib4STM1AlarmModule::creatAlarmSource() {
    for (int i = 0; i < 4; ++i) {
        addAlmSrc( new SrcTribSTMPort(this, card->tribstm_obj[i], &(card->ConfigData.AlarmData.STMAlmData[i]), card->fpga2, card->cpld) );
    }
}

void Trib4STM1AlarmModule::turnLedAlarmOn(bool on) {
    card->fpga2.cardLEDAlarmOn(on);
}

TASK void Do_4STM1_LED(void* pxc) {
    Trib4STM1AlarmModule* xc = (Trib4STM1AlarmModule*)pxc;

    while (1) {
        os_dly_wait(100);
        if( xc->ifAlarm() ) {
            xc->turnLedAlarmOn(true);
        }
        else {
            xc->turnLedAlarmOn(false);
        }
    }

}
