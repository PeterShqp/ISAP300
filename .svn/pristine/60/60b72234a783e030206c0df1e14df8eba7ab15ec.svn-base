/*
 * PairResource.cpp
 *
 *  Created on: 2014Äê11ÔÂ24ÈÕ
 *      Author: Administrator
 */

#include "PairResource.h"
#include "BaseResource.h"
#include "UID.h"

std::map<uint32, PairResource*> PairResource::group;

PairResource::PairResource(uint32 uid) : Resource(uid) {

    group.insert( std::pair<uint32, PairResource*>(uid, this));
    state = Error;
    part0 = 0;
    part1 = 0;
}

PairResource::~PairResource() {
    group.erase(getUID());
}

Pair_Status_E PairResource::getPairStatus() {
    return state;

}

void PairResource::changePairStatus(void) {
    if( part0 == 0 ) {
        if( part1 == 0 ) {
            state = Error;
        }
        else {
            state = Single_B;
        }
    }
    else {
        if( part1 == 0 ) {
            state = Single_A;
        }
        else {
            state = Protected;
        }
    }
}

bool PairResource::foundResource(BaseResource* r) {
    if( r ) {
        if( r->getUID() == getUID() ) {
            part0 = r;
            changePairStatus();
            return true;
        }
        else if( r->getUID() == (UID::getPartnerUID(getUID())) ){
            part1 = r;
            changePairStatus();
            return true;
        }
    }
    return false;
}

bool PairResource::loseResource(BaseResource* r) {
    if( r ) {
        if( r->getUID() == getUID() ) {
            part0 = 0;
            changePairStatus();
            return true;
        }
        else if( r->getUID() == (UID::getPartnerUID(getUID())) ){
            part1 = 0;
            changePairStatus();
            return true;
        }
    }
    return false;
}
