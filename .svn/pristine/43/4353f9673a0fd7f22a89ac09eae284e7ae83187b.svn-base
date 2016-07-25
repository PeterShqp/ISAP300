/*
 * PairPortFE1.cpp
 *
 *  Created on: 2015年7月4日
 *      Author: Administrator
 */

#include "PairPortFE1.h"
#include "PortFE1.h"

std::map<uint32, PairPortFE1*> PairPortFE1::group;

PairPortFE1::PairPortFE1(uint32 uid) : PairResource(uid) {
    group.insert( std::pair<uint32, PairPortFE1*>(uid, this));

}

PairPortFE1::~PairPortFE1() {
    group.erase(getUID());
}

uint8 PairPortFE1::getPortEnable(void) {
    std::pair<PortFE1*, PortFE1*> p = getParts<PortFE1>();
    if( p.first ) {
        return p.first->getPortEnable();
    }
    if( p.second ) {
        return p.second->getPortEnable();
    }
    return 0;
}
bool PairPortFE1::setPortEnable(uint8 en) {
    std::pair<PortFE1*, PortFE1*> p = getParts<PortFE1>();
    if( p.first && p.second ) {
        return p.first->setPortEnable(en) &&
                p.second->setPortEnable(en);
    }
    else if( p.second ) {
        return p.second->setPortEnable(en);
    }
    else if( p.first ) {
        return p.first->setPortEnable(en);
    }
    return false;

}

char* PairPortFE1::getDescription(uint32* len) {
    std::pair<PortFE1*, PortFE1*> p = getParts<PortFE1>();
    if( p.first && p.second ) {
        return p.first->getDescription(len);
    }
    else if( p.second ) {
        return p.second->getDescription(len);
    }
    else if( p.first ) {
        return p.first->getDescription(len);
    }
    return 0;
}
bool PairPortFE1::setDescription(char* s, uint32 len) {
    std::pair<PortFE1*, PortFE1*> p = getParts<PortFE1>();
    if( p.first && p.second ) {
        return p.first->setDescription(s, len) &&
                p.second->setDescription(s, len);
    }
    else if( p.second ) {
        return p.second->setDescription(s, len);
    }
    else if( p.first ) {
        return p.first->setDescription(s, len);
    }
    return false;
}
