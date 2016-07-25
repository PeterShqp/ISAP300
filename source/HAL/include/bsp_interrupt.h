/*
 * bsp_interrupt.h
 *
 *  Created on: 2013-12-25
 *      Author: Administrator
 */

#ifndef BSP_INTERRUPT_H_
#define BSP_INTERRUPT_H_

#if defined (__cplusplus)
extern "C"
{
#endif

void Dcc_interrupt_enable(void);
void Dcc_interrupt_disable(void);
void SIC_2_Enable(void);
void SIC_2_Disable(void);
void SIC_1_Enable(void);
void SIC_1_Disable(void);

#if defined (__cplusplus)
}
#endif
#endif /* BSP_INTERRUPT_H_ */
