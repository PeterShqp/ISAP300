/*
 * AlarmPropertyTemplate.cpp
 *
 *  Created on: 2014Äê9ÔÂ1ÈÕ
 *      Author: Administrator
 */

#include "AlarmPropertyTemplate.h"
#include "BAlarmModule.h"
#include <stdio.h>

std::map<uint32, AlarmPropertyTemplate*> AlarmPropertyTemplate::group;

AlarmPropertyTemplate::AlarmPropertyTemplate(int sn) : Sn(sn) {

    group.insert(std::pair<uint32, AlarmPropertyTemplate*>(Sn, this));

}

AlarmPropertyTemplate::~AlarmPropertyTemplate() {
    group.erase(Sn);
}

bool AlarmPropertyTemplate::addType(char* s, uint32 len) {
    int type, level, mask, trap;
    Alarm_Property_T p;
    s[len] = '\0';
    sscanf(s, "%d,%d,%d,%d", &type, &level, &mask, &trap);
    p.level = level;
    p.mask = mask;
    p.trap = trap;
    Types.insert(std::pair<uint32, Alarm_Property_T>(type, p));
    return true;
}
bool AlarmPropertyTemplate::delType(uint32 type) {
    Types.erase(type);
    return true;
}

bool AlarmPropertyTemplate::activeTo(BAlarmModule* m) {
    if( m ) {
        std::map<uint32, Alarm_Property_T>::iterator it = Types.begin();
        while( it != Types.end() ) {
            m->setAlarmPropertyTo(it->first, &it->second);
            it++;
        }
    }
    return true;

}

bool AlarmPropertyTemplate::activeTo(int slot) {
    BAlarmModule* m = BAlarmModule::getInstance(slot);
    return activeTo(m);
}
bool AlarmPropertyTemplate::activeToAll(void) {
    BAlarmModule* m = BAlarmModule::getFirstInstance();
    while( m ) {
        activeTo(m);
        m = BAlarmModule::getNextInstance(m->itsSn());
    }
    return true;
}
bool AlarmPropertyTemplate::activeToSource(uint32 srcid) {
    return false;
}
bool AlarmPropertyTemplate::clearTypes(void) {
    Types.clear();
    return true;
}
