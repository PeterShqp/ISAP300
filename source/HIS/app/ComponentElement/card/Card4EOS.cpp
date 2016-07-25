/*
 * Card4EOS.cpp
 *
 *  Created on: 2014Äê10ÔÂ24ÈÕ
 *      Author: Administrator
 */

#include "Card4EOS.h"
#include "UID.h"
#include "PairRscSDHChannel.h"
#include <string.h>
#include "SysError.h"
#include "CardTypeID_define.h"
#include <stdio.h>
#include "GeneralLogic.h"
#include "EOS4CardAlarmModule.h"

Card4EOS::Card4EOS(std::string& name, CBaseSlot* slot) : CBaseCard(name, slot),
                                                         cpld(slot), fpga(slot), eos_1(slot, 0x8000) {
//    if(GeneralLogic::instance().ifColdStart()){
    Chip_INIT_RESULT rst = fpga.ChipInit();
        if( rst == failed ) {
            throw SysError("!!!Chip 4EOSlogic init failed!!!");
        }
        else if( rst == succeed ) {
            cpld.ChipInit();

            if( eos_1.ChipInit() == failed ) {
                throw SysError("!!!RC6400 init failed!!!");
            }
        }
        else {
            printf("%s have been running!", fpga.itsName().c_str());
        }
//    }
    if( !fetchConfig() ) {
        throw SysError("!!!Card 4EOS config data error!!!");
    }
    cardversionInfo = cpld.GetVerInfo();

    ST_Chvc_channel chvcinfo = {0};
    ST_Sdh_channel linkInfo = {0};
    chvcinfo.slot = linkInfo.slot = slot->GetSn();
    for (int i = 0; i < 126; ++i) {
        chvcinfo.group = linkInfo.bus = i / 63;
        chvcinfo.channel = linkInfo.channel = i % 63;
        uint32 uid = UID::makeUID(&linkInfo);
        PairRscSDHChannel* linkch = PairRscSDHChannel::getInstance(uid);
        if( linkch ) {
            uid = UID::makeUID(&chvcinfo);
            chvc_obj[i] = new CHVC(uid, this, linkch, eos_1, eos_1, &ConfigData.chvc[i]);
        }
    }

    ST_VCG vcginfo;
    vcginfo.slot = slot->GetSn();
    for (int i = 0; i < 4; ++i) {
        vcginfo.vcg = i;
        vcg_obj[i] = new VCG(UID::makeUID(&vcginfo), this, &ConfigData.vcg[i], eos_1);
    }

    AM = new EOS4CardAlarmModule(this);
    AM->initModule();
}

Card4EOS::~Card4EOS() {
    delete AM;
    for (int i = 0; i < 126; ++i) {
        delete chvc_obj[i];
    }
    for (int i = 0; i < 4; ++i) {
        delete vcg_obj[i];
    }
}

int Card4EOS::GetCartTypeID() {
    return EOS_4_CARD_TYPEID;
}

void Card4EOS::loadDefaultData(void) {
    CBaseCard::loadDefaultData();
    for (int i = 0; i < 4; ++i) {
        ConfigData.vcg[i].enable = 1;
        ConfigData.vcg[i].lcas = 1;
        ConfigData.VCGAlmData[i].Property[0].level = 1;
    }
}
