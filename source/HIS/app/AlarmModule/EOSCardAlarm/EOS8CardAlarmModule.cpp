/*
 * EOS8CardAlarmModule.cpp
 *
 *  Created on: 2014Äê10ÔÂ28ÈÕ
 *      Author: Administrator
 */

#include "EOS8CardAlarmModule.h"
#include "SrcAlarmVCG.h"
#include "Card8EOS.h"

EOS8CardAlarmModule::EOS8CardAlarmModule(Card8EOS* c) : BAlarmModule(c) {

    card = c;

}

EOS8CardAlarmModule::~EOS8CardAlarmModule() {
    // TODO Auto-generated destructor stub
}

void EOS8CardAlarmModule::creatAlarmSource() {
    for (int i = 0; i < 8; ++i) {
        addAlmSrc( new SrcAlarmVCG(this, card->vcg_obj[i], &(card->ConfigData.VCGAlmData[i])) );
    }
}
