/*
 * Card24E1.cpp
 *
 *  Created on: 2013-12-17
 *      Author: Administrator
 */

#include "Card24E1.h"
#include "CardTypeID_define.h"
#include "UID.h"
#include "CBaseSlot.h"
#include "PairRscSDHChannel.h"
#include <string.h>
#include "SysError.h"
//#include "GeneralLogic.h"
#include "E1CardAlarmModule.h"
#include <iostream>


//TASK void Do_24E1_LED(void* pcard);
//构造函数通过槽位号获取ezbus
Card24E1::Card24E1(std::string& name, CBaseSlot* slot) : CBaseCard(name, slot),
		cpld(slot), chipE1(slot), chipE1Map(slot, 0x8000, mode_MAP) {
//	if(GeneralLogic::instance().ifColdStart()) {
	    Chip_INIT_RESULT rst = chipE1.ChipInit();
		if( rst == failed ) {
			throw SysError("!!!Card 24E1 E1Logic init error!!!");
		}
		else if( rst == succeed ) {
		    if( chipE1Map.ChipInit() == failed ) {
		        throw SysError("!!!Card 24E1 RC7883 init error!!!");
		    }
		}
        else {
            std::cout << chipE1.itsName() << " have been running!" << std::endl;
        }
//	}
    if( !fetchConfig() ) {
        throw SysError("!!!Card 24E1 config data error!!!");
    }
    ST_E1 info;
    info.slot = slot->GetSn();
    for (int i = 0; i < E1_Port_Num; ++i) {
        info.E1 = i;
        uint32 uid = UID::makeUID(&info);
        PairRscSDHChannel* mapLink = getConnectedSDHChannel(uid);
        e1port_obj[i] = new PortE1(uid, mapLink, this, chipE1Map, &ConfigData.port[i]);
    }


    cardversionInfo = cpld.GetVerInfo();

    AM = new E1CardAlarmModule(this);
    AM->initModule();

}

Card24E1::~Card24E1() {
    delete AM;
    for (int i = 0; i < E1_Port_Num; ++i) {
        delete e1port_obj[i];
    }
}

int Card24E1::GetCartTypeID() {
    return E1_24_CARD_TYPEID;
}


PairRscSDHChannel* Card24E1::getConnectedSDHChannel(uint32 puid) {
    UN_Info e1info = UID::breakUID(puid);
    ST_Sdh_channel chinfo;
    chinfo.slot = e1info.E1.slot;
    chinfo.bus = 0;
    chinfo.channel = e1info.E1.E1;
    uint32 chUID = UID::makeUID(&chinfo);
    return PairRscSDHChannel::getInstance(chUID);
}


void Card24E1::loadDefaultData(void) {
    UE1_Config_Data_T temp;
    temp.enable = 1;
    memset(temp.sncp, 0, 8);
    temp.dlen = 0;
    memset(temp.desc, 0, sizeof(temp.desc));
    for (int i = 0; i < 24; ++i) {
        memcpy( &ConfigData.port[i], &temp, sizeof(UE1_Config_Data_T));
        ConfigData.E1AlmData[i].Property[0].level = 2;
    }
}

