/*
 * SlotEXTNoSDH.cpp
 *
 *  Created on: 2015年5月28日
 *      Author: Administrator
 */

#include "SlotEXTNoSDH.h"
#include "CardTypeID_define.h"
#include "RegisterAccess.h"

const static int supportCardTable[] = {
    VF_30_CARD_TYPEID, VF_16_CARD_TYPEID, VF_8_CARD_TYPEID,
    DATA_16_CARD_TYPEID, DATA_8_CARD_TYPEID,
    FXS_32_CARD_TYPEID, FXO_32_CARD_TYPEID, MT_30_CARD_TYPEID,
    FE1_16_CARD_TYPEID
};

SlotEXTNoSDH::SlotEXTNoSDH(int sn, RegisterAccess* ra, ComponentFactory* factory) : CBaseSlot(sn, ra, factory) {
    // TODO Auto-generated constructor stub
    HOLDToReset = 0;
    FlagStart = 0;
}

SlotEXTNoSDH::~SlotEXTNoSDH() {
    // TODO Auto-generated destructor stub
}

int SlotEXTNoSDH::GetCardTypeIDFromHardware() {
    if( HOLDToReset != 0 ) {
        --HOLDToReset;
        return -1;
    }
    if( FlagStart == 0 ) {
        return -1;
    }
    uint16 val = getRegisterAccess()->readReg(0x00ff);
    switch( val ) {
    case value_30VF:
        return VF_30_CARD_TYPEID;
    case value_16VF:
        return VF_16_CARD_TYPEID;
    case value_8VF:
        return VF_8_CARD_TYPEID;
    case vlaue_16DATA:
        return DATA_16_CARD_TYPEID;
    case value_32FXS:
        return FXS_32_CARD_TYPEID;
    case value_32FXO:
        return FXO_32_CARD_TYPEID;
    case value_30MT:
        return MT_30_CARD_TYPEID;
    case value_16FE1:
        return FE1_16_CARD_TYPEID;
    case value_8DATA:
        return DATA_8_CARD_TYPEID;
    }
    return -1;
}

bool SlotEXTNoSDH::supportThisCard(int cardType) {
    for( int i = 0; i < sizeof(supportCardTable)/sizeof(int); i++ ) {
        if( supportCardTable[i] == cardType ) {
            return true;
        }
    }
    return false;
}

bool SlotEXTNoSDH::reset(Start_Type_E type){
    if( !cardExist() || type == Warm_start ) {
        return false;
    }
    HOLDToReset = 10;
    return true;
}
