/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CBaseSlot.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/SlotCard/CBaseSlot.cpp
 ** Created by:          Shqp
 ** Created date:        2012-4-11
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#include "CBaseSlot.h"
#include "CBaseCard.h"
#include "ComponentFactory.h"
#include "os.h"
#include "RegisterAccess.h"

//ÿһ������̳У����ṹ���������Ĳ�λ�ţ��������ߣ�������������ҿ���Ӳ��ID������ID��
CBaseSlot::CBaseSlot(int sn, RegisterAccess* reg, ComponentFactory* factory) {
	iSn = sn;
	ra = reg;
	card = NULL;
	iFactory = factory;
	state = NoCard;
}

CBaseSlot::~CBaseSlot() {
    if( card ) {
        iFactory->destroyCard(card);
        card = 0;
    }
    delete ra;
}

std::string& CBaseSlot::GetName() {
	static std::string s("");
	if( card == NULL ) {
		return s;
	}
	else {
		return card->GetName();
	}
}


/*
 * ����һ�鿨��������У������´���
 */
CBaseCard* CBaseSlot::InsertCard(int TypeID) {
	return card = iFactory->makeCard(TypeID,this);
}

void CBaseSlot::RemoveCard(void) {
	iFactory->destroyCard(card);
	card = 0;
}


int CBaseSlot::GetCardType(void) {
	if( card ) {
		return card->GetCartTypeID();
	}
	return 0;
}


int CBaseSlot::getCurrentCardTypeID(void) {
    int type = GetCardTypeIDFromHardware();
    if( supportThisCard(type) ) {
        return type;
    }
    return -1;
}

//int CBaseSlot::PlugInCard(CBaseCard* objCard) {
//	if( card != 0 ) {
//		return -1;
//	}
//	card = objCard;
//	return 0;
//}
//int CBaseSlot::PullOutCard(void) {
//	if( card != 0 ) {
//		delete card;
//		card = 0;
//		return 0;
//	}
// 	return -1;
// }




