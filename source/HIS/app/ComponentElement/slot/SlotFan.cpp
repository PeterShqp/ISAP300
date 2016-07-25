/*
 * SlotFan.cpp
 *
 *  Created on: 2013-12-5
 *      Author: Administrator
 */

#include "SlotFan.h"
#include "FANPOWOnLine.h"
const static int supportCardTable[] = {FAN_CARD_TYPEID};

SlotFan::SlotFan(int sn, RegisterAccess* ra, ComponentFactory* f) : CBaseSlot(sn, ra, f) {

}

SlotFan::~SlotFan() {
    // TODO Auto-generated destructor stub
}

int SlotFan::GetCardTypeIDFromHardware() {
	FANPOW_OnLine fan(SlotFan::GetSn());
    int rtnV = 0;
	if( mod.processFANCommand(fan) == DEFErrorSuccess ) {
	    uint8* result = fan.getResultBuff();
        if( result[1] != 0 ) {
            rtnV = FAN_CARD_TYPEID;
        }
	}
	return rtnV;
}

bool SlotFan::supportThisCard(int cardType) {
    for( int i = 0; i < sizeof(supportCardTable)/sizeof(int); i++ ) {
        if( supportCardTable[i] == cardType ) {
            return true;
        }
    }
    return false;
}
