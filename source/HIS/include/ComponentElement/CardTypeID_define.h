/*
 * CardTypeID_define.h
 *
 *  Created on: 2013-11-21
 *      Author: Administrator
 */

#ifndef CARDTYPEID_DEFINE_H_
#define CARDTYPEID_DEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

typedef enum {
    XC_CARD_TYPEID = 30,
    E1_24_CARD_TYPEID,  //24E1
    E1_48_CARD_TYPEID,  //48E1
    EOS_8_CARD_TYPEID,  //8EOS ��
    VF_30_CARD_TYPEID,  //30VF
    PWR_AC_CARD_TYPEID, //AC��Դ
    PWR_DC_CARD_TYPEID, //DC
    FAN_CARD_TYPEID,    //���� 37
    STM_8_CARD_TYPEID,  //8STM֧·��
    STM_4_CARD_TYPEID,  //4STM֧·��
    VF_16_CARD_TYPEID,  //16VF
    VF_8_CARD_TYPEID,   //8VF/10VF
    EOS_8X_CARD_TYPEID, //8EOS ��
    E1_16_CARD_TYPEID,  //16E1
    EOS_4X_CARD_TYPEID, //4EOS ��
    EOS_4_CARD_TYPEID,  //4EOS ��
    EOS_8N_CARD_TYPEID, //8EOS ��
    EOS_8XN_CARD_TYPEID, //8EOS ��
    EOS_4XN_CARD_TYPEID, //4EOS ��
    EOS_4N_CARD_TYPEID,  //4EOS ��
    DATA_16_CARD_TYPEID,//16DATA:TYPEID=50
    V5_CARD_TYPEID,
    DXC_CARD_TYPEID,
    FE1_16_CARD_TYPEID,
    FXS_32_CARD_TYPEID,
    FXO_32_CARD_TYPEID, // typeid = 55
    MT_30_CARD_TYPEID,
    PCMXC_CARD_TYPEID,
    DATA_8_CARD_TYPEID,
    VF_8N_CARD_TYPEID,  //8VF New

} all_card_type;


enum {
    value_24E1 = 0xa9cd,
    value_48E1 = 0xa982,
    value_8EOS = 0xa983,
    value_30VF = 0xa984,
    value_4STM = 0xa985,
    value_8STM = 0xa986,
    value_16VF = 0xa994,
    value_8VF  = 0xa9a4,
    value_32FXS= 0xa9b4,
    value_32FXO= 0xa9c4,
    value_30MT = 0xa9d4,
    value_8EOSX= 0xa987,
    value_16E1 = 0xa988,
    value_4EOS = 0xa989,
    value_4EOSX= 0xa98a,
    value_4EOS2= 0xa98c,
    value_4EOSX2=0xa98e,
    value_8EOS2= 0xa98d,
    value_8EOSX2=0xa98f,
    vlaue_16DATA=0xa990,
    value_V5    =0xa991,
    value_16FE1 =0xa992,
    value_8DATA =0xa9b0,
    value_8VF_N =0xa9e4,
};

#if defined (__cplusplus)
}
#endif
#endif /* CARDTYPEID_DEFINE_H_ */
