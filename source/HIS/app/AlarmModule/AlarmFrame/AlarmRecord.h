/*
 * AlarmRecord.h
 *
 *  Created on: 2014��8��6��
 *      Author: Administrator
 */

#ifndef ALARMRECORD_H_
#define ALARMRECORD_H_

#include <map>
#include "EZ_types.h"
#include <string>

class AlarmInstance;

class AlarmRecord {
    AlarmRecord();
public:
    AlarmRecord(AlarmInstance*);
    virtual ~AlarmRecord();

    uint32 itsSN(void) {
        return sn;
    };

    std::string itsContent(void);
    uint32 itsRaiseTime() {
        return timeticks;
    };

    uint32 itsAlarmType();
    uint32 itsAlarmSource();
    uint32 itsAlarmLevel();
private:
    uint32 sn;
    uint32 timeticks;
    AlarmInstance* Ins;
    static uint32 SerialNumber;

private:
    static std::map<uint32, AlarmRecord*> group;
public:
    /* group option */
    static AlarmRecord* getInstance(uint32 uid) {
        std::map<uint32, AlarmRecord*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static AlarmRecord* getFirstInstance(void) {
        std::map<uint32, AlarmRecord*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static AlarmRecord* getNextInstance(uint32 suid) {
        std::map<uint32, AlarmRecord*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* ALARMRECORD_H_ */
