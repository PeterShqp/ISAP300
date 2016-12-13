#ifndef TrapList_CPP
#define TrapList_CPP

#include "TrapList.h"
#include "SNMPDefine.h"
#include "SNMPPdu.h"
#include "TimeTicks.h"
#include "Integer32.h"
#include "AlarmRecord.h"
#include "EthMemory.h"
#include <string.h>
#include "DeviceComponent.h"
#include "DeviceAttribute.h"
#ifdef EZ_DEBUG
#include <stdio.h>
#endif

extern "C" void SendFrameBySwitch(LAYER2FRAME* frame);

uint32 OIDImplTimeticks[] = { 1, 3, 6, 1, 2, 1, 1, 3, 0 };//time
uint32 OIDTrapFix[] = { 1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0 };//TRAP OID

uint32 OIDImplEventID[] =  { 1, 3, 6, 1, 4, 1, 25449, 1, 1, 12, 2, 0 };
uint32 OIDImplTrapItem[] = { 1, 3, 6, 1, 4, 1, 25449, 1, 1, 12, 3, 0 };

TASK void tsk_trap(void);

uint16 udp_listen_ack(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len) {
    return 0;
}

TrapList TrapList::t;

TrapList::TrapList(void) {

    memset((uint8*) &trapBuffer, 0, sizeof(TrapBuffer) * TrapMaxNumber);
    currentIndex = 0;
    endIndex = 0;
    soc_massage = 0;
    tsk_send_trap = 0;
    inited = false;

}
TrapList::~TrapList(void) {
}
void TrapList::Initial(void) {
    soc_massage = udp_get_socket(0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_listen_ack);
    if( soc_massage == 0 ) {
        printf("\n!!!soc_massage = udp_get_socket failed!!!\n");
        return ;
    }
    if( !udp_open( soc_massage, 162 ) ) {
        udp_release_socket(soc_massage);
        return ;
    }
    tsk_send_trap = os_tsk_create(tsk_trap, P_FILE_SYNC);
    inited = true;
}

void TrapList::deInitial(void) {
    if( inited ) {
        os_tsk_delete(tsk_send_trap);
        udp_close(soc_massage);
        udp_release_socket(soc_massage);
    }
}

/*
 * 生成告警产生报文，并加入到发送队列
 */
void TrapList::insertNewAlarmTrap(AlarmRecord *record) {
    makeAlarmTrapDatagram(alarm_raise, record);
}

void TrapList::insertRecoveryAlarmTrap(AlarmRecord *record, uint32 timetick) {
    makeAlarmTrapDatagram(alarm_clear, record);
}


void TrapList::makeAlarmTrapDatagram(Alarm_Trap_type_E type, AlarmRecord *record) {

    if( !inited ) {
        return;
    }
    if (record == NULL)
        return;

    /*检查trapbuf是否满*/
    if (endIndex != currentIndex) {
        //�Ƿ�buffer������� ����
        if ((endIndex == TrapMaxNumber - 1) && currentIndex == 0) {
            return;
        } else if ((endIndex + 1) == currentIndex) {
            return;
        }
    }

    /*VBS 初始化*/
    OIDImplTrapItem[10] = 3;
    OIDImplEventID[10] = 2;
    SNMPPdu pdu;
    pdu.commond = SNMPPdu::TRAP;
    VariableBinding vb[5];
    pdu.variableBindings.variableBinding = vb;
    pdu.variableBindings.vbsLength = 5;

    /*1.3.6.1.2.1.1.3.0 Timeticks*/
    OID oid1(OIDImplTimeticks, 9);
    pdu.variableBindings.getAt(0)->setOID(&oid1);
    TimeTicks value1(record->itsRaiseTime());
    pdu.variableBindings.getAt(0)->setValue(&value1);

    /*1.3.6.1.6.3.1.1.4.1.0 TrapOID*/
        /*1.3.6.1.4.1.25449.1.1.12.2.type alarmType*/

    OID oid2(OIDTrapFix, 11);
    pdu.variableBindings.getAt(1)->setOID(&oid2);
    OIDImplEventID[11] = record->itsAlarmType();
    if( type == alarm_clear ) {
        OIDImplEventID[11] |= 0x8000;
    }
    OID value2(OIDImplEventID, 12);
    pdu.variableBindings.getAt(1)->setValue(&value2);

    /*1.3.6.1.4.1.25449.1.1.12.3.1 alarm sn*/
    OIDImplTrapItem[11] = 1;
    OID oid3(OIDImplTrapItem, 12);
    pdu.variableBindings.getAt(2)->setOID(&oid3);
    Integer32 value3(record->itsSN());
    pdu.variableBindings.getAt(2)->setValue(&value3);

    //Alarm source ID
    /*1.3.6.1.4.1.25449.1.1.12.3.2 Alarm source ID*/
    OIDImplTrapItem[11] = 2;
    OID oid4(OIDImplTrapItem, 12);
    pdu.variableBindings.getAt(3)->setOID(&oid4);
    Integer32 value4(record->itsAlarmSource());
    pdu.variableBindings.getAt(3)->setValue(&value4);

    //Alarm level
    /*1.3.6.1.4.1.25449.1.1.12.3.3 Alarm level*/
    OIDImplTrapItem[11] = 3;
    OID oid5(OIDImplTrapItem, 12);
    pdu.variableBindings.getAt(4)->setOID(&oid5);
    Integer32 value5(record->itsAlarmLevel());
    pdu.variableBindings.getAt(4)->setValue(&value5);

    int pklen = pdu.getPDUBerLength();
    int buflen = pklen + 1 + SNMPPdu::getLengthBerLength(pklen);

    ///unsigned char *buf = new unsigned char[buflen];
    if (pdu.encode((unsigned char*) trapBuffer[endIndex].buffer, buflen,
            pklen)) {
        trapBuffer[endIndex].buffersize = buflen;
        trapBuffer[endIndex].valid = 1;
    } else {
        trapBuffer[endIndex].buffersize = 0;
        trapBuffer[endIndex].valid = 0;
    }

    pdu.variableBindings.variableBinding = NULL;
    endIndex++;
    if (endIndex >= TrapMaxNumber) {
        endIndex = 0;
    }

}


bool TrapList::isHasTrapItem() {
    if (endIndex != currentIndex)
        return true;
    else
        return false;
}
void TrapList::sendaTrapItem() {

    if (endIndex == currentIndex)
        return;
    uint8* beSend = trapBuffer[currentIndex].buffer;
    uint16 sendLen = trapBuffer[currentIndex].buffersize;
    uint8* send_buff = udp_get_buf(sendLen);
    if( send_buff == 0 ) {
#ifdef EZ_DEBUG
        printf("\nTrapList::sendaTrapItem error udp_get_buf\n");
#endif
        return;
    }
    uint8 trapIP[4];
    DeviceComponent::getDeviceAttribute().getTrapDestIP(trapIP);
    memcpy( send_buff, beSend, sendLen );

//    while( arp_cache_ip(trapIP, ARP_FIXED_IP) != __TRUE ) {
//        if( !Protected ) {
//#ifdef EZ_DEBUG
//        strcpy(msg_ack, "Remote loss");
//#endif
//            return;
//        }
//        os_dly_wait(100);
//    };
    if( udp_send(soc_massage, trapIP, 162, send_buff, sendLen) != __TRUE ) {
#ifdef EZ_DEBUG
		printf("\nTrapList::sendaTrapItem error udp_send\n");
#endif
        return;
    }

    trapBuffer[currentIndex].valid = 0;
    currentIndex++;
    if (currentIndex >= TrapMaxNumber) {
        currentIndex = 0;
    }
}

bool TrapList::ifTrapDestExist() {
    uint8 trapIP[4];
    DeviceComponent::getDeviceAttribute().getTrapDestIP(trapIP);
    if( arp_cache_ip(trapIP, ARP_FIXED_IP) != __TRUE ) {
        return false;
    }
    return true;
}


TASK void tsk_trap(void)		//��������
{
    while( 1 ) {
        if( TrapList::instance().ifTrapDestExist() ) {
            os_dly_wait(100);
            while( TrapList::instance().isHasTrapItem() ) {
                TrapList::instance().sendaTrapItem();
            }
        }
        else {
//#ifdef EZ_DEBUG
//        printf("\n!!!Trap destination unreanchable!!!\n");
//#endif
            os_dly_wait(6000);
        }
    }
}

#endif

