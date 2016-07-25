/*
 * Card4EOSFXN.cpp
 *
 *  Created on: 2015年5月16日
 *      Author: Administrator
 */

#include "Card4EOSFXN.h"
#include "CardTypeID_define.h"

Card4EOSFXN::Card4EOSFXN(std::string& name, CBaseSlot* slot) : Card4EOSN(name, slot){
    // TODO Auto-generated constructor stub

}

Card4EOSFXN::~Card4EOSFXN() {
    // TODO Auto-generated destructor stub
}

int Card4EOSFXN::GetCartTypeID() {
    return EOS_4XN_CARD_TYPEID;
}
