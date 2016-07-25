/*
 * sysapi_misc.c
 *
 *  Created on: 2013-10-11
 *      Author: Administrator
 */

#include "lpc_irq_fiq.h"
#include "lpc32xx_intc_driver.h"
#include "sysapi.h"
#include "TerminalUart.h"
#include "lpc_string.h"
#include "os.h"
#include <LPC325x.H>                    /* LPC325x definitions               */

/* Prototype for external IRQ handler */
void lpc32xx_irq_handler(void);
void SWI_Handler(void);


EXCEPT_DATA_T excdata;

static UNS_8 undef_msg[] = "Undefined instruction";
static UNS_8 dabort_msg[] = "Data abort";
static UNS_8 excunk_msg[] = "Unknown exception";
static UNS_8 excty_msg[] = "Exception: ";
static UNS_8 spsr_msg[] = " CPSR value at exception: ";
static UNS_8 lr_msg[]   = " Exception address      : ";
static UNS_8 rx_msg[]   = " Register value :";
static UNS_8 rx1_msg[]   = " (r";
static UNS_8 rx2_msg[]   = ")";
static UNS_8 sd_msg[] = "System is down. Reset system";

/*
 * 初始化中断向量表
 * 中断向量表拷贝到内部ram地址0后调用该API函数。
 * 注意：该函数只能在SVC模式下调用，系统正常运行后不能调用！
 */
void sys_initial_intr_vec(void) {
    /* Disable interrupts in ARM core */
    disable_irq_fiq();
    /* Initialize interrupt system */
    int_initialize(0xFFFFFFFF);

    /* Install standard IRQ dispatcher at ARM IRQ vector */
    int_install_arm_vec_handler(IRQ_VEC, (PFV) lpc32xx_irq_handler);

    /* Install exception handler */
    int_install_arm_vec_handler(UNDEFINED_INST_VEC, (PFV) arm9_exchand);
    int_install_arm_vec_handler(PREFETCH_ABORT_VEC, (PFV) arm9_exchand);
    int_install_arm_vec_handler(DATA_ABORT_VEC, (PFV) arm9_exchand);
    int_install_arm_vec_handler(SWI_VEC, (PFV)SWI_Handler);
    int_install_arm_vec_handler(RESET_VEC, (PFV)(0x80000000));
//    enable_irq_fiq();

    /* Install mstimer interrupts handlers as a IRQ interrupts */
//    int_install_irq_handler(IRQ_HSTIMER, (PFV) os_clock_interrupt);

}



/***********************************************************************
 *
 * Function: trap_exception
 *
 * Purpose: Displays exception data when an exception occurs
 *
 * Processing:
 *     See function.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void trap_exception(void)
{
    UNS_8 str [16], *pstr;
    int idx;

    term_dat_out_crlf((UNS_8 *) "");

    /* Determine exception type */
    switch (excdata.cpsr & 0x0F)
    {
        case 0xB:
            /* Undefined instruction */
            pstr = undef_msg;
            break;

        case 0x7:
            /* Data abort */
            pstr = dabort_msg;
            break;

        default:
            /* Unknown */
            pstr = excunk_msg;
            break;
    }

    /* Exception type */
    term_dat_out(excty_msg);
    term_dat_out_crlf(pstr);

    /* CPSR and exception address */
    term_dat_out(spsr_msg);
    str_makehex(str, excdata.spsr, 8);
    term_dat_out_crlf(str);
    term_dat_out(lr_msg);
    str_makehex(str, excdata.lr, 8);
    term_dat_out_crlf(str);

    /* Dump registers */
    for (idx = 0; idx <= 13; idx++)
    {
        term_dat_out(rx_msg);
        str_makehex(str, excdata.r[idx], 8);
        term_dat_out(str);
        term_dat_out(rx1_msg);
        str_makedec(str, (UNS_32) idx);
        term_dat_out(str);
        term_dat_out_crlf(rx2_msg);
    }

    term_dat_out_crlf(sd_msg);

    while (1);
}

void int_enable_eth_real (void) {
    /* Ethernet Interrupt Enable function. */
	MIC_ER |=  (1 << 29);
}

void int_disable_eth_real (void) {
    /* Ethernet Interrupt Disable function. */
    MIC_ER &= ~(1 << 29);
}

