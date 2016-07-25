/*
 * RscSDHChannel.cpp
 *
 *  Created on: 2013-11-28
 *      Author: Administrator
 */

#include "RscSDHChannel.h"
#include "CardXC.h"
#include "ChipCP1121A.h"
#include "UID.h"
#include "CPPTools.h"
#include "RscSDHBus.h"

std::map<uint32, RscSDHChannel*> RscSDHChannel::group;

RscSDHChannel::RscSDHChannel(uint32 uid, ConfigCell* card, ChipCP1121A& chipDriver, bool paired = false)
        : ConnectableResource(uid, card, paired), driver(chipDriver) {
    group.insert( std::pair<uint32, RscSDHChannel*>(uid, this));

//    downStream = 0;
}

RscSDHChannel::~RscSDHChannel() {
    group.erase(getUID());
}

int RscSDHChannel::getSpeedLevel(void) {
    return 2;
}
bool RscSDHChannel::setFrom(int fromHID) {
    uint32 hid = getHID();
    int rtn = 0;
    if( fromHID < 0 ) {
        rtn = driver.connectVC12(-1, -1, hid >> 8, hid & 0xff);
    }
    else {
        rtn = driver.connectVC12( fromHID >> 8, fromHID & 0xff, hid >> 8, hid & 0xff);
    }
    if( rtn < 0 ) {
        return false;
    }
    return true;
}
uint32 RscSDHChannel::getHID() {//硬件ID包含总线号和通道号。
    uint32 uid = getUID();
    uint8 busSn = RscSDHBus::itsHardwareID(uid);
    uint8 chsn = itsHardwareID(uid);
    return (busSn << 8) | chsn;
}

uint8 RscSDHChannel::itsHardwareID(uint32 uid) {
    UN_Info info = UID::breakUID(uid);
    return info.sdhch.channel;
}
