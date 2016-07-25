/*
 * Card32FXO.cpp
 *
 *  Created on: 2015年6月10日
 *      Author: Administrator
 */

#include "Card32FXO.h"
#include "CardTypeID_define.h"

Card32FXO::Card32FXO(std::string& name, CBaseSlot* slot) : Card30VF(name, slot) {
    // TODO Auto-generated constructor stub

}

Card32FXO::~Card32FXO() {
    // TODO Auto-generated destructor stub
}

int Card32FXO::GetCartTypeID() {
    return FXO_32_CARD_TYPEID;
}
