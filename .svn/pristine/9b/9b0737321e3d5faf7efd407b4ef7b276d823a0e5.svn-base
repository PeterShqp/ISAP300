/*
 * Card4STM1.h
 *
 *  Created on: 2014-5-15
 *      Author: Administrator
 */

#ifndef CARD4STM1_H_
#define CARD4STM1_H_

#include "CBaseCard.h"
#include "ChipRC7883.h"
#include "Chip8STM1CPLD.h"
#include "DriverTrib4STM1.h"
#include "PortSTM4.h"
#include "Chip8STM1Logic1.h"
#include "Chip8STM1Logic2.h"
#include "TribSTM1AlarmDataDefine.h"
#include "STMConfigDataDefine.h"

typedef struct {
    STM_Config_Data_T port[4];
    Trib4STM1_Alarm_Data_T AlarmData;
}Card_ConfigData_4STM1;

class Slot155Channel;
class CrossConnectionManager;
class PairRscSDHChannel;
//class DCCTribRcv;
//class DCCTribSnd;
class Trib4STM1AlarmModule;

class Card4STM1: public CBaseCard {
public:
    Card4STM1(std::string& name, CBaseSlot* slot);
    virtual ~Card4STM1();

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
    Chip8STM1CPLD cpld;
    std::string cardversionInfo;

    friend class Trib4STM1AlarmModule;
    ChipRC7883 tmchip1;
    ChipRC7883 tmchip2;
    Chip8STM1Logic1 fpga1;
    Chip8STM1Logic2 fpga2;
    DriverTrib4STM1 driver;
    Slot155Channel* sltch_obj[126];
    PortSTM4* tribstm_obj[4];
    CrossConnectionManager* ccm_obj;
    Card_ConfigData_4STM1 ConfigData;
//    DCCTribRcv* dccsdhrcv_obj[4];
//    DCCTribSnd* dccsdhsnd_obj[4];


    PairRscSDHChannel* getConnectedSDHChannel(uint32 puid);

    OS_TID CSTM4_alarm;

    Trib4STM1AlarmModule* Am;


};

#endif /* CARD4STM1_H_ */
