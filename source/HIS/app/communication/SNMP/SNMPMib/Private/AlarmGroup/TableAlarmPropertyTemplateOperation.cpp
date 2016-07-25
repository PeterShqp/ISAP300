/*
 * TableAlarmPropertyTemplateOperation.cpp
 *
 *  Created on: 2014年8月28日
 *      Author: Administrator
 */

#include "TableAlarmPropertyTemplateOperation.h"
#include "CSnmpConstDefine.h"
#include "AlarmPropertyTemplate.h"

column_info_T TableAlarmPropertyTemplateOperation::colInfo[template_operation_columns] = {
        { 1, Mib_write_only,CSnmpConstDefine::ucConstInteger32 },
};

TableAlarmPropertyTemplateOperation::TableAlarmPropertyTemplateOperation(uint32* oid, uint32 oidLen, table_info_T* tInfo) :
        CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableAlarmPropertyTemplateOperation::~TableAlarmPropertyTemplateOperation() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableAlarmPropertyTemplateOperation::getColInfo(int sn) {
    return &colInfo[sn];
}

/*
 * 创建新对象
 */
CMibNodeObject* TableAlarmPropertyTemplateOperation::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch (sn) {
    case template_new:
        return new TableAlarmPropertyTemplateOperation_new(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableAlarmPropertyTemplateOperation::getFirstIndex(index_info_T* index) {
    return -1;
}
int TableAlarmPropertyTemplateOperation::getNextIndex(index_info_T* index) {
    return -1;
}

int TableAlarmPropertyTemplateOperation_new::callbackSet( const index_info_T& index, uint32 sn ) {
    AlarmPropertyTemplate* t = new AlarmPropertyTemplate(sn);
    if( t ) {
        return 0x5A;
    }
    return -1;
}
