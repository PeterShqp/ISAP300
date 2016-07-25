/*
 * BAlarmSource.cpp
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#include "BAlarmSource.h"
#include "AlarmInstance.h"
#include "BAlarmModule.h"

BAlarmSource::BAlarmSource(BAlarmModule* m) : ItsModule(m) {

}

BAlarmSource::~BAlarmSource() {
    /*
     * 删除告警实例
     */
    INSMap::iterator it = InsGroup.begin();
    while( it != InsGroup.end() ) {
        delete it->second;
        it++;
    }
    InsGroup.clear();
}

/*
 * ����澯 �澯Դ�����źŵĲɼ�
 * ���澯���ƣ�����Ϊ�޸澯
 */
void BAlarmSource::processAlarm(void) {
    if( ifSrcRestrain() ) {
        //���澯Դ�����ƣ������и澯�źŰ��޸澯����
        INSMap::iterator it = InsGroup.begin();
        while( it != InsGroup.end() ) {
            it->second->setAlarm(false);
            it++;
        }
        return;
    }
    INSMap::iterator it = InsGroup.begin();
    while( it != InsGroup.end() ) {
        it->second->setAlarm(getAlarm(it->first));
        it++;
    }
}


/*
 * ���Ӹ澯�ź�
 */
void BAlarmSource::addAlmIns(AlarmInstance* ai) {
    InsGroup.insert(std::pair<int, AlarmInstance*>(ai->getType(), ai));
}

/*
 * ɾ��澯�ź�
 */
void BAlarmSource::delalmIns(AlarmInstance* ai) {
    InsGroup.erase(ai->getType());
    delete ai;
};


bool BAlarmSource::ifHaveMAJ(void) {
    INSMap::iterator it = InsGroup.begin();
    while( it != InsGroup.end() ) {
        if( (it->second->getLevel() == 1 || it->second->getLevel() == 2)
                && it->second->currentState() ) {
            return true;
        }
        it++;
    }
    return false;
}

bool BAlarmSource::ifHaveMIN(void) {
    INSMap::iterator it = InsGroup.begin();
    while( it != InsGroup.end() ) {
        if( (it->second->getLevel() == 3 ) && it->second->currentState() ) {
            return true;
        }
        it++;
    }
    return false;
}


bool BAlarmSource::saveConfigData(void) {
    return itsModule()->saveConfigData();
}


AlarmInstance* BAlarmSource::getAlarmInstanceByTypeID(int type) {
    INSMap::iterator it = InsGroup.find(type);
    if( it != InsGroup.end() ) {
        return it->second;
    }
    return 0;
}

AlarmInstance* BAlarmSource::getFirstAlarmInstance(void) {
    INSMap::iterator it = InsGroup.begin();
    if( it != InsGroup.end() ) {
        return it->second;
    }
    return 0;
}

AlarmInstance* BAlarmSource::getNextAlarmInstance(int type) {
    INSMap::iterator it = InsGroup.find(type);
    if( it != InsGroup.end() ) {
        it++;
        if( it != InsGroup.end() ) {
            return it->second;
        }
    }
    return 0;
}

AlarmInstance* BAlarmSource::getNextAlarmInstance(AlarmInstance* ai) {
    return getNextAlarmInstance( ai->getType() );
}
