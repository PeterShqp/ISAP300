/*
 * ChannelDcc.cpp
 *
 *  Created on: 2017年6月30日
 *      Author: Shi
 */

#include "ChannelDcc.h"
#include "SysError.h"
#include <iostream>
#include "UID.h"

ChannelDcc::ChannelDcc(uint32 uid, DriverPCM& d) : NMChannel(uid), chip(d) {
	// TODO Auto-generated constructor stub
    try {
        UN_Info info = UID::breakUID(uid);
        uint8 chid = info.nm.sn;
        if( chid == 0 ) {
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

ChannelDcc::~ChannelDcc() {
	// TODO Auto-generated destructor stub
}

bool ChannelDcc::havePacet(void) {
    return chip.ifHavePacket(hid);
}

int ChannelDcc::getPacketLen(void) {
    return chip.getPacketLen(hid);
}

bool ChannelDcc::getPacketData(uint8*d, uint16 len, uint16 startPos) {
    if( len == 0 ) {
        len = chip.getPacketLen(hid);
    }
    if( len == 0 ) {
        return false;
    }
    return chip.GetDCCPacket(hid, d, len, startPos);
}

void ChannelDcc::discardPacket() {
    chip.clearDccRdBufForce(hid);
}

void ChannelDcc::start(void) {
}
void ChannelDcc::stop(void) {
}
void ChannelDcc::sendData(uint8* d, uint32 len) {
    chip.DccSendPacket(hid, d, len);
}

