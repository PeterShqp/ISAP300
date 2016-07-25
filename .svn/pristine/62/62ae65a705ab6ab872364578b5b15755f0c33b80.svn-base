/*
 * PcmClockOptionTable.cpp
 *
 *  Created on: 2015Äê2ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "PcmClockOptionTable.h"
#include "ClockSourceManager.h"
#include "CCommonDefine.h"
#include "XCPair.h"

column_info_T PcmClockOptionTable::colInfo[pcm_clk_option_size] = {
        {1, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


PcmClockOptionTable::PcmClockOptionTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

PcmClockOptionTable::~PcmClockOptionTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* PcmClockOptionTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* PcmClockOptionTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case pcm_back_clk_num:
        return new CMibPcmclkoption_number(sn, oid, oidLen, this);
    case pcm_cur_clk:
        return new CMibPcmclkoption_curclk(sn, oid, oidLen, this);
    case pcm_assign_clk:
        return new CMibPcmclkoption_assign(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int PcmClockOptionTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    return 1;
}

int PcmClockOptionTable::getNextIndex(index_info_T* index) {
    return -1;
}

int CMibPcmclkoption_number::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getPcmClockManager()->getBackupClockSourceNumber();
}
int CMibPcmclkoption_number::callbackSet( const index_info_T& index, uint32 val) {
    bool rtn = XCPair::instance().getPcmClockManager()->setBackupClockSourceNumber(val);
    if( rtn ) {
        return 0x5A;
    }
    return -1;
}

int CMibPcmclkoption_curclk::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getPcmClockManager()->getWorkingClockSource();
}

int CMibPcmclkoption_assign::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getPcmClockManager()->getExpectClockSource();
}
int CMibPcmclkoption_assign::callbackSet( const index_info_T& index, uint32 val) {
    if( XCPair::instance().getPcmClockManager()->setExpectClockSource(val) ) {
        return 0x5A;
    }
    return -1;
}

