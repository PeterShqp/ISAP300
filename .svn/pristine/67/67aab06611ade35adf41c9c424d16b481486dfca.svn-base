/*
 * PairRscVC12.cpp
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#include "PairRscVC12.h"

std::map<uint32, PairRscVC12*> PairRscVC12::group;

PairRscVC12::PairRscVC12(uint32 uid) : PairRscConnectable(uid) {
    group.insert( std::pair<uint32, PairRscVC12*>(uid, this));

}

PairRscVC12::~PairRscVC12() {
    group.erase(getUID());
}

