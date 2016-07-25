/*
 * TableAlarmPropertyConfig.cpp
 *
 *  Created on: 2014年8月28日
 *      Author: Administrator
 */

#include "TableAlarmPropertyConfig.h"
#include "AlarmInstance.h"
#include "BAlarmModule.h"
#include "CCommonDefine.h"
#include "CSnmpConstDefine.h"
#include <string.h>

column_info_T TableAlarmPropertyConfig::colInfo[table_alm_ppt_config_columns] = {
        { 1, Mib_read_only,CSnmpConstDefine::ucConstOctetString },
        { 2, Mib_read_only,CSnmpConstDefine::ucConstOctetString },
        { 3, Mib_read_write,CSnmpConstDefine::ucConstOctetString },
};

TableAlarmPropertyConfig::TableAlarmPropertyConfig(uint32* oid, uint32 oidLen, table_info_T* tInfo) :
        CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableAlarmPropertyConfig::~TableAlarmPropertyConfig() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableAlarmPropertyConfig::getColInfo(int sn) {
    return &colInfo[sn];
}

/*
 * 创建新对象
 */
CMibNodeObject* TableAlarmPropertyConfig::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch (sn) {
    case alarm_source_name:
        return new TableAlarmPropertyConfig_srcname(sn, oid, oidLen, this);
    case alarm_type_name:
        return new TableAlarmPropertyConfig_typename(sn, oid, oidLen, this);
    case alarm_property:
        return new TableAlarmPropertyConfig_property(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableAlarmPropertyConfig::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    AlarmInstance* i = BAlarmModule::getFirstAlarmInstance();
    if( i ) {
        index->index[1] = i->itsSlot()+1;
        index->index[2] = i->itsSourceIndex();
        index->index[3] = i->getType();
        return 1;
    }
    return -1;
}
int TableAlarmPropertyConfig::getNextIndex(index_info_T* index) {
    AlarmInstance* i = BAlarmModule::getAlarmInstance(index->index[1]-1, index->index[2], index->index[3]);
    if( i ) {
        AlarmInstance* ai = BAlarmModule::getNextAlarmInstance(i);
        if( ai ) {
            index->index[1] = ai->itsSlot()+1;
            index->index[2] = ai->itsSourceIndex();
            index->index[3] = ai->getType();
            return 1;
        }
    }
    return -1;
}

int TableAlarmPropertyConfig_srcname::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    AlarmInstance* i = BAlarmModule::getAlarmInstance(index.index[1]-1, index.index[2], index.index[3]);
    if( i ) {
        std::string& name = i->itsSourceName();
        *len = name.size();
        memcpy(buf, name.c_str(), *len);
        return 1;
    }
    return 0;
}


int TableAlarmPropertyConfig_typename::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    AlarmInstance* i = BAlarmModule::getAlarmInstance(index.index[1]-1, index.index[2], index.index[3]);
    if( i ) {
        std::string& name = i->itsTypeName();
        *len = name.size();
        memcpy(buf, name.c_str(), *len);
        return 1;
    }
    return 0;
}

int TableAlarmPropertyConfig_property::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    AlarmInstance* i = BAlarmModule::getAlarmInstance(index.index[1]-1, index.index[2], index.index[3]);
    if( i ) {
        std::string name = i->itsStrProperty();
        *len = name.size();
        memcpy(buf, name.c_str(), *len);
        return 1;
    }
    return 0;
}

int TableAlarmPropertyConfig_property::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
    AlarmInstance* i = BAlarmModule::getAlarmInstance(index.index[1]-1, index.index[2], index.index[3]);
    if( i ) {
        buf[len] = '\0';
        i->setProperty((char*)buf);
        return 0x5A;
    }
    return -1;
}
