/*
 * OMUIdle.cpp
 *
 *  Created on: 2014��12��9��
 *      Author: Administrator
 */

#include "OMUIdle.h"
#include "CommunicationModule.h"
#include "SyncFileBakAPI.h"


OMUIdle::OMUIdle() : OMUStatus(10) {
    CommunicationModule::initStandby();
    lockIt(true);
    sync = new SyncFileBakAPI(this);
}

OMUIdle::~OMUIdle() {
    delete sync;
    CommunicationModule::clearStandby();
}

Working_STATE_E OMUIdle::getStatus(void) {
    return OMU_Idle;
}

