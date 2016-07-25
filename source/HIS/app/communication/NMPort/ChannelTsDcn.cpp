/*
 * ChannelTsDcn.cpp
 *
 *  Created on: 2015年11月11日
 *      Author: Administrator
 */

#include "ChannelTsDcn.h"
#include "DriverPCM.h"
#include "UID.h"
 
ChannelTsDcn::ChannelTsDcn(uint32 uid, DriverPCM& d) : NMChannel(uid), chip(d) {
    UN_Info info = UID::breakUID(uid);
    hid = info.nm.sn;
}

ChannelTsDcn::~ChannelTsDcn() {
    // TODO Auto-generated destructor stub
}

bool ChannelTsDcn::havePacet(void) {
    return chip.ifDcnHavePacket(hid);
}

int ChannelTsDcn::getPacketLen(void) {
    return chip.getDcnPacketLen(hid);
}

bool ChannelTsDcn::getPacketData(uint8*d, uint16 len, uint16 startPos) {

    return chip.getDcnPacket(hid, d, len);
}

void ChannelTsDcn::discardPacket() {
    chip.readDcnPacketOver(hid);
}

void ChannelTsDcn::start(void) {
    if(getTSMap() == 0) {
        return; //如果无可用时隙，则不打开dcn通道
    }
    chip.setDcnInterruptEnable(hid, 1);
}
void ChannelTsDcn::stop(void) {
    setTSMap(0); //dcn 停止时必须清除所占时隙
    chip.setDcnInterruptEnable(hid, 0);
}
void ChannelTsDcn::sendData(uint8* d, uint32 len) {
    chip.sendDcnPacket(hid, d, len);
}

bool ChannelTsDcn::setTSMap(uint32 tsmap) {
    return chip.selectDcnTs(hid, tsmap);
}
uint32 ChannelTsDcn::getTSMap(void) {
    return chip.getDcnTsMap(hid);
}
