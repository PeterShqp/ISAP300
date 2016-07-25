/*
 * RscSDHBus.cpp
 *
 *  Created on: 2013-11-28
 *      Author: Administrator
 */

#include "RscSDHBus.h"
#include "CPPTools.h"
#include "UID.h"
#include "CardXC.h"
#include "ChipCP1121A.h"
#include "RscSDHChannel.h"

std::map<uint32, RscSDHBus*> RscSDHBus::group;

RscSDHBus::RscSDHBus(uint32 uid, ConfigCell* card, ChipCP1121A& chipDriver, bool paired)
        : ConnectableResource(uid, card, paired), driver(chipDriver) {
    group.insert( std::pair<uint32, RscSDHBus*>(uid, this));

    UN_Info info = UID::breakUID(uid);
    ST_Sdh_channel chinfo;
    chinfo.slot = info.sdhbus.slot;
    chinfo.bus = info.sdhbus.sdhbus;
    chinfo.xcsn = info.sdhbus.xcsn;
    for( int i = 0; i < 63; i++ ) {
        chinfo.channel = i;
        uint32 chuid = UID::makeUID(&chinfo);
        sdhch_obj[i] = new RscSDHChannel(chuid, card, chipDriver, paired);
    }

}

RscSDHBus::~RscSDHBus() {
    for( int i = 0; i < 63; i++ ) {
        delete sdhch_obj[i];
    }
    group.erase(getUID());
}

int RscSDHBus::getSpeedLevel(void) {
    return 155;
}
bool RscSDHBus::setFrom(int fromHID) {

    int rtn = driver.connectVC4(fromHID, getHID());
    if( rtn < 0 ) {
        return false;
    }
    return true;
}
uint32 RscSDHBus::getHID() {
    uint32 uid = getUID();
    return itsHardwareID(uid);
}

uint8 RscSDHBus::itsHardwareID(uint32 uid) {
    static uint8 slotbusmap[] = {16, 16, 8, 9, 0, 10, 11};
    static uint8 secondbusoffset[] = {1, 1, 4, 4, 0, 4, 4};
    UN_Info info = UID::breakUID(uid);
    uint8 slot = info.sdhbus.slot;
    uint8 sn = info.sdhbus.sdhbus;

    return slotbusmap[slot] + sn * secondbusoffset[slot];
}

