/*
 * TableUseableClockSource.cpp
 *
 *  Created on: 2014-1-13
 *      Author: Administrator
 */

#include "TableUseableClockSource.h"
#include "ClockSourceManager.h"
#include "ClockSource.h"
#include <string.h>
#include "CCommonDefine.h"
#include "XCPair.h"

column_info_T TableUseableClockSource::colInfo[usable_clk_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32}
};


TableUseableClockSource::TableUseableClockSource(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableUseableClockSource::~TableUseableClockSource() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableUseableClockSource::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* TableUseableClockSource::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case clk_index:
        return new CMibUsealbeClk_index(sn, oid, oidLen, this);
    case clk_name:
        return new CMibUsealbeClk_name(sn, oid, oidLen, this);
    case clk_status:
        return new CMibUsealbeClk_status(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableUseableClockSource::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    ClockSource* cs = XCPair::instance().getSdhClockManager()->getFirstClockSource();
    if( cs ) {
        index->index[1] = cs->getUID();
        return 1;
    }
    return -1;
}

int TableUseableClockSource::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    ClockSourceManager* m = XCPair::instance().getSdhClockManager();
    if( m ) {
        ClockSource* cs = m->getNextClockSource(index->index[1]);
        if( cs ) {
            index->index[1] = cs->getUID();
            return 1;
        }
    }
    return -1;
}

int CMibUsealbeClk_index::CallbackGet(const index_info_T& index) {
    ClockSourceManager* m = XCPair::instance().getSdhClockManager();
    if( m ) {
        ClockSource* cs = m->getClockSource(index.index[1]);
        if( cs ) {
            return cs->getUID();
        }
    }
    return -1;
}

int CMibUsealbeClk_name::CallbackGet(const index_info_T& index, uint8* s, uint32* len) {
    ClockSourceManager* m = XCPair::instance().getSdhClockManager();
    if( m ) {
        ClockSource* cs = m->getClockSource(index.index[1]);
        if( cs ) {
            std::string name = cs->getName();
            *len = name.size();
            strcpy((char*)s, name.c_str());
            return 0x5A;
        }
    }
    return -1;
}

int CMibUsealbeClk_status::CallbackGet(const index_info_T& index) {
    ClockSourceManager* m = XCPair::instance().getSdhClockManager();
    if( m ) {
        ClockSource* cs = m->getClockSource(index.index[1]);
        if( cs ) {
            return cs->getStatus();
        }
    }
    return -1;
}
