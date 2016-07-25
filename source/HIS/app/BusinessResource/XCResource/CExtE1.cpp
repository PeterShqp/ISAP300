/*
 * CExtE1.cpp
 *
 *  Created on: 2014-3-31
 *      Author: Administrator
 */

#include "CExtE1.h"
#include "CPPTools.h"
#include "DriverPCM.h"


CExtE1::CExtE1(uint32 uid, ConfigCell* card, DriverPCM* driver, bool paired)
        : CSTBus(uid, card, driver, paired){
	
//	UN_Info info = UID::breakUID(uid);
//	itsName = "ExtE1/OMU" +
// 			CPPTools::number2string(info.stbus.slot + 1) +
// 			"/" +
// 			CPPTools::number2string(info.stbus.stbus%4 + 1);
}

CExtE1::~CExtE1() {
    // TODO Auto-generated destructor stub

}

