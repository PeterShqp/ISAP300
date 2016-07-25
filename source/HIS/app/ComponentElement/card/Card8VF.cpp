/*
 * Card8VF.cpp
 *
 *  Created on:
 *      Author: Administrator
 */

#include "Card8VF.h"
#include "CardTypeID_define.h"

Card8VF::Card8VF(std::string& name, CBaseSlot* slot) :
    CardVF(name, slot, 10) {
    // TODO Auto-generated constructor stub

}

Card8VF::~Card8VF() {
    // TODO Auto-generated destructor stub
}

int Card8VF::GetCartTypeID() {
    return VF_8_CARD_TYPEID;
}
