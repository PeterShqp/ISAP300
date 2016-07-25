/*
 * EosCardConfigDefine.h
 *
 *  Created on: 2014��12��23��
 *      Author: Administrator
 */


#ifndef EOSCARDCONFIGDEFINE_H_
#define EOSCARDCONFIGDEFINE_H_

#include "EosCardAlarmDataDefine.h"
#if defined (__cplusplus)
extern "C"
{
#endif
typedef struct {
    uint8 sncp; //������������
}CHVC_ConfigData_T;

typedef struct {
    uint8 enable;
    uint8 lcas;
    uint8 descLen;
    uint8 desc[32];
    uint8 flow;
    uint8 memberNum;
    uint32 member[63];
}VCG_ConfigData_T;

typedef struct {
    CHVC_ConfigData_T chvc[126];
    VCG_ConfigData_T vcg[8];
    SrcVCGAlarm_Data VCGAlmData[8];
}Card_ConfigData_8EOS;

typedef struct {
    CHVC_ConfigData_T chvc[126];
    VCG_ConfigData_T vcg[4];
    SrcVCGAlarm_Data VCGAlmData[4];
}Card_ConfigData_4EOS;

#if defined (__cplusplus)
}
#endif
#endif /* EOSCARDCONFIGDEFINE_H_ */
