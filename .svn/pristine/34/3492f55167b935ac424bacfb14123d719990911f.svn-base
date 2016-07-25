/*
 * AlarmPropertyTemplate.h
 *
 *  Created on: 2014Äê9ÔÂ1ÈÕ
 *      Author: Administrator
 */

#ifndef ALARMPROPERTYTEMPLATE_H_
#define ALARMPROPERTYTEMPLATE_H_

#include <map>
#include "EZ_types.h"
#include "AlarmDataDefine.h"

class BAlarmModule;
class AlarmPropertyTemplate {
    AlarmPropertyTemplate();
public:
    AlarmPropertyTemplate(int sn);
    virtual ~AlarmPropertyTemplate();

    int itsSn(void) {
        return Sn;
    };
    bool addType(char* s, uint32 len);
    bool delType(uint32 type);
    bool activeTo(int slot);
    bool activeToAll(void);
    bool activeToSource(uint32 srcid);
    bool clearTypes(void);

private:
    int Sn;
    std::map<uint32, Alarm_Property_T> Types;
    bool activeTo(BAlarmModule*);
private:
    static std::map<uint32, AlarmPropertyTemplate*> group;
public:
    /* group option */
    static AlarmPropertyTemplate* getInstance(uint32 uid) {
        std::map<uint32, AlarmPropertyTemplate*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static AlarmPropertyTemplate* getFirstInstance(void) {
        std::map<uint32, AlarmPropertyTemplate*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static AlarmPropertyTemplate* getNextInstance(uint32 suid) {
        std::map<uint32, AlarmPropertyTemplate*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };};

#endif /* ALARMPROPERTYTEMPLATE_H_ */
