/*
 * OMUStandby.cpp
 *
 *  Created on: 2014��11��27��
 *      Author: Administrator
 */

#include "OMUStandby.h"
#include "CommunicationModule.h"
#include "SyncFileBakAPI.h"
#include "GeneralLogic.h"
#include "SoftWDT.h"

OMUStandby::OMUStandby() : OMUStatus(200) {
    CommunicationModule::initStandby();
    lockIt(false);
    GeneralLogic::instance().setWarmStartType();
    sync = new SyncFileBakAPI(this);
}

OMUStandby::~OMUStandby() {
    delete sync;
    SoftWDT::instance().stopSoftWDT(); //关闭软狗
    CommunicationModule::clearStandby();
}

