/*
 * Card8EOSFXN.h
 *
 *  Created on: 2014Äê12ÔÂ23ÈÕ
 *      Author: Administrator
 */

#ifndef CARD8EOSFXN_H_
#define CARD8EOSFXN_H_

#include "Card8EOSN.h"

class Card8EOSFXN : public Card8EOSN {
public:
    Card8EOSFXN(std::string& name, CBaseSlot* slot);
    virtual ~Card8EOSFXN();

    virtual int GetCartTypeID();
};

#endif /* CARD8EOSFXN_H_ */
