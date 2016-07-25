/*
 * ResetModule.cpp
 *
 *  Created on: 2014-3-20
 *      Author: Administrator
 */

#include "ResetModule.h"
#include "os.h"
#include <iostream>

OS_TID t_reset;
TASK void T_Device_Reset(void);


ResetModule::ResetModule() {
    t_reset = os_tsk_create(T_Device_Reset, P_Reset);

}

ResetModule::~ResetModule() {
    // TODO Auto-generated destructor stub
}


void resetSoftware(void) {
    os_evt_set(0x0001, t_reset);
}
bool resetCard(int sn);
void resetDevice(void);

TASK void T_Device_Reset(void) {
    os_evt_wait_or(0x0003, 0xffff);
    uint16 flgEvent = os_evt_get();

    if( flgEvent == 0x0001 ) {
        std::cout << "MCU will restart!" << std::endl;
    }
    else if( flgEvent == 0x0002 ) {
    }


}
