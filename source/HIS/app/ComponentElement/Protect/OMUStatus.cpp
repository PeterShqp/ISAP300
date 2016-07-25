/*
 * OMUStatus.cpp
 *
 *  Created on: 2014��11��27��
 *      Author: Administrator
 */

#include "OMUStatus.h"
#include "os.h"
#include <LPC325x.h>                    /* LPC325x definitions               */

#define LED_RUN   (1<<12)

#define LED_ON(led)  P3_OUTP_CLR = led;
#define LED_OFF(led) P3_OUTP_SET = led;

TASK void toggleRun (void* dly) {
    uint8 delay = *((uint8*)dly);
    for (;;) {
        LED_ON (LED_RUN);
        os_dly_wait (delay);
        LED_OFF(LED_RUN);
        os_dly_wait (delay);
    }
}

OMUStatus::OMUStatus(uint8 delay) {
    dly_times = delay;
    led_run = os_tsk_create_ex(toggleRun, P_LED_RUN, &dly_times);
    Locked = true;
}

OMUStatus::~OMUStatus() {
    os_tsk_delete(led_run);
}

