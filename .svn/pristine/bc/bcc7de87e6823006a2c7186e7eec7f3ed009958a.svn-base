/*
 * CardFAN.h
 *
 *  Created on: 2015Äê3ÔÂ4ÈÕ
 *      Author: Administrator
 */

#ifndef CARDFAN_H_
#define CARDFAN_H_

#include "CBaseCard.h"

typedef struct {
}Card_ConfigData_FAN;

class CardFAN: public CBaseCard {
    CardFAN();
public:
    CardFAN(std::string& name, CBaseSlot* slot);
    virtual ~CardFAN();

    virtual std::string& GetCardVerInfo();
    virtual int GetCartTypeID();
    virtual uint8* getConfigDataBuff(void) {
        return (uint8*) &ConfigData;
    };
    virtual uint32 getConfigDataLen(void) {
        return sizeof(ConfigData);
    };
private:
    Card_ConfigData_FAN ConfigData;
    std::string cardversionInfo;
};

#endif /* CARDFAN_H_ */
