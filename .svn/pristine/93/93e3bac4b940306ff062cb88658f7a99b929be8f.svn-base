/*
 * PairTSChannel.cpp
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#include "PairTSChannel.h"

std::map<uint32, PairTSChannel*> PairTSChannel::group;

PairTSChannel::PairTSChannel(uint32 uid) : PairRscConnectable(uid) {

    group.insert( std::pair<uint32, PairTSChannel*>(uid, this));
    DownStream = 0;

}

PairTSChannel::~PairTSChannel() {
    group.erase(getUID());
}

