/*
 * BAlarmModule.cpp
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#include "BAlarmModule.h"
#include "SysError.h"
#include "BAlarmSource.h"
#include "CBaseCard.h"
#include "BAlarmDisplay.h"
#include "AlarmInstance.h"


std::map<uint32, BAlarmModule*> BAlarmModule::group;

TASK void Alarm_Process(void* xc);


BAlarmModule::BAlarmModule(CBaseCard* c) : slotSn(c->getSn()){
    group.insert(std::pair<uint32, BAlarmModule*>(slotSn, this));
    card = c;
    tsk_alm_process = 0;
}

BAlarmModule::~BAlarmModule() {
    os_tsk_delete(tsk_alm_process);
    delete []task_stack;
    SRCMap::iterator it = SrcGroup.begin();
    while( it != SrcGroup.end() ) {
        delete it->second;
        it++;
    }
    SrcGroup.clear();
    group.erase(slotSn);
}

/*
 * �������и澯Դ���ֱ���ÿ���澯Դ��
 */
void BAlarmModule::processAlarm(void) {
    SRCMap::iterator it = SrcGroup.begin();
    while( it != SrcGroup.end() ) {
        it->second->processAlarm();
        it++;
    }
}

/*
 * ģ���ʼ����������ģ�齨�������ȵ���,Ĭ���ڸ澯���������е��á�
 * �˷����ᰴ˳�򹹽��澯������澯Դ
 * ���Ҹ��������澯Դ�ĳ�ʼ��������澯�ź�
 */
void BAlarmModule::initModule(void) {
    task_stack = new uint8[8192];
    creatAlarmSource();
    initSource();
    tsk_alm_process = os_tsk_create_user_ex(Alarm_Process, P_Alarm_Process, task_stack, 8192, this);
}

/*
 * ÿ���澯Դ����Լ��ĸ澯�ź�
 */
void BAlarmModule::initSource(void) {
    SRCMap::iterator it = SrcGroup.begin();
    while( it != SrcGroup.end() ) {
        it->second->makeAlarmSignal();
		it++;
    }
}

void BAlarmModule::addAlmSrc(BAlarmSource* src) {
    SrcGroup.insert(std::pair<uint32, BAlarmSource*>(src->itsID(), src));
}

void BAlarmModule::delAlmSrc(BAlarmSource* src) {
    SrcGroup.erase(src->itsID());
}


bool BAlarmModule::saveConfigData(void) {
    return card->saveConfig();
}


bool BAlarmModule::ifHaveMAJ(void) {
    SRCMap::iterator it = SrcGroup.begin();
    while( it != SrcGroup.end() ) {
        if( it->second->ifHaveMAJ() ) {
            return true;
        }
        it++;
    }
    return false;
}

bool BAlarmModule::ifHaveMin(void) {
    SRCMap::iterator it = SrcGroup.begin();
    while( it != SrcGroup.end() ) {
        if( it->second->ifHaveMIN() ) {
            return true;
        }
        it++;
    }
    return false;
}

bool BAlarmModule::ifAlarm(void) {
    SRCMap::iterator it = SrcGroup.begin();
    while( it != SrcGroup.end() ) {
        if( it->second->ifAlarm() ) {
            return true;
        }
        it++;
    }
    return false;
}

AlarmInstance* BAlarmModule::getFirstAlarmInstance() {
    BAlarmModule* m = getFirstInstance();
    if( m ) {
        BAlarmSource* s = m->getFirstAlarmSource();
        if( s ) {
            return s->getFirstAlarmInstance();
        }
    }
    return 0;
}

AlarmInstance* BAlarmModule::getAlarmInstance(uint32 slot, uint32 srcid, uint32 type) {
    BAlarmModule* m = getInstance(slot);
    if( m ) {
        BAlarmSource* s = m->getAlarmSource(srcid);
        if( s ) {
            return s->getAlarmInstanceByTypeID(type);
        }
    }
    return 0;
}

AlarmInstance* BAlarmModule::getNextAlarmInstance(uint32 slot, uint32 srcid, uint32 type) {
    BAlarmModule* m = getInstance(slot);
    if( m ) {
        BAlarmSource* s = m->getAlarmSource(srcid);
        if( s ) {
            AlarmInstance* i = s->getAlarmInstanceByTypeID(type);
            if( i ) {
                //��֤Դ�Ƿ����
                AlarmInstance* rtn = s->getNextAlarmInstance(type);
                if( rtn ) {
                    return rtn; //
                }
                else {
                    s = m->getNextAlarmSource(s);
                    if( s ) {
                        return s->getFirstAlarmInstance();
                    }
                    else {
                        m = getNextInstance(slot);
                        if( m ) {
                            s = m->getFirstAlarmSource();
                            if( s ) {
                                return s->getFirstAlarmInstance();
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

AlarmInstance* BAlarmModule::getNextAlarmInstance(AlarmInstance* i) {
    if( i ) {
        return getNextAlarmInstance(i->itsSlot(), i->itsSourceIndex(), i->getType());
    }
    return 0;
}



BAlarmSource* BAlarmModule::getAlarmSource(uint32 uid) {
    SRCMap::iterator it = SrcGroup.find(uid);
    if( it != SrcGroup.end() ) {
        return it->second;
    }
    return 0;
}

BAlarmSource* BAlarmModule::getFirstAlarmSource(void) {
    SRCMap::iterator it = SrcGroup.begin();
    if( it != SrcGroup.end() ) {
        return it->second;
    }
    return 0;
}

BAlarmSource* BAlarmModule::getNextAlarmSource(BAlarmSource* s) {
    if( s ) {
        SRCMap::iterator it = SrcGroup.find(s->itsID());
        if( it != SrcGroup.end() ) {
            it++;
            if( it != SrcGroup.end() ) {
                return it->second;
            }
        }
    }
    return 0;
}

bool BAlarmModule::setAlarmPropertyTo(uint32 alarmType, Alarm_Property_T* t) {
    BAlarmSource* s = getFirstAlarmSource();
    while( s ) {
        AlarmInstance* i = s->getAlarmInstanceByTypeID(alarmType);
        if( i ) {
            i->setProperty(t);
        }
        s = getNextAlarmSource(s);
    }
    return true;
}

TASK void Alarm_Process(void* module) {
    if( module == 0 ) {
        throw SysError("!!!No Alarm module!!!");
    }
    BAlarmModule* m = (BAlarmModule*)module;

    while( 1 ) {
        os_dly_wait(300);
        m->processAlarm();
    }
}
