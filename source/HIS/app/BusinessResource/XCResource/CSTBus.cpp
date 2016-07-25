/*
 * CSTBus.cpp
 *
 *  Created on: 2013-12-16
 *      Author: Administrator
 */

#include "CSTBus.h"
#include "CTSChannel.h"
#include "UID.h"
#include "DriverPCM.h"
#include "CPPTools.h"

std::map<uint32, CSTBus*> CSTBus::group;

CSTBus::CSTBus(uint32 uid, ConfigCell* card, DriverPCM* driver, bool paired) : BaseResource(uid, card, paired) {
    ST_Time_Slot tsinfo;
    group.insert(std::pair<uint32, CSTBus*>(uid,this));
    UN_Info info = UID::breakUID(getUID());
//    chip = driver;
//    name = "STBUS-" + CPPTools::number2string(info.stbus.stbus);
    uint32 userID = 0;
    for(int i = 0; i < 32; i++ ) {
        tsinfo.slot = info.stbus.slot;
        tsinfo.xcsn = info.stbus.xcsn;
        tsinfo.E1 = info.stbus.stbus;
        tsinfo.TS = i;
        userID = UID::makeUID(&tsinfo);
        ts_obj[i] = new CTSChannel(userID, card, driver, paired);
    }
}

CSTBus::~CSTBus() {
    for(int i = 0; i < 32; i++ ) {
        delete ts_obj[i];
    }
    group.erase(getUID());

}

//bool CSTBus::getLOS() {
//    UN_Info e1info = UID::breakUID(getUID());
//    return chip->itsLOS(e1info.stbus.stbus);
//}
//
//bool CSTBus::getAIS() {
//    if( getLOS() ) {
//        return false;
//    }
//    UN_Info e1info = UID::breakUID(getUID());
//    return chip->itsAIS(e1info.stbus.stbus);
//}
//bool CSTBus::getLOF() {
//    if( getLOS() ) {
//        return false;
//    }
//    UN_Info e1info = UID::breakUID(getUID());
//    return chip->itsLOF(e1info.stbus.stbus);
//}
//bool CSTBus::getLOMF() {
//    if( getLOS() ) {
//        return false;
//    }
//    UN_Info e1info = UID::breakUID(getUID());
//    return chip->itsLOMF(e1info.stbus.stbus);
//}
