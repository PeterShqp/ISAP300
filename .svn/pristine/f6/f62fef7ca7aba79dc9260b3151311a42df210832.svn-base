/*
 * FE1CardAlarmModule.cpp
 *
 *  Created on: 2015年6月24日
 *      Author: Administrator
 */

#include "FE1CardAlarmModule.h"
#include "SrcAlarmUpE1.h"
#include "PortFE1.h"

FE1CardAlarmModule::FE1CardAlarmModule(Card16FE1* c) : BAlarmModule(c) {
    // TODO Auto-generated constructor stub
    card = c;
}

FE1CardAlarmModule::~FE1CardAlarmModule() {
    // TODO Auto-generated destructor stub
}

void FE1CardAlarmModule::creatAlarmSource() {
    for (int i = 0; i < 16; ++i) {
        addAlmSrc( new SrcAlarmUpE1(i, this, dynamic_cast<RealPortBase*>(card->fe1_obj[i]),
                &(card->ConfigData.AlarmData.UpE1AlmData[i]), card->fpga ) );
    }
}
