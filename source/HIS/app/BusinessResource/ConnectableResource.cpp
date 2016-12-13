/*
 * ConnectableResource.cpp
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#include "ConnectableResource.h"
#include "ComponentFactory.h"
#include <stdio.h>

std::map<uint32, ConnectableResource*> ConnectableResource::mapPort;

ConnectableResource::ConnectableResource(uint32 uid, ConfigCell* c, bool paired) : BaseResource(uid, c, paired) {
    if( (c == 0) || !paired ) {
        mapPort.insert( std::pair<uint32, ConnectableResource*>(uid, this));
    }
	from = 0;

}

ConnectableResource::~ConnectableResource() {
//	std::map<uint32, ConnectableResource*>::iterator it = mapPort.find(itsUID);
//	if( it != mapPort.end() ) {
//		mapPort.erase(it);
//	}
	mapPort.erase(getUID());

}

/*
 * 用于命令配置，自带排重
 */
bool ConnectableResource::connectFrom(ConnectableResource* f) {
#ifdef CC_DBG
    printf("\n---start ConnectableResource %4x::connectFrom(%4x)\n", getUID(), f->getUID());
#endif
    if( from ) {
#ifdef CC_DBG
        printf("\n---have connect\n");
#endif
        return false; // have connect
    }
    if( f ) {
        from = f;
        if( getSpeedLevel() == f->getSpeedLevel() ) {
            return setFrom(f->getHID());
        }
    }
    return false;
}
bool ConnectableResource::connectFrom(uint32 src) {
    ConnectableResource* f = getResrcInstance(src);
    return connectFrom(f);
}

bool ConnectableResource::connectFromForce(uint32 src) {
    ConnectableResource* f = getResrcInstance(src);
    if( f ) {
        from = f;
        if( getSpeedLevel() == f->getSpeedLevel() ) {
            return setFrom(f->getHID());
        }
    }
    return false;
}

bool ConnectableResource::disConnect(void) {
    if( from ) {
        setFrom(-1);
        from = 0;
        return true;
    }
    return false;
}
