/*
 * EOSCardAlarmDataDefine.h
 *
 *  Created on: 2014Äê10ÔÂ28ÈÕ
 *      Author: Administrator
 */


#ifndef EOSCARDALARMDATADEFINE_H_
#define EOSCARDALARMDATADEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "AlarmDataDefine.h"

enum {
    VCG_GFP_SynLos,
    VCG_Signal_count,
    VCG_Sig_Base = 500
};
typedef struct {
    Alarm_Property_T Property[VCG_Signal_count];
}SrcVCGAlarm_Data;

#if defined (__cplusplus)
}
#endif
#endif /* EOSCARDALARMDATADEFINE_H_ */
