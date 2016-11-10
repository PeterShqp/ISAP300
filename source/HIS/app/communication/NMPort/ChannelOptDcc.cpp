/*
 * ChannelOptDcc.cpp
 *
 *  Created on: 2016年10月24日
 *      Author: Administrator
 */

#include "ChannelOptDcc.h"
#include "UID.h"
#include "DriverPCM.h"
#include "SysError.h"
#include <iostream>

ChannelOptDcc::ChannelOptDcc(uint32 uid, DriverPCM& d) : NMChannel(uid), chip(d) {
    try {
        UN_Info info = UID::breakUID(uid);
        if( info.nm.sn == 0 ) {
            hid = DCC_A;
        }
        else {
            hid = DCC_B;
        }
    }
    catch(SysError& s) {
        std::cout << s.what() << std::endl;
        return;
    }

}

ChannelOptDcc::~ChannelOptDcc() {
    // TODO Auto-generated destructor stub
}

bool ChannelOptDcc::havePacet(void) {
    return chip.ifHavePacket(hid);
}

int ChannelOptDcc::getPacketLen(void) {
    return chip.getPacketLen(hid);
}

bool ChannelOptDcc::getPacketData(uint8*d, uint16 len, uint16 startPos) {
    if( len == 0 ) {
        len = getPacketLen();
    }
    if( len == 0 ) {
        return false;
    }
    return chip.GetDCCPacket(hid, d, len, startPos);
}

void ChannelOptDcc::discardPacket() {
    chip.clearDccRdBufForce(hid);
}

void ChannelOptDcc::start(void) {
}
void ChannelOptDcc::stop(void) {
}
void ChannelOptDcc::sendData(uint8* d, uint32 len) {
    chip.DccSendPacket(hid, d, len);
}
