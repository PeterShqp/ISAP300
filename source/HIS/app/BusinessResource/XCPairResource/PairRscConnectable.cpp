/*
 * PairRscConnectable.cpp
 *
 *  Created on: 2014��11��25��
 *      Author: Administrator
 */

#include "PairRscConnectable.h"
#include "ConnectableResource.h"
#include <stdio.h>

PairRscConnectable::PairRscConnectable(uint32 uid) : ConnectableResource(uid), pairTool(uid) {
    // TODO Auto-generated constructor stub

}

PairRscConnectable::~PairRscConnectable() {
    // TODO Auto-generated destructor stub
}

int PairRscConnectable::getSpeedLevel(void) {
    std::pair<ConnectableResource*, ConnectableResource*> p = pairTool.getParts<ConnectableResource>();
    if( p.first ) {
        return p.first->getSpeedLevel();
    }
    if( p.second ) {
        return p.second->getSpeedLevel();
    }
    return 0;
}
bool PairRscConnectable::setFrom(int fromHID) {
#ifdef CC_DBG
    printf("\n----PairRscConnectable::setFrom(%4x) \n", fromHID);
#endif
    std::pair<ConnectableResource*, ConnectableResource*> p = pairTool.getParts<ConnectableResource>();
    if( p.first && p.second ) {
        return p.first->setFrom(fromHID) &&
                p.second->setFrom(fromHID);
    }
    else if( p.second ) {
        return p.second->setFrom(fromHID);
    }
    else if( p.first ) {
        return p.first->setFrom(fromHID);
    }
    return false;
}
uint32 PairRscConnectable::getHID() {
    std::pair<ConnectableResource*, ConnectableResource*> p = pairTool.getParts<ConnectableResource>();
    if( p.first ) {
        return p.first->getHID();
    }
    if( p.second ) {
        return p.second->getHID();
    }
    return 0;
}
//uint32 PairRscConnectable::getConnectFrom(void) {
//    std::pair<ConnectableResource*, ConnectableResource*> p = pairTool.getParts<ConnectableResource>();
//    if( p.second && p.first ) {
//        if( p.first->getConnectFrom() == p.second->getConnectFrom() ) {
//            return p.first->getConnectFrom();
//        }
//    }
//    return 0;
//}
