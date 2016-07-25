/*
 * AlarmInstance.h
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#ifndef ALARMINSTANCE_H_
#define ALARMINSTANCE_H_

#include "AlarmDataDefine.h"
#include <string>

class AlarmRecord;
class BAlarmDisplay;
class BAlarmSource;

class AlarmInstance {
    AlarmInstance();
public:
    AlarmInstance(int type, BAlarmSource*, Alarm_Property_T*);
    AlarmInstance(int type, BAlarmSource*, Alarm_Property_T*, BAlarmDisplay*);
    virtual ~AlarmInstance();

    void setAlarm(bool alarm);

    void setLevel(uint8 lv, bool save = true);
    void setTrap(uint8 tp, bool save = true);
    void setMask(uint8 msk, bool save = true);
    void setProperty(Alarm_Property_T*, bool save = true);
    void setProperty(char* s, bool save = true);

    uint8 getLevel() {
        return Property->level;
    };
    uint8 getTrap() {
        return Property->trap;
    };
    uint8 getMask() {
        return Property->mask;
    };

    int getType(void) {
        return TypeID;
    };

    BAlarmSource* getSource(void) {
        return Source;
    };

    bool equelTo(AlarmInstance*);

    bool currentState(void) {
        return StateCurr;
    };

    int itsSlot(void);
    uint32 itsSourceIndex(void);
    std::string& itsSourceName(void);
    std::string& itsTypeName(void);
    std::string itsStrProperty(void);

private:
    int TypeID;
    std::string typeName;
    Alarm_Property_T* Property;
    bool StateCurr; //false --> normal; true --> alarm
    int StateBak;   //0 --> normal; 1 --> alarm; -1 --> idle;
    AlarmRecord* Record;
    BAlarmDisplay* Display;
    BAlarmSource* Source;
};

#endif /* ALARMINSTANCE_H_ */
