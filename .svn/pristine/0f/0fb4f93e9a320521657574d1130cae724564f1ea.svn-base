/*
 * SlotPower.cpp
 *
 *  Created on: 2013-12-5
 *      Author: Administrator
 */

#include "SlotPower.h"
#include "FANPOWOnLine.h"
#include "rtl.h"
#include <stdio.h>
const static int supportCardTable[] = {PWR_AC_CARD_TYPEID, PWR_DC_CARD_TYPEID};

SlotPower::SlotPower(int sn, RegisterAccess* ra, ComponentFactory* f) : CBaseSlot(sn, ra, f) {

}

SlotPower::~SlotPower() {
    // TODO Auto-generated destructor stub
}

int SlotPower::GetCardTypeIDFromHardware() {
    uint8 cmd_slot = SlotPower::GetSn();
	FANPOW_OnLine pow(cmd_slot);
	uint8 rtn = 0;
	if( mod.processFANCommand(pow) == DEFErrorSuccess ) {
        uint8* rsltbuf = pow.getResultBuff();
        if(rsltbuf[1]  == 1){
            rtn =  PWR_AC_CARD_TYPEID;
        }
        else if(rsltbuf[1] == 2){
            rtn = PWR_DC_CARD_TYPEID;
        }
	}
	return rtn;
}

bool SlotPower::supportThisCard(int cardType) {
    for( int i = 0; i < sizeof(supportCardTable)/sizeof(int); i++ ) {
        if( supportCardTable[i] == cardType ) {
            return true;
        }
    }
    return false;
}
