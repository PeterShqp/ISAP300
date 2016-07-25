/*
 * PortE1.cpp
 *
 *  Created on: 2014-3-25
 *      Author: Administrator
 */

#include "PortE1.h"
#include "ChipRC7883.h"
#include "UID.h"
#include <string.h>
#include "PairRscSDHChannel.h"
#include "CPPTools.h"

std::map<uint32, PortE1*> PortE1::group;

PortE1::PortE1(uint32 uid, PairRscSDHChannel* mapLink, ConfigCell* card, ChipRC7883& dri, UE1_Config_Data_T* config)
        : RealPortBase(uid,card), driver(dri) {

    group.insert(std::pair<uint32, PortE1*>(uid, this));
    ConfigData = config;
    mapLink->setDownStream(uid);
    MappingCh = mapLink;

}

PortE1::~PortE1() {
    if( MappingCh )
        MappingCh->setDownStream(0);
    group.erase(getUID());
}

int PortE1::getEnable(void) {
    return ConfigData->enable;
}
bool PortE1::setEnable(int en, bool save) {
    int sn = getPortSn();
    if( driver.setPortEnable(sn, en) && save ) {
        ConfigData->enable = en;
        return saveConfig();
    }
    return false;
}

char* PortE1::getDescription(uint32* len) {
    if( len ) {
        *len = ConfigData->dlen;
    }
    return ConfigData->desc;
}
bool PortE1::setDescription(char* s, uint32 len, bool save) {
    memcpy( ConfigData->desc, s, len );
    ConfigData->dlen = len;
    if( save ) {
        return saveConfig();
    }
    return true;
}
/*
 * ÿһ��7883ֻ�ܳ�24·������FPGA����63��ʱ϶�ġ�
 */
int PortE1::getPortSn() {
    UN_Info info = UID::breakUID(getUID());
    return info.E1.E1 % 24;
}
int PortE1::getPortSlot() {
    UN_Info info = UID::breakUID(getUID());
    return info.E1.slot;
}

uint32 PortE1::getMappingLinkUID(void) {
    if( MappingCh ) {
        return MappingCh->getUID();
    }
    return 0;
}

uint32 PortE1::getProtectPartner(void) {
//    return UID::getPartnerUID(getMappingLinkUID());
//
    UN_Info info = UID::breakUID(getMappingLinkUID());
    info.sdhch.bus ^= 1;
    ST_Sdh_channel partner;
    partner.slot = info.sdhch.slot;
    partner.bus = info.sdhch.bus;
    partner.channel = info.sdhch.channel;
    partner.xcsn = info.sdhch.xcsn;
    return UID::makeUID(&partner);
}

int PortE1::setLoop(const int type) {
    switch( type ) {
    case dev_and_line_loop:
        driver.setPortLoopOutAndIn(getPortSn());
        break;
    case dev_loop:
        driver.setPortLoopInOnly(getPortSn());
        break;
    case line_loop:
        driver.setPortLoopOutOnly(getPortSn());
        break;
    case no_loop:
        driver.setPortLoopClear(getPortSn());
        break;
    }
    return 0x5A;
}

uint8* PortE1::getSNCP(uint32* len) {
    *len = 8;
    return ConfigData->sncp;
}
bool PortE1::setSNCP(uint8* cc, uint32 len, bool save) {
    int en = 1;
    uint8 cmp[8] = {0};
    if( memcmp(cc, cmp, 8) == 0 ) {
        en = 0;
    }
    if( driver.setSNCP(getPortSn(), en) ) {
        if( en == 1 ) {
            PairRscSDHChannel::getInstance(getProtectPartner())->setDownStream(getUID());
        }
        else {
            PairRscSDHChannel::getInstance(getProtectPartner())->setDownStream(0);
        }
        if( save ) {
            memcpy(ConfigData->sncp, cc, 8);
            return saveConfig();
        }
        return 0x5A;
    }
    return false;
}

bool PortE1::getLos(void) {
    if( getEnable() == 0 ) {
        return false;
    }
    return driver.getE1Los(getPortSn());
}
