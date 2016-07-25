/*
 * PcmClockSourceTable.cpp
 *
 *  Created on: 2015Äê2ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "PcmClockSourceTable.h"
#include "ClockSourceManager.h"
#include "CCommonDefine.h"
#include "XCPair.h"

column_info_T PcmClockSourceTable::colInfo[pcm_clk_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


PcmClockSourceTable::PcmClockSourceTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

PcmClockSourceTable::~PcmClockSourceTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* PcmClockSourceTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* PcmClockSourceTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case pcm_clk_pri:
        return new CMibPcmClk_pri(sn, oid, oidLen, this);
    case pcm_clk_index:
        return new CMibPcmClk_index(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int PcmClockSourceTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    int maxIndex = XCPair::instance().getPcmClockManager()->getBackupClockSourceNumber();
    if( maxIndex > 0 ) {
        index->index[1] = 1;
        return 1;
    }
    return -1;
}

int PcmClockSourceTable::getNextIndex(index_info_T* index) {
    int maxIndex = XCPair::instance().getPcmClockManager()->getBackupClockSourceNumber();
    if( index->index[1] < maxIndex ) {
        ++(index->index[1]);
        return 1;
    }
    return -1;
}



int CMibPcmClk_pri::CallbackGet(const index_info_T& index) {
    return index.index[1];
}


int CMibPcmClk_index::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getPcmClockManager()->getBackupClockSource(index.index[1]-1);
}
int CMibPcmClk_index::callbackSet( const index_info_T& index, uint32 val) {
    if( XCPair::instance().getPcmClockManager()->setBackupClockSource(index.index[1]-1, val) ) {
        return 0x5A;
    }
    return -1;
}
