/*
 * SrcAlarmVC4.cpp
 *
 *  Created on: 2014Äê9ÔÂ5ÈÕ
 *      Author: Administrator
 */

#include "SrcAlarmVC4.h"
#include "XCAlarmDataDefine.h"
#include "AlarmInstance.h"
#include "RscVC4.h"

SrcAlarmVC4::SrcAlarmVC4(BAlarmModule* m, RscVC4* vc4, SrcVC4Alarm_Data* data) : BAlarmSource(m) {
    port = vc4;
    pConfigData = data;

}

SrcAlarmVC4::~SrcAlarmVC4() {
    // TODO Auto-generated destructor stub
}

void SrcAlarmVC4::makeAlarmSignal(void) {
    addAlmIns( new AlarmInstance(VC4_Sig_BASE+AU_AIS, this, &(pConfigData->Property[AU_AIS])) );
    addAlmIns( new AlarmInstance(VC4_Sig_BASE+AU_LOP, this, &(pConfigData->Property[AU_LOP])) );
    addAlmIns( new AlarmInstance(VC4_Sig_BASE+HP_RDI, this, &(pConfigData->Property[HP_RDI])) );
    addAlmIns( new AlarmInstance(VC4_Sig_BASE+HP_REI, this, &(pConfigData->Property[HP_REI])) );
    addAlmIns( new AlarmInstance(VC4_Sig_BASE+HP_TIM, this, &(pConfigData->Property[HP_TIM])) );
    addAlmIns( new AlarmInstance(VC4_Sig_BASE+HP_SLM, this, &(pConfigData->Property[HP_SLM])) );
    addAlmIns( new AlarmInstance(VC4_Sig_BASE+HP_UNEQ, this, &(pConfigData->Property[HP_UNEQ])) );
}


bool SrcAlarmVC4::ifSrcRestrain() {
    return false;
}

bool SrcAlarmVC4::getAlarm(int type) {
    switch( type - VC4_Sig_BASE ) {
    case AU_AIS:
        return port->getAUAIS();
    case AU_LOP:
        return port->getAULOP();
    case HP_RDI:
        return port->getHPRDI();
    case HP_REI:
        return port->getHPREI();
    case HP_TIM:
        return port->getHPTIM();
    case HP_SLM:
        return port->getHPSLM();
    case HP_UNEQ:
        return port->getHPUNEQ();
    }
    return false;
}

std::string SrcAlarmVC4::getTypeName(int type) {
    switch( type-VC4_Sig_BASE ) {
    case AU_AIS: {
        std::string name("AU_AIS");
        return name;
    }
    case AU_LOP: {
        std::string name("AU_LOP");
        return name;
    }
    case HP_RDI: {
        std::string name("HP_RDI");
        return name;
    }
    case HP_REI: {
        std::string name("HP_REI");
        return name;
    }
    case HP_TIM: {
        std::string name("HP_TIM");
        return name;
    }
    case HP_SLM: {
        std::string name("HP_SLM");
        return name;
    }
    case HP_UNEQ: {
        std::string name("HP_UNEQ");
        return name;
    }
    }
    std::string name("No exist");
    return name;

}
uint32 SrcAlarmVC4::itsID(void) {
    return port->getUID();
}
std::string& SrcAlarmVC4::itsName(void) {
    return port->getName();
}
