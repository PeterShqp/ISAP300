/*
 * Card8EOSN.cpp
 *
 *  Created on: 2014��12��22��
 *      Author: Administrator
 */

#include "Card8EOSN.h"
#include "CardTypeID_define.h"
//#include "GeneralLogic.h"
#include "SysError.h"
#include "UID.h"
#include "PairRscSDHChannel.h"
#include <iostream>
#include "EOS8NCardAlarmModule.h"

Card8EOSN::Card8EOSN(std::string& name, CBaseSlot* slot) : CBaseCard(name, slot),
        cpld(slot), fpga(slot), fpga2(slot), eos_1(slot, 0x8000), eos_2(slot, 0xa000) {
//    if(GeneralLogic::instance().ifColdStart()){
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
            if( (eos_1.ChipInit() == failed) || (eos_2.ChipInit() == failed) ) {
                throw SysError("!!!RC6400 init failed!!!");
            }
        }
        else {
            std::cout << "FPGAS have been running!" << std::endl;
        }
//    }
    if( !fetchConfig() ) {
        throw SysError("!!!Card 8EOS config data error!!!");
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
            chvc_obj[i] = new CHVC(chuid, this, linkch, eos_1, eos_2, &ConfigData.chvc[i]);
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
    for (int i = 0; i < 8; ++i) {
        vcginfo.vcg = i;
        if( (i / 4)  == 0 ) {
            vcg_obj[i] = new VCG(UID::makeUID(&vcginfo), this, &(ConfigData.vcg[i]), eos_1);
        }
        else {
            vcg_obj[i] = new VCG(UID::makeUID(&vcginfo), this, &(ConfigData.vcg[i]), eos_2);
        }
        if( vcg_obj[i] == 0 ) {
            throw SysError("!!!New VCG Error!!!");
        }
    }

    AM = new EOS8NCardAlarmModule(this);
    AM->initModule();
}

Card8EOSN::~Card8EOSN() {
    delete AM;
    for (int i = 0; i < 126; ++i) {
        delete chvc_obj[i];
    }
    for (int i = 0; i < 8; ++i) {
        delete vcg_obj[i];
    }
}


int Card8EOSN::GetCartTypeID() {
    return EOS_8N_CARD_TYPEID;
}

void Card8EOSN::loadDefaultData(void) {
    CBaseCard::loadDefaultData();
    for (int i = 0; i < 8; ++i) {
        ConfigData.vcg[i].enable = 1;
        ConfigData.vcg[i].lcas = 1;
        ConfigData.VCGAlmData[i].Property[0].level = 1;
    }
}
