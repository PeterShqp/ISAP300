/*
 * TableClockSourceOption.cpp
 *
 *  Created on: 2014-1-16
 *      Author: Administrator
 */

#include "TableClockSourceOption.h"
#include "ClockSourceManager.h"
#include "CCommonDefine.h"
#include "XCPair.h"

column_info_T TableClockSourceOption::colInfo[clk_option_size] = {
        {1, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


TableClockSourceOption::TableClockSourceOption(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableClockSourceOption::~TableClockSourceOption() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableClockSourceOption::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* TableClockSourceOption::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case back_clk_num:
        return new CMibclkoption_number(sn, oid, oidLen, this);
    case cur_clk:
        return new CMibclkoption_curclk(sn, oid, oidLen, this);
    case assign_clk:
        return new CMibclkoption_assign(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableClockSourceOption::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    return 1;
}

int TableClockSourceOption::getNextIndex(index_info_T* index) {
    return -1;
}

int CMibclkoption_number::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getSdhClockManager()->getBackupClockSourceNumber();
}
int CMibclkoption_number::callbackSet( const index_info_T& index, uint32 val) {
    bool rtn = XCPair::instance().getSdhClockManager()->setBackupClockSourceNumber(val);
    if( rtn ) {
        return 0x5A;
    }
    return -1;
}

int CMibclkoption_curclk::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getSdhClockManager()->getWorkingClockSource();
}

int CMibclkoption_assign::CallbackGet(const index_info_T& index) {
    return XCPair::instance().getSdhClockManager()->getExpectClockSource();
}
int CMibclkoption_assign::callbackSet( const index_info_T& index, uint32 val) {
    if( XCPair::instance().getSdhClockManager()->setExpectClockSource(val) ) {
        return 0x5A;
    }
    return -1;
}

