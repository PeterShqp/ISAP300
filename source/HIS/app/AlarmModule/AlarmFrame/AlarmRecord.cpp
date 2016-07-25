/*
 * AlarmRecord.cpp
 *
 *  Created on: 2014��8��6��
 *      Author: Administrator
 */

#include "AlarmRecord.h"
#include "CPPTools.h"
#include <stdio.h>
#include "AlarmInstance.h"
#include "RTC.h"
#include <time.h>

uint32 AlarmRecord::SerialNumber = 0;
std::map<uint32, AlarmRecord*> AlarmRecord::group;

AlarmRecord::AlarmRecord(AlarmInstance* i) {
    sn = ++SerialNumber;
    timeticks = RTC::getRunningSecs();
    Ins = i;
    group.insert( std::pair<uint32, AlarmRecord*>(sn, this) );
}

AlarmRecord::~AlarmRecord() {
//    FILE* f = fopen("HistoryAlarm.txt", "a");
//    if( f != 0 ) {
//        std::string c = itsContent() + "," + CPPTools::number2string( time(0) ) + "\r\n";
//        fputs(c.c_str(), f);
//        fclose(f);
//    }
    group.erase(sn);
}

std::string AlarmRecord::itsContent(void) {
    std::string content = CPPTools::number2string(
            Ins->itsSlot() + 1 ) + "," +
            Ins->itsSourceName() + "," +
            Ins->itsTypeName() + "," +
            CPPTools::number2string(Ins->getLevel()) + "," +
            CPPTools::number2string( RTC::converRunningSecsToUTC(timeticks) );
    return content;
}

uint32 AlarmRecord::itsAlarmType() {
    return Ins->getType();
}
uint32 AlarmRecord::itsAlarmSource() {
    return Ins->itsSourceIndex();
}
uint32 AlarmRecord::itsAlarmLevel() {
    return Ins->getLevel();
}
