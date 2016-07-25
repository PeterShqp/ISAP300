/*
 * SlotXC.cpp
 *
 *  Created on: 2013-11-20
 *      Author: Administrator
 */

#include "SlotXC.h"
#include "CardTypeID_define.h"
#include "RegisterAccess.h"
#include "GeneralLogic.h"
#include <iostream>
#include "CardXC.h"
#include "SlotModule.h"

static const int supportCardTable[] = {XC_CARD_TYPEID, DXC_CARD_TYPEID, PCMXC_CARD_TYPEID};

TASK void Do_Xc_Reset(void);

SlotXC::SlotXC(int sn, RegisterAccess* ra, ComponentFactory* f) : CBaseSlot(sn, ra, f){
    // TODO Auto-generated constructor stub

}

SlotXC::~SlotXC() {
    // TODO Auto-generated destructor stub
}

int SlotXC::GetCardTypeIDFromHardware() {
    uint16 val = getRegisterAccess()->readReg(0x20ff);
    if( val == 0x0bcda ) {
        return XC_CARD_TYPEID;
    }
    else if( val == 0xabcd ) {
        return DXC_CARD_TYPEID;//PCMXC_CARD_TYPEID;
    }
    else if( val == 0xabce ) {
        return DXC_CARD_TYPEID;
    }
    return -1;
}

bool SlotXC::supportThisCard(int cardType) {
    for( int i = 0; i < sizeof(supportCardTable)/sizeof(int); i++ ) {
        if( supportCardTable[i] == cardType ) {
            return true;
        }
    }
    return false;
}

/*
 * XC�۵ĸ�λ���壺
 * 1. ���� ��ʾMCU��Ԫ��λ
 * 2. ������ʾXC��������
 */
bool SlotXC::reset(Start_Type_E resetcode){
	if(resetcode == Warm_start){
		std::cout << "Warm start" << std::endl;
		GeneralLogic::instance().setWarmStartType();
	}
	else if(resetcode == Cold_start){
		std::cout << "Cold start" << std::endl;
		GeneralLogic::instance().setColdStartType();
	}
    //�ر����в忨�ж�Դ
    for (int i = 0; i < 7; ++i) {
        CBaseCard* c = SlotModule::getSlot(i)->GetCardObject();
        if( c != 0 ) {
            c->closeInterrupt();
        }
    }
    os_tsk_create(Do_Xc_Reset,P_Reset);

	return true;
}


//�ȷ���5A��Ȼ�����������΄�
TASK void Do_Xc_Reset(void){

    //��CPLD�Ĵ�����λ
    GeneralLogic::instance().stopWTD();
    GeneralLogic::instance().resetMcu();
	os_tsk_delete_self();
}
