/*
 * PairRscSDHBus.cpp
 *
 *  Created on: 2014Äê11ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "PairRscSDHBus.h"
#include "UID.h"
#include "PairRscSDHChannel.h"

std::map<uint32, PairRscSDHBus*> PairRscSDHBus::group;

PairRscSDHBus::PairRscSDHBus(uint32 uid) : PairRscConnectable(uid) {

    group.insert( std::pair<uint32, PairRscSDHBus*>(uid, this));

    UN_Info info = UID::breakUID(uid);
    ST_Sdh_channel chinfo;
    chinfo.slot = info.sdhbus.slot;
    chinfo.bus = info.sdhbus.sdhbus;
    chinfo.xcsn = info.sdhbus.xcsn;
    for( int i = 0; i < 63; i++ ) {
        chinfo.channel = i;
        uint32 chuid = UID::makeUID(&chinfo);
        sdhch_obj[i] = new PairRscSDHChannel(chuid);
    }
}

PairRscSDHBus::~PairRscSDHBus() {
    for( int i = 0; i < 63; i++ ) {
        delete sdhch_obj[i];
    }
    group.erase(getUID());
}

