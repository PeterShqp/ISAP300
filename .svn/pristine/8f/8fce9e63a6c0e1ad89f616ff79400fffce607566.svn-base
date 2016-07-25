/*
 * TableCurrentAlarm.h
 *
 *  Created on: 2014Äê9ÔÂ10ÈÕ
 *      Author: Administrator
 */

#ifndef TABLECURRENTALARM_H_
#define TABLECURRENTALARM_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    alarm_record_sn,
    alarm_record_content,
    alarm_record_columns

};

class TableCurrentAlarm : public CMibTable {
    TableCurrentAlarm();
public:
    TableCurrentAlarm(uint32*, uint32, table_info_T*);
    virtual ~TableCurrentAlarm();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[alarm_record_columns];
};


class TableCurrentAlarm_sn : public CMibTableColumn {
    TableCurrentAlarm_sn();
public:
    TableCurrentAlarm_sn(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableCurrentAlarm_sn() {};

    virtual int CallbackGet(const index_info_T& index);
};

class TableCurrentAlarm_content : public CMibTableColumn {
    TableCurrentAlarm_content();
public:
    TableCurrentAlarm_content(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableCurrentAlarm_content() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

#endif /* TABLECURRENTALARM_H_ */
