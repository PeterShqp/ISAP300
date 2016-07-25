/*
 * E1CardAlarmDataDefine.h
 *
 *  Created on: 2014Äê9ÔÂ9ÈÕ
 *      Author: Administrator
 */


#ifndef E1CARDALARMDATADEFINE_H_
#define E1CARDALARMDATADEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "AlarmDataDefine.h"

enum {
	E1_LOS,
    E1_Signal_count,
    E1_Sig_Base = 400,
};
typedef struct {
    Alarm_Property_T Property[E1_Signal_count];
}SrcE1Alarm_Data;


//typedef struct {
//    SrcE1Alarm_Data E1AlmData[24];
//}E1Card_Alarm_Data_T;

#if defined (__cplusplus)
}
#endif
#endif /* E1CARDALARMDATADEFINE_H_ */
