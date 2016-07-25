/*
 * BaseResource.cpp
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#include "BaseResource.h"
#include "CBaseCard.h"
#include "UID.h"
//#include "DeviceComponent.h"
#include "XCPair.h"
#include "SysError.h"

BaseResource::BaseResource(uint32 uid, ConfigCell* card, bool paired) : Resource(uid) {
    BelongCard = card;
    Paired = paired;
    if( paired ) {
        XCPair::instance().addResource(this);
    }
}

BaseResource::~BaseResource() {
    if( Paired ) {
        XCPair::instance().removeResource(this);
    }
}

bool BaseResource::saveConfig(void) {
    if( BelongCard ) {
        return BelongCard->saveConfig();
    }
    return false;
}

