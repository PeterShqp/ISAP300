/*
 * SrcAlarmUpE1.cpp
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */

#include "SrcAlarmUpE1.h"
#include "RealPortBase.h"
#include "AlarmInstance.h"
#include "DriverPCM.h"
#include "SysError.h"

SrcAlarmUpE1::SrcAlarmUpE1(uint8 sn, BAlarmModule* m, RealPortBase* port, SrcUpE1Alarm_Data* data, DriverPCM& chip)
        : BAlarmSource(m), driver(chip), ledwork(sn, chip), ledalm(sn, chip) {
    if( m == 0 || port == 0 || data == 0 ) {
        throw SysError("SrcAlarmUpE1 error input para");
    }
    e1 = port;
    SN = sn;
    pConfigData = data;
}

SrcAlarmUpE1::~SrcAlarmUpE1() {
    // TODO Auto-generated destructor stub
}

void SrcAlarmUpE1::makeAlarmSignal(void) {
    addAlmIns( new AlarmInstance(UpE1_Sig_BASE+UpE1_LOS, this, &(pConfigData->Property[UpE1_LOS]), &ledalm) );
    addAlmIns( new AlarmInstance(UpE1_Sig_BASE+UpE1_AIS, this, &(pConfigData->Property[UpE1_AIS]), &ledalm) );
    addAlmIns( new AlarmInstance(UpE1_Sig_BASE+UpE1_LOF, this, &(pConfigData->Property[UpE1_LOF]), &ledalm) );
    addAlmIns( new AlarmInstance(UpE1_Sig_BASE+UpE1_LOMF, this, &(pConfigData->Property[UpE1_LOMF]), &ledalm));
}
bool SrcAlarmUpE1::ifSrcRestrain() {
    return false;
}

bool SrcAlarmUpE1::getAlarm(int type) {
    switch( type-UpE1_Sig_BASE ) {
    case UpE1_LOS:
        driver.turnOnLedWork(SN, !driver.itsLOS(SN));
        if( !e1->ifEnabled() ) {
            return false;
        }
        return driver.itsLOS(SN);
    case UpE1_AIS:
        if( !e1->ifEnabled() ) {
            return false;
        }
        if( driver.itsLOS(SN) ) {
            return false;
        }
        return driver.itsAIS(SN);
    case UpE1_LOF:
        if( !e1->ifEnabled() ) {
            return false;
        }
        if( driver.itsLOS(SN) ) {
            return false;
        }
        return driver.itsLOF(SN);
    case UpE1_LOMF:
        if( !e1->ifEnabled() ) {
            return false;
        }
        if( driver.itsLOS(SN) ) {
            return false;
        }
        return driver.itsLOMF(SN);
    }
    return false;
}
std::string SrcAlarmUpE1::getTypeName(int type) {
    switch( type-UpE1_Sig_BASE ) {
    case UpE1_LOS: {
        std::string name("E1_LOS");
        return name;
	}
    case UpE1_AIS: {
        std::string name("E1_AIS");
        return name;
	}
    case UpE1_LOF: {
        std::string name("E1_LOF");
        return name;
    }
    case UpE1_LOMF: {
        std::string name("E1_LOMF");
        return name;
    }
    }
	std::string name("NONE");
	return name;
}
uint32 SrcAlarmUpE1::itsID(void) {
    return e1->getUID();
}
std::string& SrcAlarmUpE1::itsName(void) {
    return e1->getName();
}
