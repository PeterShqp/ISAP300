/*
 * TableAlarmPropertyConfig.h
 *
 *  Created on: 2014Äê8ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef TABLEALARMPROPERTYCONFIG_H_
#define TABLEALARMPROPERTYCONFIG_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    alarm_source_name,
    alarm_type_name,
    alarm_property,
    table_alm_ppt_config_columns

};

class TableAlarmPropertyConfig : public CMibTable {
    TableAlarmPropertyConfig();
public:
    TableAlarmPropertyConfig(uint32*, uint32, table_info_T*);
    virtual ~TableAlarmPropertyConfig();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[table_alm_ppt_config_columns];
};


class TableAlarmPropertyConfig_srcname : public CMibTableColumn {
    TableAlarmPropertyConfig_srcname();
public:
    TableAlarmPropertyConfig_srcname(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyConfig_srcname() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableAlarmPropertyConfig_typename : public CMibTableColumn {
    TableAlarmPropertyConfig_typename();
public:
    TableAlarmPropertyConfig_typename(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyConfig_typename() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableAlarmPropertyConfig_property : public CMibTableColumn {
    TableAlarmPropertyConfig_property();
public:
    TableAlarmPropertyConfig_property(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyConfig_property() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
    virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

#endif /* TABLEALARMPROPERTYCONFIG_H_ */
