/*
 * Trib8STM1AlarmModule.cpp
 *
 *  Created on: 2014Äê9ÔÂ16ÈÕ
 *      Author: Administrator
 */

#include "Trib8STM1AlarmModule.h"
#include "SrcTribSTMPort.h"
#include "TribSTM1AlarmDataDefine.h"
#include "Card8STM1.h"

Trib8STM1AlarmModule::Trib8STM1AlarmModule(Card8STM1* c) : BAlarmModule(c) {

    card = c;

}

Trib8STM1AlarmModule::~Trib8STM1AlarmModule() {
    // TODO Auto-generated destructor stub
}

void Trib8STM1AlarmModule::creatAlarmSource() {
    for (int i = 0; i < 8; ++i) {
        addAlmSrc( new SrcTribSTMPort(this, card->tribstm_obj[i], &(card->ConfigData.AlarmData.STMAlmData[i]), card->fpga2, card->cpld) );
    }
}
