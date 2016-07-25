/*
 * PairRscSDHChannel.cpp
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#include "PairRscSDHChannel.h"


std::map<uint32, PairRscSDHChannel*> PairRscSDHChannel::group;

PairRscSDHChannel::PairRscSDHChannel(uint32 uid) : PairRscConnectable(uid) {

    group.insert( std::pair<uint32, PairRscSDHChannel*>(uid, this));
    downStream = 0;

}

PairRscSDHChannel::~PairRscSDHChannel() {
    group.erase(getUID());
}

