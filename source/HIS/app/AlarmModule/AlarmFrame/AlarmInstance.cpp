/*
 * AlarmInstance.cpp
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#include "AlarmInstance.h"
#include "AlarmRecord.h"
#include "BAlarmDisplay.h"
#include "BAlarmSource.h"
#include "BAlarmModule.h"
#include <stdio.h>
#include "TrapList.h"
#include "RTC.h"

AlarmInstance::AlarmInstance(int type, BAlarmSource* src, Alarm_Property_T* p) : typeName(src->getTypeName(type)) {
    TypeID = type;
    Property = p;
    Record = 0;
    Display = 0;
    StateCurr = false;
    Source = src;
    StateBak = -1;
}

AlarmInstance::AlarmInstance(int type, BAlarmSource* src, Alarm_Property_T* p, BAlarmDisplay* d) : typeName(src->getTypeName(type)) {
    TypeID = type;
    Property = p;
    Record = 0;
    Display = d;
    if( Display ) {
        Display->addInstance(this);
    }
    StateCurr = false;
    Source = src;
    StateBak = -1;
}


AlarmInstance::~AlarmInstance() {
    if( Record ) {
        delete Record;
    }
}

void AlarmInstance::setAlarm(bool alarm) {
    /* �Ը澯�ź������δ��� */
    StateCurr = alarm && (Property->mask == 0);

    if( StateBak != StateCurr ) {
        StateBak = StateCurr;
        if( StateCurr ) {
            //���κ� �澯�������޸澯��¼���򴴽��¼�¼
            Record = new AlarmRecord(this);
            //�������
            if( Display ) {
                Display->update(this);
            }
            if( getTrap() == 1 ) {
                TrapList::instance().insertNewAlarmTrap(Record);
            }
        }
        else {
            //���κ� �澯�����������и澯��¼����ɾ��ԭ��¼
            if( Record != 0 ) {
                if( getTrap() == 1 ) {
                    TrapList::instance().insertRecoveryAlarmTrap(Record, RTC::getRunningSecs());
                }
                delete Record;
                Record = 0;
            }
            //�������
            if( Display ) {
                Display->update(this);
            }
        }
    }
}

void AlarmInstance::setLevel(uint8 lv, bool save) {
    Property->level = lv;
    if( save ) {
        Source->saveConfigData();
    }
}
void AlarmInstance::setTrap(uint8 tp, bool save) {
    Property->trap = tp;
    if( save ) {
        Source->saveConfigData();
    }
}
void AlarmInstance::setMask(uint8 msk, bool save) {
    Property->mask = msk;
    if( save ) {
        Source->saveConfigData();
    }
}
void AlarmInstance::setProperty(Alarm_Property_T* ap, bool save ) {
    Property->level = ap->level;
    Property->mask = ap->mask;
    Property->trap = ap->trap;
    if( save ) {
        Source->saveConfigData();
    }
}

void AlarmInstance::setProperty(char* s, bool save ) {
    int level, mask, trap;
    sscanf(s, "%d,%d,%d", &level, &mask, &trap);
    Property->level = level;
    Property->mask = mask;
    Property->trap = trap;
    if( save ) {
        Source->saveConfigData();
    }
}

bool AlarmInstance::equelTo(AlarmInstance* i) {
    if( (getType() == i->getType()) && (getSource()->itsID() == i->getSource()->itsID()) ) {
        return true;
    }
    return false;
}

//bool AlarmInstance::operator== (const AlarmInstance* t) const {
//    if( (getType() != t.getType()) || (getSource()->itsID() != t->getSource()->itsID()) ) {
//        return true;
//    }
//    return false;
//}


int AlarmInstance::itsSlot(void) {
    return getSource()->itsModule()->itsSn();
}

uint32 AlarmInstance::itsSourceIndex(void) {
    return Source->itsID();
}

std::string& AlarmInstance::itsSourceName(void) {
    return Source->itsName();
}
std::string& AlarmInstance::itsTypeName(void) {
    return typeName;
}
std::string AlarmInstance::itsStrProperty(void) {
    char s[20];
    sprintf(s, "%d,%d,%d", Property->level, Property->mask, Property->trap);
    std::string ss(s);
    return ss;
}

