/*
 * Card30VF.cpp
 *
 *  Created on: 2014-2-20
 *      Author: Administrator
 */

#include "Card30VF.h"
#include "CardTypeID_define.h"
#include <string.h>

Card30VF::Card30VF(std::string& name, CBaseSlot* slot) :
		CardVF(name, slot, 30) {
}

Card30VF::~Card30VF() {

}

int Card30VF::GetCartTypeID() {
	return VF_30_CARD_TYPEID;
}



