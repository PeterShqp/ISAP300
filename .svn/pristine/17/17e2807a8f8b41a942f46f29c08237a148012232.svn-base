/*
 * SrcAlarmVCG.cpp
 *
 *  Created on: 2014Äê10ÔÂ28ÈÕ
 *      Author: Administrator
 */

#include "SrcAlarmVCG.h"
#include "AlarmInstance.h"
#include "VCG.h"

SrcAlarmVCG::SrcAlarmVCG(BAlarmModule* m, VCG* v, SrcVCGAlarm_Data* d) : BAlarmSource(m) {

    vcg = v;
    PConfigData = d;
}

SrcAlarmVCG::~SrcAlarmVCG() {
    // TODO Auto-generated destructor stub
}

void SrcAlarmVCG::makeAlarmSignal(void) {
    addAlmIns( new AlarmInstance(VCG_Sig_Base+VCG_GFP_SynLos, this, &(PConfigData->Property[VCG_GFP_SynLos])) );
}

bool SrcAlarmVCG::ifSrcRestrain() {
    return false;
}

bool SrcAlarmVCG::getAlarm(int type) {
    switch( type-VCG_Sig_Base ) {
    case VCG_GFP_SynLos:
        return vcg->ifGFPSynLos();
    }
    return false;
}
std::string SrcAlarmVCG::getTypeName(int type) {
    switch( type-VCG_Sig_Base ) {
    case VCG_GFP_SynLos:
        std::string name("VCG_GFP_SynLos");
        return name;
    }
    std::string name("No exist");
    return name;
}
uint32 SrcAlarmVCG::itsID(void) {
    return vcg->getUID();
}
std::string& SrcAlarmVCG::itsName(void) {
    return vcg->getName();
}
