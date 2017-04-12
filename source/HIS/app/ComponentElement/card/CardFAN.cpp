/*
 * CardFAN.cpp
 *
 *  Created on: 2015��3��4��
 *      Author: Administrator
 */

#include "CardFAN.h"
#include "CardTypeID_define.h"
#include "SysError.h"
#include "FANPOWModule.h"
#include "CmdFanVer.h"
#include <stdio.h>

CardFAN::CardFAN(std::string& name, CBaseSlot* slot) : CBaseCard(name, slot) {

    cardversionInfo = "V1.3";

    if( !fetchConfig() ) {
        throw SysError("!!!Card FAN config data error!!!");
    }
}

CardFAN::~CardFAN() {
    // TODO Auto-generated destructor stub
}

std::string& CardFAN::GetCardVerInfo() {
    FANPOWModule mod;
    CmdFanVer cmd;
    if( mod.processFANCommand(cmd) == DEFErrorSuccess ) {
        cardversionInfo.clear();
        cardversionInfo = "MCU:V";
        uint8* rst = cmd.getResultBuff();
        cardversionInfo += CPPTools::number2string(rst[1]);
		cardversionInfo += ",";
    }
    else {
        cardversionInfo = "MCU:V1.3,";
        printf("\n!!!processFANCommand Error!!!");

    }
    return cardversionInfo;
}
int CardFAN::GetCartTypeID() {
    return FAN_CARD_TYPEID;
}


uint8 CardFAN::getBuzzerCfg(void) {
    return ConfigData.buzzerCtrl;
}
bool CardFAN::setBuzzerCfg(uint8 r) {
    ConfigData.buzzerCtrl = r;
    return saveConfig();
}
