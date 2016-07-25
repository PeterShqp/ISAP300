/*
 * bsp_interrupt.c
 *
 *  Created on: 2013-12-25
 *      Author: Administrator
 */
#include "bsp_interrupt.h"
#include "lpc32xx_intc_driver.h"


void Dcc_interrupt_enable(void) {
    int_enable(IRQ_GPI_03);
}

void Dcc_interrupt_disable(void) {
    int_disable(IRQ_GPI_03);
}

void SIC_2_Enable(void) {
    int_enable(IRQ_SUB2IRQ);
}

void SIC_2_Disable(void) {
    int_disable(IRQ_SUB2IRQ);
}

void SIC_1_Enable(void) {
    int_enable(IRQ_SUB1IRQ);
}

void SIC_1_Disable(void) {
    int_disable(IRQ_SUB1IRQ);
}
