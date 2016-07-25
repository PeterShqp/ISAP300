/*
 * Card48E1.cpp
 *
 *  Created on: 2014年5月17日
 *      Author: Administrator
 */
#include "Card48E1.h"
#include "CardTypeID_define.h"
#include "UID.h"
#include "CBaseSlot.h"
#include "PairRscSDHChannel.h"
#include <string.h>
#include "SysError.h"
//#include "GeneralLogic.h"
#include "E1Card48AlarmModule.h"
#include <iostream>


//TASK void Do_48E1_LED(void* pxc);

Card48E1::Card48E1(std::string& name,CBaseSlot* slot):CBaseCard(name,slot),cpld(slot),
			chipE1(slot),chipE1Map1(slot,0x8000,mode_MAP), chipE1Map2(slot,0xa000,mode_MAP_2){
//	if(GeneralLogic::instance().ifColdStart()){
    Chip_INIT_RESULT rst = chipE1.ChipInit();
		if( rst == failed ){
			throw SysError("!!!Card 48E1 E1Logic init error!!!");
		}
		else if( rst == succeed ) {
		    if( chipE1Map1.ChipInit() == failed ){
		        throw SysError("!!!Card 48E1 RC7883-1 init error!!!");
		    }
            if( chipE1Map2.ChipInit() == failed ){
                throw SysError("!!!Card 48E1 RC7883-2 init error!!!");
            }
		}
        else {
            std::cout << chipE1.itsName() << " have been running!" << std::endl;
        }
//	}
	if(!fetchConfig()){
		throw SysError("!!!Card 48E1 config data error!!!");
	}

	ST_E1 info;//记录某槽对应的某一个E1
	info.slot = slot->GetSn();
	for(int i =0;i<E1_Port_Num;++i){
		info.E1 =i;
		uint32 uid =UID::makeUID(&info);
		PairRscSDHChannel* mapLink = getConnectedSDHChannel(uid);
		if(  0 == i /24 ) {
			e1port_obj[i]=new PortE1(uid,mapLink,this,chipE1Map1,&ConfigData.port[i]);//前24个E1口
		}
		else {
			e1port_obj[i]=new PortE1(uid,mapLink,this,chipE1Map2,&ConfigData.port[i]);
		}

	}
//	C48E1_LED =os_tsk_create_ex(Do_48E1_LED,P_LED,this);
	cardversionInfo = cpld.GetVerInfo();

    AM = new E1Card48AlarmModule(this);
    AM->initModule();

}
Card48E1::~Card48E1(){
//    os_tsk_delete(C48E1_LED);
    delete AM;
	for(int i =0;i<E1_Port_Num;++i){
		delete e1port_obj[i];
	}
}
int Card48E1::GetCartTypeID(){
	return E1_48_CARD_TYPEID;
}
PairRscSDHChannel* Card48E1::getConnectedSDHChannel(uint32 puid){//SDH与E1对应连接
	UN_Info e1info = UID::breakUID(puid);//由资源编码推出E1资源所在槽位及E1信号。
	ST_Sdh_channel chinfo;//
	chinfo.slot = e1info.E1.slot;
	chinfo.bus =0;//两条SDHBUS对应着48个E1，只用到其中一条BUS。
	chinfo.channel = e1info.E1.E1;
	uint32 chUID = UID::makeUID(&chinfo);//制作SDH_CHANNEL资源ID
	return PairRscSDHChannel::getInstance(chUID);//通过MAP容器内的SDH_CHANNEL KEY找出对应的CHANNEL
}
void Card48E1::loadDefaultData(void){
	UE1_Config_Data_T temp;
	temp.enable=1;
	memset(temp.sncp,0,8);//copy 8 bytes 0 to temp.sncp array address.
	temp.dlen = 0;
	memset(temp.desc,0,sizeof(temp.desc));
    for (int i = 0; i < 48; ++i) {
        memcpy( &ConfigData.port[i], &temp, sizeof(UE1_Config_Data_T));
        ConfigData.E1AlmData[i].Property[0].level = 2;
    }
}

//TASK void Do_48E1_LED(void* pcard){
//	Card48E1* card = (Card48E1*) pcard;
//	card->chipE1.ledAlmkOn(false);
//	card->chipE1.ledConnectOn(false);
//	card->chipE1.ledDropOn(false);
//	card->chipE1.ledWorkOn(true);
//	while(1){
//		os_dly_wait(100);
//	}
//}
