/*
 * DXCAlarmModule.cpp
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */

#include "DXCAlarmModule.h"
#include "CardDXC.h"
#include "SrcAlarmUpE1.h"
#include "CExtE1.h"
#include "PortFE1.h"
#include "ObjectReference.h"
#include "CardFAN.h"
#include "FANPOWModule.h"
#include "CmdRing.h"
#include <stdio.h>

TASK void Do_DXC_LED(void* dxc);
DXCAlarmModule::DXCAlarmModule(CardDXC* c) : BAlarmModule(c) {
    // TODO Auto-generated constructor stub
    XCCard = c;
    dxc_alarm = os_tsk_create_ex(Do_DXC_LED, P_LED, this);
}

DXCAlarmModule::~DXCAlarmModule() {
    os_tsk_delete(dxc_alarm);
}

void DXCAlarmModule::creatAlarmSource() {
    for (int i = 0; i < 4; ++i) {
        addAlmSrc( new SrcAlarmUpE1(i, this, static_cast<RealPortBase*>(XCCard->fe1_obj[i]),
                &(XCCard->AlarmData.UpE1AlmData[i]), XCCard->fpga ) );
    }
}

void DXCAlarmModule::turnLedMajOn(bool on) {
    XCCard->fpga.turnOnLedMaj(on);
}
void DXCAlarmModule::turnLedMinOn(bool on) {
    XCCard->fpga.turnOnLedMin(on);
}


TASK void Do_DXC_LED(void* pxc) {
    DXCAlarmModule* xc = (DXCAlarmModule*)pxc;
    uint8 ring = 0;
    uint8 ringBak = 0;
    while(1) {
        os_dly_wait(300);
        bool maj = false;
        bool min = false;
        BAlarmModule* mm = BAlarmModule::getFirstInstance();
        while( mm ) {
            if( !maj ) {
                maj = mm->ifHaveMAJ();
            }
            if( !min ) {
                min = mm->ifHaveMin();
            }
            mm = BAlarmModule::getNextInstance(mm->itsSn());
        }
        if( maj ) {
            //�������澯��
            xc->turnLedMajOn(true);
            ring = 1;
        }
        else {
            //�����澯��
            xc->turnLedMajOn(false);
            ring = 0;

       }
        if( min ) {
            //������Ҫ�澯��
            xc->turnLedMinOn(true);
        }
        else {
            //���Ҫ�澯��
            xc->turnLedMinOn(false);
       }
        if( ObjectReference::getFANCard() ) {
            if( ObjectReference::getFANCard()->getBuzzerCfg() == 0 ) {
                ring = 0;
            }

            if( ring != ringBak ) {
                ringBak = ring;
                FANPOWModule mod;
                CmdRing cmd(ring);
                if( mod.processFANCommand(cmd) == DEFErrorSuccess ) {
                    #ifdef EZ_DEBUG
                    uint8* result = cmd.getResultBuff();
                    if( result[1] != 0x5a ) {
                        printf("\n!!!CmdRing Error!!!");
                    }
                    #endif
                }
                else {
                    printf("\n!!!processFANCommand Error!!!");

                }
            }
        }
    }
}
