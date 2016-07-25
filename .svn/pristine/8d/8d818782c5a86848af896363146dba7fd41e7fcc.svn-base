/*
 * Slot155Channel.cpp
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#include "Slot155Channel.h"
#include "UID.h"
#include "PairRscSDHChannel.h"
#include "DriverSDH.h"
#include "CPPTools.h"

std::map<uint32, Slot155Channel*> Slot155Channel::group;

Slot155Channel::Slot155Channel(uint32 uid, PairRscSDHChannel* mapLink, ConfigCell* card, DriverSDH& d) : ConnectableResource(uid, card), driver(d) {

    group.insert(std::pair<uint32, Slot155Channel*>(uid, this));

    mapLink->setDownStream(uid);
    MappingCh = mapLink;
}

Slot155Channel::~Slot155Channel() {
    MappingCh->setDownStream(0);
    group.erase(getUID());
}


uint32 Slot155Channel::getDownStream(void) {

    return getConnectFrom();
}
uint32 Slot155Channel::getUpStream(void) {
    return MappingCh->getUID();
}

bool Slot155Channel::setFrom(int fromHID) { // if fromHID < 0, disconnect
    int rtn = 0;
    if( fromHID < 0 ) {
        MappingCh->setDownStream(getUID());
        rtn = driver.connectVC12(-1, -1, (getHID()>>8)& 0x7f, getHID() & 0xff);
    }
    else {
        MappingCh->setDownStream(getDownStream());
        rtn = driver.connectVC12((fromHID>>8)& 0x7f, fromHID & 0xff, (getHID()>>8)& 0x7f, getHID() & 0xff);
    }
    if( rtn < 0 ) {
        return false;
    }
    return true;
}

uint32 Slot155Channel::getHID() {
    uint32 uid = getUID();
    UN_Info info = UID::breakUID(uid);
    uint8 vc4sn =  info.sltch.group;
    uint8 vc12sn = info.sltch.channel;
    return (vc4sn << 8) | vc12sn;
}
