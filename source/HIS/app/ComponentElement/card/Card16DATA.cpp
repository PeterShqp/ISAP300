/*
 * Card16DATA.cpp
 *
 *  Created on: 2015��1��20��
 *      Author: Administrator
 */

#include "Card16DATA.h"
#include "CardTypeID_define.h"

Card16DATA::Card16DATA(std::string& name, CBaseSlot* slt) :
    CardDATA(name,slt,16) {
}

Card16DATA::~Card16DATA() {
}

int Card16DATA::GetCartTypeID(){
	return DATA_16_CARD_TYPEID;//50
}

