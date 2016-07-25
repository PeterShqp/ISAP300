/*
 * TableDeviceClockSource.cpp
 *
 *  Created on: 2014-1-16
 *      Author: Administrator
 */

#include "TableDeviceClockSource.h"
#include "ClockSourceManager.h"
#include "CCommonDefine.h"
#include "XCPair.h"

column_info_T TableDeviceClockSource::colInfo[dev_clk_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


TableDeviceClockSource::TableDeviceClockSource(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableDeviceClockSource::~TableDeviceClockSource() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableDeviceClockSource::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* TableDeviceClockSource::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case dev_clk_pri:
        return new CMibDevClk_pri(sn, oid, oidLen, this);
    case dev_clk_index:
        return new CMibDevClk_index(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableDeviceClockSource::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    int maxIndex = XCPair::instance().getSdhClockManager()->getBackupClockSourceNumber();
    if( maxIndex > 0 ) {
        index->index[1] = 1;
        return 1;
    }
    return -1;
}

int TableDeviceClockSource::getNextIndex(index_info_T* index) {
    int maxIndex = XCPair::instance().getSdhClockManager()->getBackupClockSourceNumber();
    if( index->index[1] < maxIndex ) {
        ++(index->index[1]);
        return 1;
    }
    return -1;
}



int CMibDevClk_pri::CallbackGet(const index_info_T& index) {
    return index.index[1];
}


int CMibDevClk_index::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getSdhClockManager()->getBackupClockSource(index.index[1]-1);
}
int CMibDevClk_index::callbackSet( const index_info_T& index, uint32 val) {
    if( XCPair::instance().getSdhClockManager()->setBackupClockSource(index.index[1]-1, val) ) {
        return 0x5A;
    }
    return -1;
}
