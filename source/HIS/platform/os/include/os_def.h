/*
 * os_def.h
 *
 *  Created on: 2013-9-24
 *      Author: Administrator
 */

#ifndef OS_DEF_H_
#define OS_DEF_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include <rtl.h>
#include "EZ_types.h"

#define INTR_HANDLER    __irq
#define __OS_INIT__     rtx_os_init
#define TASK            __task


void rtx_os_init(void);



static const uint8 P_Reset          = 1;
static const uint8 P_WDT            = 250;
static const uint8 P_LED_RUN        = 2;
static const uint8 P_SYNC           = 20;
static const uint8 P_Agint_MAC      = 4;
static const uint8 P_CFG_Store      = 5;
static const uint8 P_Loop_Process   = 6;
static const uint8 P_Alarm_Process  = 7;
static const uint8 P_SAVE           = 8;
static const uint8 P_LED            = 10;
static const uint8 P_FAST_CHECK     = 40;
static const uint8 P_ClkSrc_process = 50;
static const uint8 P_CLI_Process    = 201;
static const uint8 P_Protect		= 90;
static const uint8 P_Online_Check   = 16;
static const uint8 P_SW_Process     = 95;
static const uint8 P_ETH_RCV        = P_SW_Process - 2;
static const uint8 P_DCC_RCV        = P_ETH_RCV - 1;
static const uint8 P_PORT_Send      = P_SW_Process - 4;
static const uint8 P_TCP_Main       = 100;
static const uint8 P_TCP_Time       = P_TCP_Main+1;

static const uint8 P_FILE_SYNC      = 15;

#if defined (__cplusplus)
}
#endif
#endif /* OS_DEF_H_ */
