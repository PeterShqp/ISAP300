/*
 * PortData.cpp
 *
 *  Created on: 2014-2-25
 *      Author: Administrator
 */

#include "PortData.h"
#include "PairTSChannel.h"
#include "UID.h"
#include "CPPTools.h"
#include "Chip16DATALogic.h"
#include <string.h>

std::map<uint32, PortData*> PortData::group;

PortData::PortData(uint32 uid, ConfigCell* card, PairTSChannel* t,Chip16DATALogic& dri,DATA_Config_T* config)
        : RealPortBase(uid, card) ,drive(dri){
    group.insert( std::pair<uint32, PortData*>(uid, this));
    ConfigData = config;
    ts = t;
    if( ts ) {
        ts->setDownStream(uid);
    }
    setEnable(1);
}

PortData::~PortData() {
    if( ts ) {
        ts->setDownStream(0);
    }
    group.erase(getUID());
}

int PortData::setLoop(const int type) {
	uint8 sn = getPortSn();
	switch( type ) {
	case dev_and_line_loop:
		drive.setPortLoopOut(sn, 1);
		drive.setPortLoopIn(sn, 1);
		break;
	case line_loop:
		drive.setPortLoopOut(sn, 1);
		drive.setPortLoopIn(sn, 0);
		break;
	case dev_loop:
		drive.setPortLoopOut(sn, 0);
		drive.setPortLoopIn(sn, 1);
		break;
	case no_loop:
		drive.setPortLoopOut(sn, 0);
		drive.setPortLoopIn(sn, 0);
		break;
	default:
		return -1;
	}
	return 0x5A;
}

int PortData::getEnable(void) {
    return ConfigData->enable;
}
bool PortData::setEnable(int en, bool save) {
    int sn = getPortSn();
    drive.setPortEnable(sn, en);
    if( save ) {
        ConfigData->enable = en;
        return saveConfig();
    }
    return true;
}
uint8 PortData::getPortSn() {
    UN_Info info = UID::breakUID(getUID());
    return info.data.port;
}
int PortData::getPortType(void) {
		return drive.getDPtype(getPortSn());

}
char* PortData::getDesc(uint32* len) {
	if( len ){
		*len = ConfigData->dlen;
	}
	return ConfigData->desc;
}
int PortData::setDesc(const char* s, uint32 len) {
	ConfigData->dlen = len;
	memcpy(ConfigData->desc, s, len);
	saveConfig();
	return 1;
}
