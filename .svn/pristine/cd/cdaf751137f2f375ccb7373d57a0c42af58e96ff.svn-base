/*
 * EmuXCAlarmDataDefine.h
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */


#ifndef DXCALARMDATADEFINE_H_
#define DXCALARMDATADEFINE_H_

#if defined (__cplusplus)

#include "AlarmDataDefine.h"

extern "C"
{
#endif


enum {
    UpE1_LOS,
    UpE1_AIS,
    UpE1_LOF,
    UpE1_LOMF,
    UpE1_Signal_Count,
    UpE1_Sig_BASE = 400
};

typedef struct {
    Alarm_Property_T Property[UpE1_Signal_Count];
}SrcUpE1Alarm_Data;

typedef struct {
    SrcUpE1Alarm_Data UpE1AlmData[4];
}DXC_Alarm_Data_T;

typedef struct {
    SrcUpE1Alarm_Data UpE1AlmData[16];
}FE116_Alarm_Data_T;

#if defined (__cplusplus)
}
#endif
#endif /* DXCALARMDATADEFINE_H_ */
