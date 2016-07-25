/*
 * Card4EOSN.h
 *
 *  Created on: 2015年5月16日
 *      Author: Administrator
 */

#ifndef CARD4EOSN_H_
#define CARD4EOSN_H_

#include "CBaseCard.h"
#include "ChipRC6400.h"
#include "CHVC.h"
#include "VCG.h"
#include "Chip8EOSCPLD.h"
#include "EOSCardAlarmDataDefine.h"
#include "Chip8EOSLogicN.h"
#include "Chip8EOSLogicN2.h"
#include "EosCardConfigDefine.h"

class EOS4NCardAlarmModule;

class Card4EOSN: public CBaseCard {
public:
    Card4EOSN(std::string& name, CBaseSlot* slot);
    virtual ~Card4EOSN();

    virtual int GetCartTypeID();
    virtual uint8* getConfigDataBuff(void) {
        return (uint8*) &ConfigData;
    };
    virtual uint32 getConfigDataLen(void) {
        return sizeof(ConfigData);
    };
    virtual void loadDefaultData(void);
    virtual std::string& GetCardVerInfo(){
        return cardversionInfo;
    };
private:
    friend class EOS4NCardAlarmModule;
    Chip8EOSLogicN fpga;
    Chip8EOSLogicN2 fpga2;
    ChipRC6400 eos_1;
    Chip8EOSCPLD cpld;
    std::string cardversionInfo;

    CHVC* chvc_obj[126];
    VCG* vcg_obj[4];
    Card_ConfigData_4EOS ConfigData;
    EOS4NCardAlarmModule* AM;
};

#endif /* CARD4EOSN_H_ */
