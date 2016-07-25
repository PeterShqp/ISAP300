/*
 * TableAlarmPropertyTemplateConfig.cpp
 *
 *  Created on: 2014年8月28日
 *      Author: Administrator
 */

#include "TableAlarmPropertyTemplateConfig.h"
#include "CCommonDefine.h"
#include "CSnmpConstDefine.h"
#include "AlarmPropertyTemplate.h"


column_info_T TableAlarmPropertyTemplateConfig::colInfo[table_template_config_columns] = {
        { 1, Mib_read_only,CSnmpConstDefine::ucConstInteger32 },
        { 2, Mib_write_only,CSnmpConstDefine::ucConstOctetString },
        { 3, Mib_write_only,CSnmpConstDefine::ucConstInteger32 },
        { 4, Mib_write_only,CSnmpConstDefine::ucConstInteger32 },
        { 5, Mib_write_only,CSnmpConstDefine::ucConstInteger32 },
        { 6, Mib_write_only,CSnmpConstDefine::ucConstInteger32 },
        { 7, Mib_write_only,CSnmpConstDefine::ucConstInteger32 },
};

TableAlarmPropertyTemplateConfig::TableAlarmPropertyTemplateConfig(uint32* oid, uint32 oidLen, table_info_T* tInfo) :
        CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableAlarmPropertyTemplateConfig::~TableAlarmPropertyTemplateConfig() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableAlarmPropertyTemplateConfig::getColInfo(int sn) {
    return &colInfo[sn];
}

/*
 * 创建新对象
 */
CMibNodeObject* TableAlarmPropertyTemplateConfig::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch (sn) {
    case template_sn:
        return new TableAlarmPropertyTemplateConfig_sn(sn, oid, oidLen, this);
    case add_alarm_type:
        return new TableAlarmPropertyTemplateConfig_addtype(sn, oid, oidLen, this);
    case del_alarm_type:
        return new TableAlarmPropertyTemplateConfig_deltype(sn, oid, oidLen, this);
    case active_to_group:
        return new TableAlarmPropertyTemplateConfig_activegroup(sn, oid, oidLen, this);
    case active_to_source:
        return new TableAlarmPropertyTemplateConfig_activesource(sn, oid, oidLen, this);
    case clear_alarm_type:
        return new TableAlarmPropertyTemplateConfig_clear(sn, oid, oidLen, this);
    case del_template:
        return new TableAlarmPropertyTemplateConfig_del(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableAlarmPropertyTemplateConfig::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getFirstInstance();
    if( t ) {
        index->index[1] = t->itsSn();
        return 1;
    }
    return -1;
}
int TableAlarmPropertyTemplateConfig::getNextIndex(index_info_T* index) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getNextInstance(index->index[1]);
    if( t ) {
        index->index[1] = t->itsSn();
        return 1;
    }
    return -1;
}

int TableAlarmPropertyTemplateConfig_sn::CallbackGet(const index_info_T& index) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getInstance(index.index[1]);
    if( t ) {
        return t->itsSn();
    }
    return -1;
}

int TableAlarmPropertyTemplateConfig_addtype::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getInstance(index.index[1]);
    if( t ) {
        if( t->addType((char*)buf, len) ) {
            return 0x5A;
        }
    }
    return -1;
}

int TableAlarmPropertyTemplateConfig_deltype::callbackSet( const index_info_T& index, uint32 type ) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getInstance(index.index[1]);
    if( t ) {
        if( t->delType(type) ) {
            return 0x5A;
        }
    }
    return -1;
}

int TableAlarmPropertyTemplateConfig_activegroup::callbackSet( const index_info_T& index, uint32 scope ) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getInstance(index.index[1]);
    if( t ) {
        if( scope == CCommonDefine::uiConstDeviceIndex ) {
            if( t->activeToAll() ) {
                return 0x5A;
            }
        }
        else {
            if( t->activeTo(scope-1) ) {
                return 0x5A;
            }
        }
    }
    return -1;
}

int TableAlarmPropertyTemplateConfig_activesource::callbackSet( const index_info_T& index, uint32 src ) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getInstance(index.index[1]);
    if( t ) {
        if( t->activeToSource(src) ) {
            return 0x5A;
        }
    }
    return -1;
}

int TableAlarmPropertyTemplateConfig_clear::callbackSet( const index_info_T& index, uint32 templateid ) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getInstance(index.index[1]);
    if( t ) {
        if( t->clearTypes() ) {
            return 0x5A;
        }
    }
    return -1;
}

int TableAlarmPropertyTemplateConfig_del::callbackSet( const index_info_T& index, uint32 ) {
    AlarmPropertyTemplate* t = AlarmPropertyTemplate::getInstance(index.index[1]);
    if( t ) {
        delete t;
        return 0x5A;
    }
    return -1;
}
