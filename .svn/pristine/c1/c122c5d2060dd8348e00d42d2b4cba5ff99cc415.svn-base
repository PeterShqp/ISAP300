/*
 * FE1ConfigDataDefine.h
 *
 *  Created on: 2015年7月4日
 *      Author: Administrator
 */


#ifndef FE1CONFIGDATADEFINE_H_
#define FE1CONFIGDATADEFINE_H_

#include "EZ_types.h"

#if defined (__cplusplus)
extern "C"
{
#endif

typedef struct {
    uint32 bitMap; //dcn时表示ts时隙位图，dcc时，表示sabit或OH开销占用
}NM_CH_ConfigData_T;

typedef struct {
    uint8 porten; //1 加入交换体系（与软交换端口绑定、ch中断打开）， 0 不参与交换（解绑软交换端口、ch中断关闭）
    uint8 type;   //0 dcc, 1 dcn;
    uint8 topodir; //对应软交换端口ID
    uint8 desc[32];
    uint8 descLen;
    NM_CH_ConfigData_T sabitCH;
    NM_CH_ConfigData_T dcnCH;
}FE1_NM_Config_Data_T;

typedef struct {
    uint8 TXEN;
    char Desc[32];
    uint8 DescLen;
    FE1_NM_Config_Data_T nmportCfg;
}FE1_Config_Data_T;


#if defined (__cplusplus)
}
#endif
#endif /* FE1CONFIGDATADEFINE_H_ */
