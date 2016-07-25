/*
 * CardACPOWER.h
 *
 *  Created on: 2015Äê3ÔÂ9ÈÕ
 *      Author: Administrator
 */

#ifndef CardACPOWER_H_
#define CardACPOWER_H_

#include "CBaseCard.h"
class FANPOWType;

class CardACPOWER: public CBaseCard {
	CardACPOWER();
public:
	CardACPOWER(std::string& name, CBaseSlot* slot);
	virtual ~CardACPOWER();

	virtual std::string& GetCardVerInfo();
	virtual int GetCartTypeID();
    virtual uint8* getConfigDataBuff(void) {
        return 0;
    };
    virtual uint32 getConfigDataLen(void) {
        return 0;
    };

private:
	std::string PowVerInfo;
};

#endif /* CARDPWR1_H_ */
