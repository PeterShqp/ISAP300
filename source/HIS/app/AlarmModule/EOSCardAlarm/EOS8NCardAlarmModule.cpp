/*
 * EOS8NCardAlarmModule.cpp
 *
 *  Created on: 2015年5月18日
 *      Author: Administrator
 */

#include "EOS8NCardAlarmModule.h"
#include "SrcAlarmVCG.h"
#include "Card8EOSN.h"

EOS8NCardAlarmModule::EOS8NCardAlarmModule(Card8EOSN* c) : BAlarmModule(c) {

    card = c;

}

EOS8NCardAlarmModule::~EOS8NCardAlarmModule() {
    // TODO Auto-generated destructor stub
}

void EOS8NCardAlarmModule::creatAlarmSource() {
    for (int i = 0; i < 8; ++i) {
        addAlmSrc( new SrcAlarmVCG(this, card->vcg_obj[i], &(card->ConfigData.VCGAlmData[i])) );
    }
}
