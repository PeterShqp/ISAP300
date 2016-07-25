/*
 * CardV5.h
 *
 *  Created on: 2015Äê3ÔÂ11ÈÕ
 *      Author: Administrator
 */

#ifndef CARDV5_H_
#define CARDV5_H_

#include "CBaseCard.h"
#include "ChipV5Logic.h"

typedef struct {
}Card_ConfigData_V5;

class CardV5: public CBaseCard {
public:
    CardV5(std::string& name, CBaseSlot* slot);
    virtual ~CardV5();

    virtual int GetCartTypeID();
    virtual std::string& GetCardVerInfo(){
        return cardversionInfo;
    };
    virtual uint8* getConfigDataBuff(void) {
        return (uint8*) &ConfigData;
    };
    virtual uint32 getConfigDataLen(void) {
        return sizeof(ConfigData);
    };
private:
    ChipV5Logic fpga;
    Card_ConfigData_V5 ConfigData;
    std::string cardversionInfo;
};

#endif /* CARDV5_H_ */
