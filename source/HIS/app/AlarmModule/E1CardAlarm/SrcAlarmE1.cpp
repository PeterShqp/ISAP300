/*
 * SrcAlarmE1.cpp
 *
 *  Created on: 2014Äê9ÔÂ9ÈÕ
 *      Author: Administrator
 */

#include "SrcAlarmE1.h"
#include "PortE1.h"
#include "AlarmInstance.h"
#include "BAlarmDisplay.h"

SrcAlarmE1::SrcAlarmE1(BAlarmModule* m, PortE1* p, SrcE1Alarm_Data* data, BAlarmDisplay& LED) : BAlarmSource(m), ledWork(LED) {
    port = p;
    pConfigData = data;
}

SrcAlarmE1::~SrcAlarmE1() {
    // TODO Auto-generated destructor stub
}

void SrcAlarmE1::makeAlarmSignal(void) {
    addAlmIns( new AlarmInstance(E1_Sig_Base+E1_LOS, this, &(pConfigData->Property[E1_LOS]), &ledWork) );
}
bool SrcAlarmE1::ifSrcRestrain() {
    return false;
}
bool SrcAlarmE1::getAlarm(int type) {
    switch( type-E1_Sig_Base ) {
    case E1_LOS:
        return port->getLos();
    }
    return false;
}
std::string SrcAlarmE1::getTypeName(int type) {
    switch( type-E1_Sig_Base ) {
    case E1_LOS:
        std::string name("E1_LOS");
        return name;
    }
    std::string name("No exist");
    return name;
}
uint32 SrcAlarmE1::itsID(void) {
    return port->getUID();
}
std::string& SrcAlarmE1::itsName(void) {
    return port->getName();
}
