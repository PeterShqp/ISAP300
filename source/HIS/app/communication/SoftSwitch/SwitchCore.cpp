/*
 * SwitchCore.cpp
 *
 *  Created on: 2013-6-24
 *      Author: Administrator
 *
 *      NOTE:
 *      1. Ϊʹ���?�����ܣ��ڵ������й��ú���ǰ��������initSwitchCore()
 *      2. �?���ں�Ϊ����ϵͳ��ֻ����һ�����󣬵���ʱ���� SwitchCore::instance()����
 */

#include "SwitchCore.h"
#include "PriPacket.h"
#include "SwitchPort.h"
#include "TerminalUart.h"
#include "TopoManager.h"
#include "stdio.h"
#include "SoftWDT.h"

SwitchCore SwitchCore::sw;
os_mbx_declare(mbox_sw_input, 128);
static TASK void task_sw_proccess(void);
static TASK void taskCheckBroadcastFilter(void);

SwitchCore::SwitchCore() {
    t_sw_proccess = 0;
    t_broad_filter = 0;
    bcfilt = false;
}

SwitchCore::~SwitchCore() {
	// TODO Auto-generated destructor stub
}

/*
 * �?���ں˳�ʼ��
 * 1. ��Ϣ���г�ʼ��
 * 2. ������������
 */
void SwitchCore::initSwitchCore(void) {
#ifdef EXT_DBG
    printf("\ninitSwitchCore() start.\n");
#endif
    os_mbx_init(mbox_sw_input, sizeof(mbox_sw_input));
    t_sw_proccess = os_tsk_create(task_sw_proccess, P_SW_Process);
    t_broad_filter = os_tsk_create(taskCheckBroadcastFilter, P_LED);
#ifdef EXT_DBG
    printf("\ninitSwitchCore() end.\n");
#endif
}

/*
 * �?���ں�ת��һ����ݰ�
 * 1. ����
 * 2. ѧϰ
 * 3. ��ݰ����ʹ���
 * ����ֵ -1 δת������Ҫ�����߸���ɾ��pkt
 * ����ֵ 1 �ɹ�ת��
 */
int SwitchCore::transmitAPacket(PriPacket& pkt) {
    if( pkt.packetType() == multicast ) {
#ifdef SW_DEBUG
        printf("multicast\n");
#endif
        TopoManager::proccessTopoSearch(pkt);
        return 0;
    }
	if( finishedPkt.finished(pkt) ) {
#ifdef SW_DEBUG
        printf("the packet %d has already been transmit!\n", pkt.getPrivateTag().sn);
#endif
		return -1;
	}

	finishedPkt.finishThePacket(pkt);
	macPortTable.learnAddress(pkt);

#ifdef SW_DEBUG
	printf("pkt %d type is: ", pkt.getPrivateTag().sn);
#endif

	switch( pkt.packetType() ) {

	case unicast: {
#ifdef SW_DEBUG
	    printf("unicast\n");
#endif
        SwitchPort* p = SwitchPort::getSwitchPort(macPortTable.findOutputPort(pkt));
        if( p ) {
            return p->outputAPacket(pkt);
        }
        else {
#ifdef SW_DEBUG
            printf("discard the packet %d\n", pkt.getPrivateTag().sn);
#endif
        }
	}
	break;

	case broadcast:{
	    SwitchPort::broadcastThePacket(pkt);
//		if( !broadcastFilter() ) {
//#ifdef SW_DEBUG
//        printf("broadcast\n");
//#endif
//        os_evt_set(0x0001, t_broad_filter);
//        return SwitchPort::broadcastThePacket(pkt);
//		}
	}
		break;
//	case multicast:
//#ifdef SW_DEBUG
//        printf("multicast\n");
//#endif
//		TopoManager::proccessTopoSearch(pkt);
	default:
		break;
	}
	return -1;

}

/*
 * �ϻ��Ѵ�����MAC��ַѧϰ��
 */
void SwitchCore::aging(void) {
    finishedPkt.aging();
    macPortTable.aging();
}

/*
 * �κ��?���˿��յ�����ô˺������?���ں˴��?������봦����У�
 */
bool SwitchCore::inputAPacket(PriPacket* p) {
    if( os_mbx_check(mbox_sw_input) == 0 ) {
#ifdef EZ_DEBUG
        printf("!!!SwitchCore::inputAPacket buff full!!!\n");
#endif
        p->deletePacket();
        return false;
    }
    os_mbx_send(mbox_sw_input, p, 0xffff);
    return true;
}

/*
 * �?����������
 * ����Ϣ������ȡһ����ת�������ת��ʧ�ܣ�����ɾ����ݰ�
 */
TASK void task_sw_proccess(void) {
    void* amsg = 0;
    WDT_Para_T sw;
    SoftWDT::instance().add(os_tsk_self(), &sw);
    while( 1 ) {
        OS_RESULT rst = os_mbx_wait(mbox_sw_input, &amsg, 100);
        if( rst != OS_R_TMO ) {

    #ifdef SW_DEBUG
            printf("transmit packet ");
    #endif
            PriPacket* p = reinterpret_cast<PriPacket*>(amsg);
            if( p ) {
    #ifdef SW_DEBUG
                printf("%d start!\n", p->getPrivateTag().sn);
    #endif
                if( SwitchCore::instance().transmitAPacket(*p) < 0 ) {
                    p->deletePacket();
                }
            }
            else {
    #ifdef SW_DEBUG
                printf("%d Error NULL PriPacket!\n", p->getPrivateTag().sn);
    #endif
            }
        }
        SoftWDT::instance().feed(os_tsk_self());
    }
}

TASK void taskCheckBroadcastFilter(void) {
	while(1) {
		os_evt_wait_or(0x0001, 0xffff);
		SwitchCore::instance().startFilter();
		os_dly_wait(100);
		SwitchCore::instance().stopFilter();
	}
}
