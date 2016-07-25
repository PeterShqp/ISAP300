/*
 * EOS4NCardAlarmModule.cpp
 *
 *  Created on: 2015年5月18日
 *      Author: Administrator
 */

#include "EOS4NCardAlarmModule.h"
#include "Card4EOSN.h"
#include "SrcAlarmVCG.h"

EOS4NCardAlarmModule::EOS4NCardAlarmModule(Card4EOSN* c) : BAlarmModule(c) {
    card = c;

}

EOS4NCardAlarmModule::~EOS4NCardAlarmModule() {
    // TODO Auto-generated destructor stub
}

void EOS4NCardAlarmModule::creatAlarmSource() {
    for (int i = 0; i < 4; ++i) {
        addAlmSrc( new SrcAlarmVCG(this, card->vcg_obj[i], &(card->ConfigData.VCGAlmData[i])) );
    }
}
