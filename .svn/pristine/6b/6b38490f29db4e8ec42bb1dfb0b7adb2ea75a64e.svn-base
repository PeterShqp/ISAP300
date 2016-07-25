/*
 * Card16E1.h
 *
 *  Created on: 2014年10月22日
 *      Author: Administrator
 */

#ifndef CARD16E1_H_
#define CARD16E1_H_

#include "CBaseCard.h"
#include "Chip16E1Logic.h"
#include "Chip16E1CPLD.h"
#include "ChipRC7883.h"
#include "PortE1.h"
#include "E1CardAlarmDataDefine.h"

class CBaseSlot;
class PortE1;
class PairRscSDHChannel;
class E1Card16AlarmModule;

typedef struct {
    UE1_Config_Data_T port[16];//16个E1口的使能、SNCP保护、描述、长度
    SrcE1Alarm_Data E1AlmData[16];
}Card_ConfigData_16E1;



class Card16E1: public CBaseCard {
    enum {E1_Port_Num = 16};
public:
    Card16E1(std::string& name, CBaseSlot* slot);
    virtual ~Card16E1();

    virtual int GetCartTypeID();
    virtual std::string& GetCardVerInfo(){
        return cardversionInfo;
    };
//    ChipE1Logic& getChipE1Logic(void) {
//        return chipE1;
//    };

    virtual uint8* getConfigDataBuff(void) {
        return (uint8*) &ConfigData;
    };
    virtual uint32 getConfigDataLen(void) {
        return sizeof(ConfigData);
    };

    virtual void loadDefaultData(void);
private:
    friend class E1Card16AlarmModule;
    Chip16E1Logic chipE1;//FPGAchip
    ChipRC7883 chipE1Map;//7883chip
    PortE1* e1port_obj[E1_Port_Num];
    Card_ConfigData_16E1 ConfigData;
    std::string cardversionInfo;
    Chip16E1CPLD cpld;
    E1Card16AlarmModule* AM;
    PairRscSDHChannel* getConnectedSDHChannel(uint32 puid);
};

#endif /* CARD16E1_H_ */
