/*
 * sysapi.h
 *
 *  Created on: 2013-10-11
 *      Author: Administrator
 */

#ifndef SYSAPI_H_
#define SYSAPI_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "lpc_types.h"
/***********************************************************************
 * Exception handler structures and functions
 **********************************************************************/

/* Exception data structure */
typedef struct
{
    UNS_32 cpsr;
    UNS_32 spsr;    /* Previous status */
    UNS_32 lr;      /* Exception address */
    UNS_32 r[13];   /* Registers */
} EXCEPT_DATA_T;
extern EXCEPT_DATA_T excdata;

/* Displays exception data when an exception occurs */
void trap_exception(void);

/* Prototype for exception pre-handler */
void arm9_exchand(void);

void int_enable_eth_real(void);
void int_disable_eth_real(void);

#if defined (__cplusplus)
}
#endif
#endif /* SYSAPI_H_ */
