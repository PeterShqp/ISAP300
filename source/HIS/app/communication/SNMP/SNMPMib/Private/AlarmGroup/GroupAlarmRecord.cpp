/*
 * GroupAlarmRecord.cpp
 *
 *  Created on: 2014Äê8ÔÂ27ÈÕ
 *      Author: Administrator
 */

#include "GroupAlarmRecord.h"
#include "TableCurrentAlarm.h"

table_info_T GroupAlarmRecord::tableInfo[table_record_size] = {
        {1, alarm_record_columns, 2},//sn, col number, index number
//        {2, table_history_columns, 1},
};

GroupAlarmRecord::~GroupAlarmRecord() {
    // TODO Auto-generated destructor stub
}


GroupAlarmRecord::GroupAlarmRecord(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
    creatTables(tableInfo, table_record_size);
}

CMibEntry* GroupAlarmRecord::MakeTable(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case table_Current_Alarm:
        return new TableCurrentAlarm(oid, oidLen, &tableInfo[sn]);
    case table_History_Alarm:
    default:
        return 0;
    }
}
