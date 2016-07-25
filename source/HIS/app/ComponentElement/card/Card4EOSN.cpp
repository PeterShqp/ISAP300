/*
 * Card4EOSN.cpp
 *
 *  Created on: 2015年5月16日
 *      Author: Administrator
 */

#include "Card4EOSN.h"
#include "SysError.h"
#include <iostream>
#include "UID.h"
#include "PairRscSDHChannel.h"
#include "CardTypeID_define.h"
#include "EOS4NCardAlarmModule.h"

Card4EOSN::Card4EOSN(std::string& name, CBaseSlot* slot) : CBaseCard(name, slot),
    cpld(slot), fpga(slot), fpga2(slot), eos_1(slot, 0x8000) {
    // TODO Auto-generated constructor stub

    Chip_INIT_RESULT rst = fpga.ChipInit();
    Chip_INIT_RESULT rst2 = fpga2.ChipInit();

        cpld.ChipInit();
        if( rst == failed ) {
            throw SysError("!!!Chip 8EOSlogic1 init failed!!!");
        }
        if( rst2 == failed ) {
            throw SysError("!!!Chip 8EOSlogic2 init failed!!!");
        }
        if( rst == succeed && rst2 == succeed ) {
            if( (eos_1.ChipInit() == failed) ) {
                throw SysError("!!!RC6400 init failed!!!");
            }
        }
        else {
            std::cout << "FPGAS have been running!" << std::endl;
        }
//    }
    if( !fetchConfig() ) {
        throw SysError("!!!Card 4EOS config data error!!!");
    }
    cardversionInfo = cpld.GetVerInfo();

    ST_Chvc_channel chvcinfo = {0};
    ST_Sdh_channel linkInfo = {0};
    chvcinfo.slot = slot->GetSn();
    linkInfo.slot = slot->GetSn();
    linkInfo.xcsn = 0;
    for (int i = 0; i < 126; ++i) {
        chvcinfo.group = i / 63;
        linkInfo.bus = i / 63;
        chvcinfo.channel = i % 63;
        linkInfo.channel = i % 63;
        uint32 linkuid = UID::makeUID(&linkInfo);
        PairRscSDHChannel* linkch = PairRscSDHChannel::getInstance(linkuid);
        if( linkch ) {
            uint32 chuid = UID::makeUID(&chvcinfo);
            chvc_obj[i] = new CHVC(chuid, this, linkch, eos_1, eos_1, &ConfigData.chvc[i]);
            if( chvc_obj[i] == 0 ) {
                throw SysError("!!!New CHVC Error!!!");
            }
        }
        else {
            throw SysError("!!!SDHBUS miss!!!");
        }
    }

    ST_VCG vcginfo;
    vcginfo.slot = slot->GetSn();
    for (int i = 0; i < 4; ++i) {
        vcginfo.vcg = i;
        vcg_obj[i] = new VCG(UID::makeUID(&vcginfo), this, &ConfigData.vcg[i], eos_1);
    }

    AM = new EOS4NCardAlarmModule(this);
    AM->initModule();
}

Card4EOSN::~Card4EOSN() {
    // TODO Auto-generated destructor stub
    delete AM;
    for (int i = 0; i < 126; ++i) {
        delete chvc_obj[i];
    }
    for (int i = 0; i < 4; ++i) {
        delete vcg_obj[i];
    }
}

int Card4EOSN::GetCartTypeID() {
    return EOS_4N_CARD_TYPEID;
}

void Card4EOSN::loadDefaultData(void) {
    CBaseCard::loadDefaultData();
    for (int i = 0; i < 4; ++i) {
        ConfigData.vcg[i].enable = 1;
        ConfigData.vcg[i].lcas = 1;
        ConfigData.VCGAlmData[i].Property[0].level = 1;
    }
}
