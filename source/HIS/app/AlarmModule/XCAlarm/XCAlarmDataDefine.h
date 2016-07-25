/*
 * XCAlarmDataDefine.h
 *
 *  Created on: 2014��8��11��
 *      Author: Administrator
 */


#ifndef XCALARMDATADEFINE_H_
#define XCALARMDATADEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "AlarmDataDefine.h"
#include "DXCAlarmDataDefine.h"

enum {
    R_LOS,
    R_OOF,
    R_LOF,
    MS_AIS,
    MS_RDI,
    MS_REI,
    STM_Signal_Count,
    STM_Sig_BASE = 100
};

enum {
    AU_AIS,
    AU_LOP,
    HP_RDI,
    HP_REI,
    HP_TIM,
    HP_SLM,
    HP_UNEQ,
    VC4_Signal_Count,
    VC4_Sig_BASE = 200
};

enum {
    TU_AIS,
    TU_LOP,
    TU_LOM,
    LP_RDI,
    LP_REI,
    LP_TIM,
    LP_SLM,
    LP_UNEQ,
    VC12_Signal_Count,
    VC12_Sig_BASE = 300
};

enum {
    XE1_LOS,
    XE1_Signal_Count,
    XE1_Sig_BASE = 400
};

typedef struct {
    Alarm_Property_T Property[VC4_Signal_Count];
}SrcVC4Alarm_Data;

typedef struct {
    Alarm_Property_T Property[STM_Signal_Count];
    SrcVC4Alarm_Data VC4AlmData[4];
}SrcSTMAlarm_Data;

typedef struct {
    SrcSTMAlarm_Data STMAlmData[2];
    SrcUpE1Alarm_Data XE1AlmData[4];
}XC_Alarm_Data_T;


#if defined (__cplusplus)
}
#endif
#endif /* XCALARMDATADEFINE_H_ */
