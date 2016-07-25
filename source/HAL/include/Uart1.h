/*
 * Uart2Fan.h
 *
 *  Created on: 2015Äê2ÔÂ26ÈÕ
 *      Author: Administrator
 */

#ifndef UART1_H_
#define UART1_H_
#include <LPC_TYPES.H>
#if defined (__cplusplus)
extern "C"
{
#endif
void huartInit(void);
void huart_dat_out(UNS_8 *dat, int bytes);
int huart_dat_in(UNS_8 *buff, int bytes);
#if defined (__cplusplus)
}
#endif /*__cplusplus */

#endif /* UART2FAN_H_ */
