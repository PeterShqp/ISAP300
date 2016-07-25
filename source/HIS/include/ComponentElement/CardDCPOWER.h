/*
 * CardDCPOWER.h
 *
 *  Created on: 2015Äê3ÔÂ9ÈÕ
 *      Author: Administrator
 */

#ifndef CardDCPOWER_H_
#define CardDCPOWER_H_
#include "CBaseCard.h"
class FANPOWType;
class CardDCPOWER: public CBaseCard {
	CardDCPOWER();
public:
	CardDCPOWER(std::string& name, CBaseSlot* slot);
	virtual ~CardDCPOWER();

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

#endif /* CARDPWR2_H_ */
