/*
 * XCConfigDataDefine.h
 *
 *  Created on: 2015年7月4日
 *      Author: Administrator
 */


#ifndef XCCONFIGDATADEFINE_H_
#define XCCONFIGDATADEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "STMConfigDataDefine.h"
#include "FE1ConfigDataDefine.h"

typedef struct {
    STM_Config_Data_T stmport[2];
    FE1_Config_Data_T fe1port[4];
}Card_ConfigData_XC;

#if defined (__cplusplus)
}
#endif
#endif /* XCCONFIGDATADEFINE_H_ */
