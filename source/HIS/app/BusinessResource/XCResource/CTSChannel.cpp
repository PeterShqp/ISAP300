/*
 * CTSChannel.cpp
 *
 *  Created on: 2014-2-18
 *      Author: Administrator
 */

#include "CTSChannel.h"
#include "DriverPCM.h"
#include "UID.h"

std::map<uint32, CTSChannel*> CTSChannel::group;

CTSChannel::CTSChannel(uint32 uid, ConfigCell* card, DriverPCM* dri, bool paired) : ConnectableResource(uid, card, paired) {
    group.insert( std::pair<uint32, CTSChannel*>(uid, this));
    driver = dri;
}

CTSChannel::~CTSChannel() {
    group.erase(getUID());
}

//std::string& CTSChannel::getName(void) {
//    return name;
//}
int CTSChannel::getSpeedLevel(void) {
    return 64;
}
bool CTSChannel::setFrom(int fromHID) {
    uint32 tohid = getHID();
    if( fromHID < 0 ) {
        return driver->RemoveCrossConnection(tohid >> 8, tohid & 0xff);
    }
	return driver->CreatCrossConnection(tohid >> 8, tohid & 0xff, fromHID >> 8, fromHID & 0xff);
}
uint32 CTSChannel::getHID() {
    uint32 uid = getUID();
    return driver->getHID(uid);

}
