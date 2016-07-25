/*
 * RscVC12.cpp
 *
 *  Created on: 2013-11-30
 *      Author: Administrator
 */

#include "RscVC12.h"
#include "UID.h"
#include "CPPTools.h"
#include "DriverSDH.h"
#include "RscVC4.h"

std::map<uint32, RscVC12*> RscVC12::group;

RscVC12::RscVC12(uint32 uid, ConfigCell* card, DriverSDH& chipDriver, bool paired)
        : ConnectableResource(uid, card, paired), driver(chipDriver) {
    // TODO Auto-generated constructor stub
    group.insert( std::pair<uint32, RscVC12*>(uid, this));
    UN_Info info = UID::breakUID(uid);
}

RscVC12::~RscVC12() {
    group.erase(getUID());
}

int RscVC12::getSpeedLevel(void) {
    return 2;
}
bool RscVC12::setFrom(int fromHID) {
    int rtn = 0;
    if( fromHID < 0 ) {
        rtn = driver.connectVC12(-1, -1, (getHID()>>8)& 0x7f, getHID() & 0xff);
    }
    else {
        rtn = driver.connectVC12((fromHID>>8)& 0x7f, fromHID & 0xff, (getHID()>>8)& 0x7f, getHID() & 0xff);
    }
    if( rtn < 0 ) {
        return false;
    }
    return true;
}
uint32 RscVC12::getHID() {
    uint32 uid = getUID();
    uint8 vc4sn =  RscVC4::itsHardwareID(uid);
    uint8 vc12sn = itsHardwareID(uid);
    return (vc4sn << 8) | vc12sn;
}

uint8 RscVC12::itsHardwareID(uint32 uid) {
    UN_Info info = UID::breakUID(uid);

    return info.vc12.lp;
}
