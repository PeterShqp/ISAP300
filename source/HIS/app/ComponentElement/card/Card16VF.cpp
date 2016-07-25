/*
 * Card16VF.cpp
 *
 *  Created on: 2014年7月14日
 *      Author: Administrator
 */

#include "Card16VF.h"
#include "CardTypeID_define.h"

Card16VF::Card16VF(std::string& name, CBaseSlot* slot) :
    CardVF(name, slot, 16) {
    // TODO Auto-generated constructor stub

}

Card16VF::~Card16VF() {
    // TODO Auto-generated destructor stub
}

int Card16VF::GetCartTypeID() {
    return VF_16_CARD_TYPEID;
}
