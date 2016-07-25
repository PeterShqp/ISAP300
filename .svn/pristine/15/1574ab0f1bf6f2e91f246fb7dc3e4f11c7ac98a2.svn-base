/*
 * VCG.cpp
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#include "VCG.h"
#include "UID.h"
#include "CHVC.h"
#include "ChipRC6400.h"
#include <string.h>
#include "CPPTools.h"

std::map<uint32, VCG*> VCG::group;

VCG::VCG(uint32 uid, ConfigCell* card, VCG_ConfigData_T* cfg, ChipRC6400& chip)
        : BaseResource(uid, card), driver(chip) {


    group.insert(std::pair<uint32, VCG*>(uid, this));
    UN_Info info = UID::breakUID(getUID());
    hid = info.vcg.vcg & 0x03;

    ConfigData = cfg;
    setEnable(ConfigData->enable, false);
    setLcas(ConfigData->lcas, false);
    for (int i = 0; i < ConfigData->memberNum; ++i) {
        addMember(ConfigData->member[i], false);
    }
    setFlowCtrl(ConfigData->flow, false);
}

VCG::~VCG() {
    group.erase(getUID());
}

int VCG::getEnable() {
    return ConfigData->enable;
}
bool VCG::setEnable(int en, bool save) {
    if( driver.setEnable(hid, en) && save ) {
        ConfigData->enable = en;
        return saveConfig();
    }
    return false;
}
int VCG::getLcas() {
    return ConfigData->lcas;
}
bool VCG::setLcas(int en, bool save) {
    if( driver.setLcas(hid, en) && save ) {
        ConfigData->lcas = en;
        return saveConfig();
    }
    return false;
}
int VCG::memberNumber() {
    return memberGroup.size();
}

/*
 * �����chvc������У�downstream = 0
 * Ӳ������ɹ������޸�CHVC downstreamΪ��ǰVCG
 */
bool VCG::addMember(uint32 mid, bool save) {
    CHVC* m = CHVC::getInstance(mid);
    if( m && (m->getDownStream() == 0) ) {

        if( driver.AddTu12ToVCGSimple(m->itsSn(), hid) ) {

            //增加总线选择期望，解决只配B总线时业务不通的问题。
            UN_Info info = UID::breakUID(m->getUID());
            driver.RC6400_TU12_Bus_Exp_Sel_Rx_Set(info.chvc.channel, info.chvc.group);

            memberGroup.insert(std::pair<uint32, CHVC*>(mid, m));
            m->bandToVCG(this);
            if( save ) {
                makeConfigData();
                return saveConfig();
            }
            else {
                return true;
            }
        }
    }
    return false;
}

bool VCG::removeMember(uint32 mid, bool save) {
    CHVC* m = getMemberInstance(mid);
    if( m ) {
        if( driver.DeleteTu12FromVCGSimple(m->itsSn()) ) {
            memberGroup.erase(mid);
            m->bandToVCG(0);
            if( save ) {
                makeConfigData();
                return saveConfig();
            }
            else {
                return true;
            }
        }
    }
    return false;
}
bool VCG::clrMember() {
    while( memberGroup.begin() != memberGroup.end()) {
        std::map<uint32, CHVC*>::iterator it = memberGroup.begin();
        removeMember(it->first, false);
    }
    makeConfigData();
    return saveConfig();

}
char* VCG::GetDesc(uint32* len) {
    if( len )
        *len = ConfigData->descLen;
    return (char*)ConfigData->desc;
}
bool VCG::SetDesc(char* desc, uint32 len) {
    if( desc ) {
        ConfigData->descLen = len;
        memcpy( ConfigData->desc, desc, len);
        return true;
    }
    return false;
}

CHVC* VCG::getMemberInstance(uint32 uid) {
    std::map<uint32, CHVC*>::iterator it = memberGroup.find(uid);
    if( it != memberGroup.end() ) {
        return it->second;
    }
    return 0;
}
CHVC* VCG::getFirstMember() {
    std::map<uint32, CHVC*>::iterator it = memberGroup.begin();
    if( it != memberGroup.end() ) {
        return it->second;
    }
    return 0;
}
CHVC* VCG::getNextMember(uint32 uid) {
    std::map<uint32, CHVC*>::iterator it = memberGroup.find(uid);
    if( it != memberGroup.end() ) {
        it++;
        if( it != memberGroup.end() ) {
            return it->second;
        }
    }
    return 0;
}


void VCG::makeConfigData(void) {
    std::map<uint32, CHVC*>::iterator it = memberGroup.begin();
    ConfigData->memberNum = memberGroup.size();
    memset(ConfigData->member, 0, sizeof(ConfigData->member));
    for (int i = 0; i < ConfigData->memberNum; ++i) {
        ConfigData->member[i] = it->first;
        it++;
    }
}

uint8 VCG::getFlowCtrl() {
    return ConfigData->flow;
}
bool VCG::setFlowCtrl(uint8 fl, bool save ) {
    driver.RC6400_Pause_Config(hid, fl);
    if( save ) {
        ConfigData->flow = fl;
        return saveConfig();
    }
    return true;
}

bool VCG::ifGFPSynLos(void) {
    if( getEnable() == 0 ) {
        return false;
    }
    return !(driver.getGFPStatus(hid));
}
