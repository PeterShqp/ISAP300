/*
 * GroupAlarmRecord.h
 *
 *  Created on: 2014Äê8ÔÂ27ÈÕ
 *      Author: Administrator
 */

#ifndef GROUPALARMRECORD_H_
#define GROUPALARMRECORD_H_

#include "CMibGroup.h"

enum {
    table_Current_Alarm,
    table_History_Alarm,
    table_record_size
};

class GroupAlarmRecord : public CMibGroup {
    GroupAlarmRecord();
public:
    GroupAlarmRecord(uint32* oid, uint8 oidlen);
    virtual ~GroupAlarmRecord();

//  virtual table_info_T* getTableInfo(int sn);
    virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
    static table_info_T tableInfo[table_record_size];
};

#endif /* GROUPALARMRECORD_H_ */
