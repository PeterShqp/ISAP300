/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CCardOnlineChecker.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/SlotCard/CCardOnlineChecker.cpp
 ** Created by:          Shqp
 ** Created date:        2012-3-30
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#include "CCardOnlineChecker.h"
#include "CBaseSlot.h"
#include "os.h"
#include "SlotModule.h"
#include "ProtectAssistCell.h"

static void TaskRun(void);

OS_TID oc;

CCardOnlineChecker::CCardOnlineChecker() {
    oc = os_tsk_create(TaskRun, P_Online_Check);
}

CCardOnlineChecker::~CCardOnlineChecker() {
	os_tsk_delete(oc);

}
/*
 * ��������ѭ����⿨״̬���޿����ȴ�忨���忨�������ȴ�ο�
 */
TASK void TaskRun() {
    static int smoothCnt[10] = {0};
    std::vector<CBaseSlot*>& Slots = SlotModule::getSlots();
    bool one_loop[7] = {false,false,false,false,false,false,false};
    bool oneLoopDone = false;
    while( 1 ) {
        os_dly_wait(100);
        for( int i = 0; i < Slots.size(); i++ ) {
            int cid;
            int state = Slots[i]->getCheckStatus();
            switch( state ) {
            case NoCard:
                cid = Slots[i]->getCurrentCardTypeID();
                if( cid > 0 ) {
                    Slots[i]->setCheckStatus(WaitInsert);
                    smoothCnt[i] = 4;
                }
                else {
                    one_loop[i] = true; //稳定在无卡
                }
                break;
            case WaitInsert: {
                cid = Slots[i]->getCurrentCardTypeID();
                if( cid > 0 ) {
                    ++smoothCnt[i];
                    if( smoothCnt[i] > 7 ) {

                        if( Slots[i]->InsertCard(cid) != 0 ) {
                            Slots[i]->setCheckStatus(Working);
                        }
                        else {
                            Slots[i]->setCheckStatus(NoCard);
                        }
                    }
                }
                else {
                    --smoothCnt[i];
                    if( smoothCnt[i] < 1 ) {
                        Slots[i]->setCheckStatus(NoCard);
                   }
                }

            }
                break;
            case Working:
                cid = Slots[i]->getCurrentCardTypeID();
                if( cid != Slots[i]->GetCardType() ) {
                    Slots[i]->setCheckStatus(WaitDelete);
                    smoothCnt[i] = 4;
                }
                else {
                    one_loop[i] = true; //稳定在有卡
                }
                break;
            case WaitDelete:
                cid = Slots[i]->getCurrentCardTypeID();
                if( cid != Slots[i]->GetCardType() ) {
                    ++smoothCnt[i];
                    if( smoothCnt[i] > 7 ) {
//                        tsk_lock();
                        Slots[i]->RemoveCard();
                        Slots[i]->setCheckStatus(NoCard);
//                        tsk_unlock();
                    }
                }
                else {
                    --smoothCnt[i];
                    if( smoothCnt[i] < 1 ) {
                        Slots[i]->setCheckStatus(Working);
                   }
                }
                break;
            default:
                Slots[i]->setCheckStatus(NoCard);
                break;
            }


        }


        if( !oneLoopDone ) {
            bool done = true;
            for (int i = 0; i < 7; ++i) { //检查是否所有槽位均已轮询完毕
                done = done && one_loop[i];
            }

            if(done) {

                oneLoopDone = true;
                OS_TID tid = ProtectAssistCell::instance().getTaskProcessWorking();
                if( tid != 0 ) {
                    os_evt_set(0x8000, tid);
                }
            }
        }
    }
}

