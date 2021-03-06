/*
 * Card8STM1.h
 *
 *  Created on: 2014��8��12��
 *      Author: Administrator
 */

#ifndef CARD8STM1_H_
#define CARD8STM1_H_

#include "CBaseCard.h"
#include "ChipRC7883.h"
#include "Chip8STM1CPLD.h"
#include "DriverSDH8STM1.h"
#include "PortSTM4.h"
#include "Chip8STM1Logic1.h"
#include "Chip8STM1Logic2.h"
#include "TribSTM1AlarmDataDefine.h"
#include "STMConfigDataDefine.h"

typedef struct {
    STM_Config_Data_T port[8];
    Trib8STM1_Alarm_Data_T AlarmData;
}Card_ConfigData_8STM1;

class Slot155Channel;
class CrossConnectionManager;
class PairRscSDHChannel;
//class DCCTribRcv;
//class DCCTribSnd;
class Trib8STM1AlarmModule;

class Card8STM1 : public CBaseCard {
public:
    Card8STM1(std::string& name, CBaseSlot* slot);
    virtual ~Card8STM1();

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
    }

    virtual void closeInterrupt(void);
private:
    friend TASK void Do_Trib8_LED(void* pxc);
    Chip8STM1CPLD cpld;
    std::string cardversionInfo;

    friend class Trib8STM1AlarmModule;
    ChipRC7883 tmchip1;
    ChipRC7883 tmchip2;
    ChipRC7883 tmchip3;
    ChipRC7883 tmchip4;
    Chip8STM1Logic1 fpga1;
    Chip8STM1Logic2 fpga2;
    DriverSDH8STM1 driver;
    Slot155Channel* sltch_obj[126];
    PortSTM4* tribstm_obj[8];
    CrossConnectionManager* ccm_obj;
    Card_ConfigData_8STM1 ConfigData;
//    DCCTribRcv* dccsdhrcv_obj[8];
//    DCCTribSnd* dccsdhsnd_obj[8];


    PairRscSDHChannel* getConnectedSDHChannel(uint32 puid);

    OS_TID CSTM8_alarm;
    Trib8STM1AlarmModule* Am;
};

#endif /* CARD8STM1_H_ */
