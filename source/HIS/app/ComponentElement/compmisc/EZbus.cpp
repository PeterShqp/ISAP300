/*
 * EZbus.cpp
 *
 *  Created on: 2013-11-30
 *      Author: Administrator
 */

#include "EZbus.h"
#include "GeneralLogic.h"
#include "os.h"
#include <iostream>
#include "bsp_interrupt.h"
#include "EZLog.h"

OS_MUT mut_ezbus;

EZbus::EZbus(uint32 slt) {
    // TODO Auto-generated constructor stub
    sltSn = slt;
}

EZbus::~EZbus() {
    // TODO Auto-generated destructor stub
}

uint16 EZbus::readReg(uint16 regAddr) {
    uint32 memoryAddr = 0xe3000000 + (regAddr << 1);
    os_mut_wait(mut_ezbus, 0xffff);
    /* �л�CS���ò� */
    GeneralLogic::instance().switchSlotTo(sltSn);
    uint16 v = *((uint16*)memoryAddr);
    os_mut_release(mut_ezbus);
    return v;
}
void EZbus::writeReg(uint16 regAddr, uint16 newData, int opt, uint16 verifyBitMask) {
    if( regAddr == 0xa0a0 ) {
        regAddr = 0xa0a0;
    }
    uint32 memoryAddr = 0xe3000000 + (regAddr << 1);
    os_mut_wait(mut_ezbus, 0xffff);
    /* �л�CS���ò� */
    GeneralLogic::instance().switchSlotTo(sltSn);
    uint16* paddr = (uint16*)memoryAddr;

//    *((uint16*)memoryAddr) = newData;
    *paddr = newData;
    if( opt ) {
        int counter = 10;
        while( counter != 0 ) {
            uint16 RData = *paddr;
            if( (RData & verifyBitMask) == (newData & verifyBitMask) ) {
                break;
            }
            std::cout << "!!!Slot-"<< (int)sltSn <<" EZbus Error!!!" << std::dec << counter << " at:" << std::hex << (int)regAddr <<
                    " Expect: "<< (int)newData << " Actual: "<< (int)RData << std::endl;
            *paddr = newData;
            counter--;
        }
        if( counter == 0 ) {
            EZLog::instance().record("EZbus write Error.");
        }
    }
    os_mut_release(mut_ezbus);
}
