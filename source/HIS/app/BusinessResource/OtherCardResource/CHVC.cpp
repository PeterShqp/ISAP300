/*
 * CHVC.cpp
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#include "CHVC.h"
#include "UID.h"
#include "PairRscSDHChannel.h"
#include "CPPTools.h"
#include "VCG.h"
#include "ChipRC6400.h"

std::map<uint32, CHVC*> CHVC::group;

CHVC::CHVC(uint32 uid, ConfigCell* card, PairRscSDHChannel* maplink, ChipRC6400& chip1, ChipRC6400& chip2, CHVC_ConfigData_T* Config)
        : BaseResource(uid, card), Driver1(chip1), Driver2(chip2) {

    group.insert(std::pair<uint32, CHVC*>(uid, this));
    LinkChannel = maplink;
    LinkChannel->setDownStream(uid);
    BandVCG = 0;
    UN_Info info = UID::breakUID(uid);
    sn = info.chvc.channel;
    ConfigData = Config;
    setSNCP(ConfigData->sncp, false);
}

CHVC::~CHVC() {
    LinkChannel->setDownStream(0);
    group.erase(getUID());
}


uint32 CHVC::getDownStream(void) {
    if( BandVCG ) {
        return BandVCG->getUID();
    }
    return 0;
}
uint32 CHVC::getUpStream(void) {
    return LinkChannel->getUID();
}

/*
 * ֻ�аﶨ��VCG��CHVC���ж�Ӧ��RC6400��
 * ����ڰ�ʱ����Ҫ�Ը�CHVC�����������ʵ��
 */
bool CHVC::bandToVCG(VCG* v) {
    BandVCG = v;
    if( BandVCG ) {
        LinkChannel->setDownStream(BandVCG->getUID());
    }
    else {
        LinkChannel->setDownStream(getUID());
    }
    return true;
}

uint32 CHVC::getProtectPartner(void) {
    UN_Info info = UID::breakUID(getUID());
    if( info.chvc.group == 0 ) {
        info.chvc.group = 1;
    }
    else {
        info.chvc.group = 0;
    }
    ST_Chvc_channel partner;
    partner.slot = info.chvc.slot;
    partner.group = info.chvc.group;
    partner.channel = info.chvc.channel;
    return UID::makeUID(&partner);
}

uint32 CHVC::getSNCP(void) {
    return ConfigData->sncp;
}


bool CHVC::setSNCP(uint32 cc, bool save) {
    int en = 0;
    if( cc != 0 ) {
        en = 1;
    }
    if( Driver1.setSNCP(sn, en) && Driver2.setSNCP(sn, en) && save) {
        if( en == 1 ) {
            getInstance(getProtectPartner())->bandToVCG(BandVCG);
        }
        else {
            getInstance(getProtectPartner())->bandToVCG(0);
        }
        if( save ) {
            ConfigData->sncp = cc;
            return saveConfig();
        }
        return true;
    }
    return false;
}
