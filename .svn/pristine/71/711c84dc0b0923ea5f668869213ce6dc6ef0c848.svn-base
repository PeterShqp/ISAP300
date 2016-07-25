/*
 * Card8EOSN.h
 *
 *  Created on: 2014��12��22��
 *      Author: Administrator
 */

#ifndef CARD8EOSN_H_
#define CARD8EOSN_H_

#include "CBaseCard.h"
#include "ChipRC6400.h"
#include "CHVC.h"
#include "VCG.h"
#include "Chip8EOSCPLD.h"
#include "EOSCardAlarmDataDefine.h"
#include "Chip8EOSLogicN.h"
#include "Chip8EOSLogicN2.h"
#include "EosCardConfigDefine.h"

class EOS8NCardAlarmModule;
class Card8EOSN: public CBaseCard {
public:
    Card8EOSN(std::string& name, CBaseSlot* slot);
    virtual ~Card8EOSN();

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
    friend class EOS8NCardAlarmModule;
    Chip8EOSLogicN fpga;
    Chip8EOSLogicN2 fpga2;
    ChipRC6400 eos_1;
    ChipRC6400 eos_2;
    Chip8EOSCPLD cpld;
    std::string cardversionInfo;

    CHVC* chvc_obj[126];
    VCG* vcg_obj[8];
    Card_ConfigData_8EOS ConfigData;
    EOS8NCardAlarmModule* AM;
};

#endif /* CARD8EOSN_H_ */
