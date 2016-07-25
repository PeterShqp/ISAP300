/*
 * SwitchPortInner.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "SwitchPortInner.h"
#include "PriPacket.h"
//#include "DCCChannelSnd.h"
//#include "DCCChannelRcv.h"
#include <string.h>

#include <iostream>
#include "DeviceComponent.h"
#include "DeviceAttribute.h"
#include "NMPort.h"

uint32 SwitchPortInner::pSnBase = 255;

SwitchPortInner::SwitchPortInner() : SwitchPort(pSnBase--) {
	// TODO Auto-generated constructor stub
}

SwitchPortInner::SwitchPortInner(uint32 sn) : SwitchPort(sn) {
}


SwitchPortInner::~SwitchPortInner() {
	// TODO Auto-generated destructor stub
}

int SwitchPortInner::outputPacket(PriPacket& pkg) {
    uint32 sn = pkg.getPrivateTag().sn;
    uint16 priLen = pkg.getPriLen();
    ch[0] = sn>>24;
    ch[1] = sn>>16;
    ch[2] = sn>>8;
    ch[3] = sn>>0;
    uint16 len = 0;
    uint8* stdd = pkg.getStdStream(&len);
    if( stdd == 0 || len < 20 ) {
        return -1;
    }
    memcpy( ch+4, stdd, len);
    std::map<uint32, NMPort*>::iterator it = nmport.begin();
    while( it != nmport.end() ) {
        if( pkg.getRcvNMPort()->getUID() != it->second->getUID() ) {
            //只发送非本管理接口收到的包
            it->second->sendData(ch, priLen);
        }
        ++it;
    }

    return 1;
}


//void SwitchPortInner::addDcc(DCCChannelRcv* ch) {
//    dccRcv.insert(std::pair<uint32, DCCChannelRcv*>( ch->getUID(), ch));
//  ch->setInnerPort(this);
//}
//
//void SwitchPortInner::addDcc(DCCChannelSnd* ch) {
//  dccSnd.insert( std::pair<uint32, DCCChannelSnd*>( ch->getUID(), ch) );
//    ch->setInnerPort(this);
//}
//
//void SwitchPortInner::removeDcc(DCCChannelRcv* ch) {
//  ch->setInnerPort(0);
//  dccRcv.erase(ch->getUID());
//}
//void SwitchPortInner::removeDcc(DCCChannelSnd* ch) {
//    ch->setInnerPort(0);
//  dccSnd.erase(ch->getUID());
//}

void SwitchPortInner::addNmPort(NMPort* p) {
    nmport.insert(std::pair<uint32, NMPort*>(p->getUID(), p));
    p->setInnerPort(this);
}
void SwitchPortInner::removePort(NMPort* p) {
    p->setInnerPort(0);
    nmport.erase(p->getUID());
}



bool SwitchPortInner::ifDropThePacket(PriPacket& pkt) {
    uint16 len = 0;
    uint8* databuf = pkt.getStdStream(&len);
    if( databuf == 0 ) {
        return true;
    }
    uint16 frameType =  ((databuf[12] << 8) | databuf[13]);
    if( frameType == 0x0806 ) {
        uint8* ip = databuf + 38; //arp request dest ip address
        uint8 remoteIP[4];
        DeviceComponent::getDeviceAttribute().getProtectMCUIP(remoteIP);
        if( memcmp(ip, remoteIP, 4) == 0 ) {
            return true;
        }
        ip = databuf + 28; //arp request src ip address
        if( memcmp(ip, remoteIP, 4) == 0 ) {
            return true;
        }
    }
    return false;
}
