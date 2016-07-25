/*
 * CardDCPOWER.cpp
 *
 *  Created on: 2015Äê3ÔÂ9ÈÕ
 *      Author: Administrator
 */

#include "CardDCPOWER.h"
#include "CardTypeID_define.h"
CardDCPOWER::CardDCPOWER(std::string& name, CBaseSlot* slot):CBaseCard(name,slot) {
	PowVerInfo ="";
}

CardDCPOWER::~CardDCPOWER() {
}

std::string& CardDCPOWER::GetCardVerInfo() {
    return  PowVerInfo;
}
int CardDCPOWER::GetCartTypeID() {
    return PWR_DC_CARD_TYPEID;
}
