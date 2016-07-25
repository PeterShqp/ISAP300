/*
 * Card4EOS.h
 *
 *  Created on: 2014��10��24��
 *      Author: Administrator
 */

#ifndef CARD4EOS_H_
#define CARD4EOS_H_

#include "CBaseCard.h"
#include "Chip8EOSLogic.h"
#include "ChipRC6400.h"
#include "CHVC.h"
#include "VCG.h"
#include "Chip8EOSCPLD.h"
#include "EOSCardAlarmDataDefine.h"
#include "EosCardConfigDefine.h"


class EOS4CardAlarmModule;

class Card4EOS: public CBaseCard {
public:
    Card4EOS(std::string& name, CBaseSlot* slot);
    virtual ~Card4EOS();

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
    friend class EOS4CardAlarmModule;
    Chip8EOSLogic fpga;
    ChipRC6400 eos_1;
    Chip8EOSCPLD cpld;
    std::string cardversionInfo;

    CHVC* chvc_obj[126];
    VCG* vcg_obj[4];
    Card_ConfigData_4EOS ConfigData;

    EOS4CardAlarmModule* AM;

};

#endif /* CARD4EOS_H_ */
