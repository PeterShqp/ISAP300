/*
 * ChannelSabit.cpp
 *
 *  Created on: 2015年11月11日
 *      Author: Administrator
 */

#include "ChannelSabit.h"
#include "UID.h"
#include "DriverPCM.h"
#include "SysError.h"
#include <iostream>

ChannelSabit::ChannelSabit(uint32 uid, DriverPCM& d) : NMChannel(uid), chip(d) {
    try {
        UN_Info info = UID::breakUID(uid);
        hid = info.nm.sn;
    }
    catch(SysError& s) {
        std::cout << s.what() << std::endl;
        return;
    }

}

ChannelSabit::~ChannelSabit() {
    // TODO Auto-generated destructor stub
}

bool ChannelSabit::havePacet(void) {
    return chip.ifSaHavePacket(hid);
}

int ChannelSabit::getPacketLen(void) {
    return chip.getSaPacketLen();
}

bool ChannelSabit::getPacketData(uint8*d, uint16 len, uint16 startPos) {
    if( len == 0 ) {
        len = getPacketLen();
    }
    if( len == 0 ) {
        return false;
    }
    return chip.getSaPacket(d, len, startPos);
}

void ChannelSabit::discardPacket() {
    chip.readSaPacketOver();
}

void ChannelSabit::start(void) {
    chip.setSabitInterruptEnable(hid, 1);
}
void ChannelSabit::stop(void) {
    chip.setSabitInterruptEnable(hid, 0);
}
void ChannelSabit::sendData(uint8* d, uint32 len) {
    chip.sendSaPacket(hid, d, len);
}
