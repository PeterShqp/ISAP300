/*
 * CInnerE1.cpp
 *
 *  Created on: 2013-12-16
 *      Author: Administrator
 */

#include "CInnerE1.h"
#include "PairRscSDHChannel.h"
#include "UID.h"
#include "CPPTools.h"

CInnerE1::CInnerE1(uint32 uid, ConfigCell* card, uint32 mapSdhCh, DriverPCM* chip, bool paired)
        : CSTBus(uid, card, chip, paired) {
    // TODO Auto-generated constructor stub
    PairRscSDHChannel* ch = PairRscSDHChannel::getInstance(UID::getPairUID(mapSdhCh));
    if( ch ) {
        ch->setDownStream(UID::getPairUID(uid));
    }
	UN_Info info = UID::breakUID(uid);
//	itsName = "InnerE1/OMU" +
//                CPPTools::number2string(info.stbus.slot + 1) + "/" +
//                CPPTools::number2string(info.stbus.stbus%4 + 1);
}

CInnerE1::~CInnerE1() {
    // TODO Auto-generated destructor stub
}

