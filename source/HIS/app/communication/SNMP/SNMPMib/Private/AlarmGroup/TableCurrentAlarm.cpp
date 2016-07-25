/*
 * TableCurrentAlarm.cpp
 *
 *  Created on: 2014年9月10日
 *      Author: Administrator
 */

#include "TableCurrentAlarm.h"
#include "AlarmRecord.h"
#include "CCommonDefine.h"
#include <string.h>


column_info_T TableCurrentAlarm::colInfo[alarm_record_columns] = {
        { 1, Mib_read_only,CSnmpConstDefine::ucConstInteger32 },
        { 2, Mib_read_only,CSnmpConstDefine::ucConstOctetString },
};

TableCurrentAlarm::TableCurrentAlarm(uint32* oid, uint32 oidLen, table_info_T* tInfo) :
        CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableCurrentAlarm::~TableCurrentAlarm() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableCurrentAlarm::getColInfo(int sn) {
    return &colInfo[sn];
}

/*
 * 创建新对象
 */
CMibNodeObject* TableCurrentAlarm::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch (sn) {
    case alarm_record_sn:
        return new TableCurrentAlarm_sn(sn, oid, oidLen, this);
    case alarm_record_content:
        return new TableCurrentAlarm_content(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableCurrentAlarm::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    AlarmRecord* r = AlarmRecord::getFirstInstance();
    if( r ) {
        index->index[1] = r->itsSN();
        return 1;
    }
    return -1;
}
int TableCurrentAlarm::getNextIndex(index_info_T* index) {
    AlarmRecord* r = AlarmRecord::getNextInstance(index->index[1]);
    if( r ) {
        index->index[1] = r->itsSN();
        return 1;
    }
    return -1;
}

int TableCurrentAlarm_sn::CallbackGet(const index_info_T& index) {
    AlarmRecord* r = AlarmRecord::getInstance(index.index[1]);
    if( r ) {
        return r->itsSN();
    }
    return -1;
}

int TableCurrentAlarm_content::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    AlarmRecord* r = AlarmRecord::getInstance(index.index[1]);
    if( r ) {
        std::string c = r->itsContent();
        *len = c.size();
        strcpy((char*)buf, c.c_str());
        return 1;
    }
    return -1;
}
