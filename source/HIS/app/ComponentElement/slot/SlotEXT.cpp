/*
 * SlotEXT.cpp
 *
 *  Created on: 2013-11-21
 *      Author: Administrator
 */

#include "SlotEXT.h"
#include "RegisterAccess.h"
#include "CBaseCard.h"
#include "CardTypeID_define.h"
#include "GeneralLogic.h"

const static int supportCardTable[] = {
        E1_48_CARD_TYPEID, E1_24_CARD_TYPEID, EOS_8_CARD_TYPEID, VF_30_CARD_TYPEID,
        STM_4_CARD_TYPEID, STM_8_CARD_TYPEID, VF_16_CARD_TYPEID, VF_8_CARD_TYPEID,
        E1_16_CARD_TYPEID, EOS_4_CARD_TYPEID, EOS_4X_CARD_TYPEID,VF_16_CARD_TYPEID,
        EOS_8X_CARD_TYPEID,EOS_8N_CARD_TYPEID, EOS_8XN_CARD_TYPEID,DATA_16_CARD_TYPEID,
        EOS_4N_CARD_TYPEID, EOS_4XN_CARD_TYPEID, V5_CARD_TYPEID,
        FXS_32_CARD_TYPEID, FXO_32_CARD_TYPEID, MT_30_CARD_TYPEID,
        FE1_16_CARD_TYPEID, DATA_8_CARD_TYPEID,
};

SlotEXT::SlotEXT(int sn, RegisterAccess* ra, ComponentFactory* f) : CBaseSlot(sn, ra, f) {
    HOLDToReset = 0;
    FlagStart = 0;
}

SlotEXT::~SlotEXT() {
    // TODO Auto-generated destructor stub
}
/*
 * ��չ���ǻ����������࣬ʵ��Ӳ��ID�����ʶ��ID��ת��
 */
int SlotEXT::GetCardTypeIDFromHardware() {
    if( HOLDToReset != 0 ) {
        --HOLDToReset;
        return -1;
    }
//    if( FlagStart == 0 ) {
//        return -1;
//    }
    uint16 val = getRegisterAccess()->readReg(0x00ff);
    switch( val ) {
    case value_24E1:
        return E1_24_CARD_TYPEID;
    case value_48E1:
        return E1_48_CARD_TYPEID;
    case value_8EOS:
        return EOS_8_CARD_TYPEID;
    case value_8EOSX:
        return EOS_8X_CARD_TYPEID;
    case value_30VF:
        return VF_30_CARD_TYPEID;
    case value_4STM:
        return STM_4_CARD_TYPEID;
    case value_8STM:
        return STM_8_CARD_TYPEID;
    case value_16VF:
        return VF_16_CARD_TYPEID;
    case value_8VF:
        return VF_8_CARD_TYPEID;
    case value_16E1:
        return E1_16_CARD_TYPEID;
    case value_4EOS:
        return EOS_4_CARD_TYPEID;
    case value_4EOSX:
        return EOS_4X_CARD_TYPEID;
    case value_8EOS2:
        return EOS_8N_CARD_TYPEID;
    case value_4EOS2:
        return EOS_4N_CARD_TYPEID;
    case value_4EOSX2:
        return EOS_4XN_CARD_TYPEID;
    case value_8EOSX2:
        return EOS_8XN_CARD_TYPEID;
    case vlaue_16DATA:
    	return DATA_16_CARD_TYPEID;
    case value_V5:
        return V5_CARD_TYPEID;
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

bool SlotEXT::supportThisCard(int cardType) {
    for( int i = 0; i < sizeof(supportCardTable)/sizeof(int); i++ ) {
        if( supportCardTable[i] == cardType ) {
            return true;
        }
    }
    return false;
}

bool SlotEXT::reset(Start_Type_E type){
    if( !cardExist() || type == Warm_start ) {
		return false;
	}
    GeneralLogic::instance().setColdStartType();
    HOLDToReset = 10;
	return true;
}

void SlotEXT::resetPLL(int sn) {
    getRegisterAccess()->writeReg(0x130f, 1<<sn);
    getRegisterAccess()->writeReg(0x130f, 0);
}
