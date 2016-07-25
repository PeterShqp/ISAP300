/*
 * Card8EOSFX.cpp
 *
 *  Created on: 2014Äê10ÔÂ27ÈÕ
 *      Author: Administrator
 */

#include "Card8EOSFX.h"
#include "CardTypeID_define.h"

Card8EOSFX::Card8EOSFX(std::string& name, CBaseSlot* slot) : Card8EOS(name, slot) {
    // TODO Auto-generated constructor stub

}

Card8EOSFX::~Card8EOSFX() {
    // TODO Auto-generated destructor stub
}

int Card8EOSFX::GetCartTypeID() {
    return EOS_8X_CARD_TYPEID;
}
