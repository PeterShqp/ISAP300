/*
 * Card8DATA.cpp
 *
 *  Created on: 2015年6月25日
 *      Author: Administrator
 */

#include "Card8DATA.h"

Card8DATA::Card8DATA(std::string& name, CBaseSlot* slt) : CardDATA(name, slt, 8) {
    // TODO Auto-generated constructor stub

}

Card8DATA::~Card8DATA() {
    // TODO Auto-generated destructor stub
}

int Card8DATA::GetCartTypeID(){
    return DATA_8_CARD_TYPEID;//50
}
