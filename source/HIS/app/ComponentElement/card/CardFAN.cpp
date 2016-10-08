/*
 * CardFAN.cpp
 *
 *  Created on: 2015��3��4��
 *      Author: Administrator
 */

#include "CardFAN.h"
#include "CardTypeID_define.h"
#include "SysError.h"

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
