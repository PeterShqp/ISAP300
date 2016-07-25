/*
 * Card8EOS.cpp
 *
 *  Created on: 2014-3-26
 *      Author: Administrator
 */

#include "Card8EOS.h"
#include "UID.h"
#include "PairRscSDHChannel.h"
#include <string.h>
#include "SysError.h"
#include "CardTypeID_define.h"
#include <stdio.h>
//#include "GeneralLogic.h"
#include "EOS8CardAlarmModule.h"


Card8EOS::Card8EOS(std::string& name, CBaseSlot* slot) : CBaseCard(name, slot),
        cpld(slot), fpga(slot), eos_1(slot, 0x8000), eos_2(slot, 0xa000) {
//	if(GeneralLogic::instance().ifColdStart()){
    Chip_INIT_RESULT rst = fpga.ChipInit();

		if( rst == failed ) {
			throw SysError("!!!Chip 8EOSlogic init failed!!!");
		}
		else if( rst == succeed ) {
            cpld.ChipInit();
            if( (eos_1.ChipInit() == failed) || (eos_2.ChipInit() == failed) ) {
                throw SysError("!!!RC6400 init failed!!!");
            }
		}
		else {
            printf("%s have been running!", fpga.itsName().c_str());
		}
//	}
    if( !fetchConfig() ) {
        throw SysError("!!!Card 8EOS config data error!!!");
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
            chvc_obj[i] = new CHVC(uid, this, linkch, eos_1, eos_2, &ConfigData.chvc[i]);
        }
    }

    ST_VCG vcginfo;
    vcginfo.slot = slot->GetSn();
    for (int i = 0; i < 8; ++i) {
        vcginfo.vcg = i;
        if( i / 4  == 0 ) {
            vcg_obj[i] = new VCG(UID::makeUID(&vcginfo), this, &ConfigData.vcg[i], eos_1);
        }
        else {
            vcg_obj[i] = new VCG(UID::makeUID(&vcginfo), this, &ConfigData.vcg[i], eos_2);
        }
    }

    AM = new EOS8CardAlarmModule(this);
    AM->initModule();
}

Card8EOS::~Card8EOS() {
    delete AM;
    for (int i = 0; i < 126; ++i) {
        delete chvc_obj[i];
    }
    for (int i = 0; i < 8; ++i) {
        delete vcg_obj[i];
    }
}

int Card8EOS::GetCartTypeID() {
    return EOS_8_CARD_TYPEID;
}

void Card8EOS::loadDefaultData(void) {
    CBaseCard::loadDefaultData();
    for (int i = 0; i < 8; ++i) {
        ConfigData.vcg[i].enable = 1;
        ConfigData.vcg[i].lcas = 1;
        ConfigData.VCGAlmData[i].Property[0].level = 1;
    }
}
