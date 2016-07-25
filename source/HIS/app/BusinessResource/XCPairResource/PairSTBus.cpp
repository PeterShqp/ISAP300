/*
 * PairSTBus.cpp
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#include "PairSTBus.h"
#include "PairTSChannel.h"
#include "UID.h"

PairSTBus::PairSTBus(uint32 uid) : PairResource(uid) {
    ST_Time_Slot tsinfo;
    UN_Info info = UID::breakUID(getUID());
    for(int i = 0; i < 32; i++ ) {
        tsinfo.slot = info.stbus.slot;
        tsinfo.xcsn = info.stbus.xcsn;
        tsinfo.E1 = info.stbus.stbus;
        tsinfo.TS = i;
        ts_obj[i] = new PairTSChannel(UID::makeUID(&tsinfo));
    }

}

PairSTBus::~PairSTBus() {
    for (int i = 0; i < 32; ++i) {
        delete ts_obj[i];
    }
}

