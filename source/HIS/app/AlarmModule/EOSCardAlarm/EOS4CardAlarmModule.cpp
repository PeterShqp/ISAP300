/*
 * EOS4CardAlarmModule.cpp
 *
 *  Created on: 2014Äê10ÔÂ28ÈÕ
 *      Author: Administrator
 */

#include "EOS4CardAlarmModule.h"
#include "Card4EOS.h"
#include "SrcAlarmVCG.h"

EOS4CardAlarmModule::EOS4CardAlarmModule(Card4EOS* c) : BAlarmModule(c) {
    card = c;

}

EOS4CardAlarmModule::~EOS4CardAlarmModule() {
    // TODO Auto-generated destructor stub
}

void EOS4CardAlarmModule::creatAlarmSource() {
    for (int i = 0; i < 4; ++i) {
        addAlmSrc( new SrcAlarmVCG(this, card->vcg_obj[i], &(card->ConfigData.VCGAlmData[i])) );
    }
}
