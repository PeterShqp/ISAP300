/*
 * Card48E1.h
 *
 *  Created on: 2014年5月17日
 *      Author: Administrator
 */

#ifndef CARD48E1_H_
#define CARD48E1_H_

#include "ChipE1Logic.h"
#include "CBaseCard.h"
#include "ChipRC7883.h"
#include "PortE1.h"
#include "Chip24E1CPLD.h"
#include "E1CardAlarmDataDefine.h"


class CBaseSlot;
class PortE1;
class PairRscSDHChannel;


typedef struct {
    UE1_Config_Data_T port[48];//48个E1口的使能、SNCP保护、描述、长度
    SrcE1Alarm_Data E1AlmData[48];
}Card_ConfigData_48E1;

class E1Card48AlarmModule;

class Card48E1 : public CBaseCard {
	enum{E1_Port_Num=48};
public:
	Card48E1(std::string& name,CBaseSlot* slot);//构造新卡名，归属槽
	virtual ~Card48E1();

	virtual int GetCartTypeID();

	ChipE1Logic& getChipE1Logic(void){
		return chipE1;
	};
	virtual uint8* getConfigDataBuff(void){
		return (uint8*) &ConfigData;
	};
	virtual uint32 getConfigDataLen(void){
		return sizeof(ConfigData);
	};
	virtual void loadDefaultData(void);
    virtual std::string& GetCardVerInfo(){
    	return cardversionInfo;
    }

private:
//	friend TASK void Do_48E1_LED(void* pxc);
    friend class E1Card48AlarmModule;
	ChipE1Logic chipE1;
	ChipRC7883 chipE1Map1;
	ChipRC7883 chipE1Map2;
	PortE1* e1port_obj[E1_Port_Num];
	Card_ConfigData_48E1 ConfigData;
	PairRscSDHChannel* getConnectedSDHChannel(uint32 puid);

	std::string cardversionInfo;
	Chip24E1CPLD cpld;
	OS_TID C48E1_LED;
	E1Card48AlarmModule* AM;

};
#endif /* CARD48E1_H_ */
