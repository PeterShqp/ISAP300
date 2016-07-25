/*
 * CardDATA.h
 *
 *  Created on: 2015年6月25日
 *      Author: Administrator
 */

#ifndef CARDDATA_H_
#define CARDDATA_H_

#include "os.h"
#include <string.h>
#include "CBaseCard.h"
#include "Chip16DATALogic.h"
#include "PortData.h"
#include "Chip16DATACPLD.h"

typedef struct {
    DATA_Config_T port[16];
}Card_ConfigData_16DATA;

class CBaseSlot;
class PortData;
class PairTSChannel;

class CardDATA: public CBaseCard {
//    static const uint8 enable = 1;
    CardDATA();
public:
    CardDATA(std::string& name,CBaseSlot* slot, uint8 pn);
    virtual ~CardDATA();

    virtual int GetCartTypeID() = 0;
    virtual std::string& GetCardVerInfo(){
        return cardversionInfo;
    }
    virtual bool Resetcard(){
//      cpld.Resetchip();
        return true;
    }
    virtual void loadDefaultData(void);
    virtual uint8* getConfigDataBuff(void) {
        return (uint8*) &Config;
    }
    virtual uint32 getConfigDataLen(void) {
        return sizeof(Config);
    };

private:
    std::string cardversionInfo;
    PortData* dataport[16];
    PairTSChannel* getConnectedTS(uint32 datauid);
    Chip16DATALogic drive;
    Chip16DATACPLD cpld;
    Card_ConfigData_16DATA Config;
    friend TASK void Do_16DATA_LED(void* pxc);
    OS_TID C16DATA_LED;
    uint8 portNumber;
private:
    static const uint8 port2ts[16] ;
};

#endif /* CARDDATA_H_ */
