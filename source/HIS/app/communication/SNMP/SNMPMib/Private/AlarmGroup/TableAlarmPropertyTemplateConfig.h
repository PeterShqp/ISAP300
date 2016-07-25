/*
 * TableAlarmPropertyTemplateConfig.h
 *
 *  Created on: 2014Äê8ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef TABLEALARMPROPERTYTEMPLATECONFIG_H_
#define TABLEALARMPROPERTYTEMPLATECONFIG_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    template_sn,
    add_alarm_type,
    del_alarm_type,
    active_to_group,
    active_to_source,
    clear_alarm_type,
    del_template,
    table_template_config_columns
};

class TableAlarmPropertyTemplateConfig : public CMibTable {
    TableAlarmPropertyTemplateConfig();
public:
    TableAlarmPropertyTemplateConfig(uint32*, uint32, table_info_T*);
    virtual ~TableAlarmPropertyTemplateConfig();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[table_template_config_columns];
};


class TableAlarmPropertyTemplateConfig_sn : public CMibTableColumn {
    TableAlarmPropertyTemplateConfig_sn();
public:
    TableAlarmPropertyTemplateConfig_sn(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateConfig_sn() {};

    virtual int CallbackGet(const index_info_T& index);
};

class TableAlarmPropertyTemplateConfig_addtype : public CMibTableColumn {
    TableAlarmPropertyTemplateConfig_addtype();
public:
    TableAlarmPropertyTemplateConfig_addtype(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateConfig_addtype() {};

    virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class TableAlarmPropertyTemplateConfig_deltype : public CMibTableColumn {
    TableAlarmPropertyTemplateConfig_deltype();
public:
    TableAlarmPropertyTemplateConfig_deltype(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateConfig_deltype() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

class TableAlarmPropertyTemplateConfig_activegroup : public CMibTableColumn {
    TableAlarmPropertyTemplateConfig_activegroup();
public:
    TableAlarmPropertyTemplateConfig_activegroup(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateConfig_activegroup() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

class TableAlarmPropertyTemplateConfig_activesource : public CMibTableColumn {
    TableAlarmPropertyTemplateConfig_activesource();
public:
    TableAlarmPropertyTemplateConfig_activesource(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateConfig_activesource() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

class TableAlarmPropertyTemplateConfig_clear : public CMibTableColumn {
    TableAlarmPropertyTemplateConfig_clear();
public:
    TableAlarmPropertyTemplateConfig_clear(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateConfig_clear() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

class TableAlarmPropertyTemplateConfig_del : public CMibTableColumn {
    TableAlarmPropertyTemplateConfig_del();
public:
    TableAlarmPropertyTemplateConfig_del(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateConfig_del() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* TABLEALARMPROPERTYTEMPLATECONFIG_H_ */
