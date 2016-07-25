/*
 * RealPortBase.cpp
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#include "RealPortBase.h"


std::map<uint32, RealPortBase*> RealPortBase::mapPort;

RealPortBase::RealPortBase(uint32 uid, ConfigCell* card, bool paired) : BaseResource(uid, card, paired) {
	mapPort.insert( std::pair<uint32, RealPortBase*>(getUID(), this));

}

RealPortBase::~RealPortBase() {
	mapPort.erase(getUID());

}

