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
//static TASK void taskCheckBroadcastFilter(void);
extern "C" void broadcastTimerOver(void);

SwitchCore::SwitchCore() {
    t_sw_proccess = 0;
//    t_broad_filter = 0;
//    bcfilt = false;
    bcCount = 0;
    MaxBroadcastPerSec = 5;
    timer_filter_broadcast = NULL;
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
//    t_broad_filter = os_tsk_create(taskCheckBroadcastFilter, P_LED);
#ifdef EXT_DBG
    printf("\ninitSwitchCore() end.\n");
#endif
}

void SwitchCore::resetSwitchCore(void) {
    finishedPkt.clear();
    macPortTable.clear();
    ipPortTable.clear();
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
    	pkt.recordProcessInfo(141);
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
    	pkt.recordProcessInfo(142); //.have been finished
        return -1;
	}

	finishedPkt.finishThePacket(pkt);
	macPortTable.learnAddress(pkt);
	ipPortTable.learnAddress(pkt);
#ifdef SW_DEBUG
	printf("pkt %d type is: ", pkt.getPrivateTag().sn);
#endif

	switch( pkt.packetType() ) {

	case unicast: {
#ifdef SW_DEBUG
	    printf("unicast\n");
#endif
    	pkt.recordProcessInfo(143); //.type is unicast

	    SwitchPort* p = SwitchPort::getSwitchPort(macPortTable.findOutputPort(pkt));
        if( p ) {
        	pkt.recordProcessInfo(144); //.will be output
            return p->outputAPacket(pkt);
        }
        else {
        	pkt.recordProcessInfo(145); //.Can't find output port

#ifdef SW_DEBUG
            printf("discard the packet %d\n", pkt.getPrivateTag().sn);
#endif
        }
	}
	break;

	case broadcast:{
    	pkt.recordProcessInfo(1412);//.type is broadcast
		if( !broadcastFilter() ) { //计数器满，则停止转发广播
    #ifdef SW_DEBUG
            printf("broadcast\n");
    #endif
            int portsn = ipPortTable.findOutputPort(pkt); //查找是否有已学习到的ip地址
            if( portsn < 0 ) {
                return SwitchPort::broadcastThePacket(pkt); //无记录则广播
            }
            else {
                //有记录则单播
                SwitchPort* objPort = SwitchPort::getSwitchPort(portsn);
                if( objPort ) {
                    return objPort->outputAPacket(pkt);
                }
                else {
#ifdef SW_DEBUG
        printf("no SwitchPort\n");
#endif
                }
            }
		}
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
    ipPortTable.aging();
}

/*
 * �κ��?���˿��յ�����ô˺������?���ں˴��?������봦����У�
 */
bool SwitchCore::inputAPacket(PriPacket* p) {
	p->recordProcessInfo(121);
    if( os_mbx_check(mbox_sw_input) == 0 ) {
#ifdef EZ_DEBUG
        printf("!!!SwitchCore::inputAPacket buff full!!!\n");
#endif
        p->deletePacket();
        return false;
    }
    os_mbx_send(mbox_sw_input, p, 0xffff);
	p->recordProcessInfo(122);

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
            	p->recordProcessInfo(131);
                if( p->ifValid() ) { //增加包类型检查，只有ARP和IP和多播包认为有效
                	p->recordProcessInfo(132);
        #ifdef SW_DEBUG
                    printf("%d start!\n", p->getPrivateTag().sn);
        #endif
                    if( SwitchCore::instance().transmitAPacket(*p) < 0 ) {
                        p->deletePacket();
                    }
                }
                else {
                    p->deletePacket();
#ifdef SW_DEBUG
            printf("%d invalid PriPacket!\n", p->getPrivateTag().sn);
#endif
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

//TASK void taskCheckBroadcastFilter(void) {
//    uint32 filterCount = 0;
//    uint8 MaxBroadcastPerSec = 5;
//	while(1) {
//		os_evt_wait_or(0x0001, 0xffff);
//		if( (++filterCount % MaxBroadcastPerSec) == 0 ) {
//            SwitchCore::instance().startFilter();
//            os_dly_wait(100);
//            SwitchCore::instance().stopFilter();
//		}
//	}
//}
//bool SwitchCore::broadcastFilter(void) {
//    if( bcCount > MaxBroadcastPerSec ) {
//        return true;
//    }
//    if( timer_filter_broadcast == NULL ) { //当没有timer是创建
//        timer_filter_broadcast = os_tmr_create(100, 1);
//        if( timer_filter_broadcast == NULL ) {
//#ifdef EZ_DEBUG
//            printf("\nos_tmr_create failed!!!\n");
//#endif
//            return true; //超时timer建立失败，则停止转发广播
//        }
//    }
//    ++bcCount;
//    return false;
//}

bool SwitchCore::broadcastFilter(void) {
	static uint32 lastTicks = 0;
	uint32 actTicks = os_time_get();
	if( (actTicks - lastTicks) > 100 ) {
		//已经是新的时间段，可以正常转发
		lastTicks = actTicks; //记录新时间段的起点
		bcCount = 0;			//新时间段广播计数复位
	}
	else if( bcCount > MaxBroadcastPerSec ) {
		//本时段已经转发的广播包数量超限
		return true;
	}
	else {
		++bcCount;
	}
	return false;
}
void broadcastTimerOver(void) {
    SwitchCore::instance().resetBcCount(); //计时时间到，清除计数器重新计数
}
