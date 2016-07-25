/*
 * PcmUseableClockSourceTable.cpp
 *
 *  Created on: 2015Äê2ÔÂ25ÈÕ
 *      Author: Administrator
 */

#include "PcmUseableClockSourceTable.h"
#include "ClockSourceManager.h"
#include "ClockSource.h"
#include <string.h>
#include "CCommonDefine.h"
#include "XCPair.h"

column_info_T PcmUseableClockSourceTable::colInfo[pcm_usable_clk_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32}
};


PcmUseableClockSourceTable::PcmUseableClockSourceTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

PcmUseableClockSourceTable::~PcmUseableClockSourceTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* PcmUseableClockSourceTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* PcmUseableClockSourceTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case pcm_useable_clk_index:
        return new CMibPcmUsealbeClk_index(sn, oid, oidLen, this);
    case pcm_clk_name:
        return new CMibPcmUsealbeClk_name(sn, oid, oidLen, this);
    case pcm_clk_status:
        return new CMibPcmUsealbeClk_status(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int PcmUseableClockSourceTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    ClockSource* cs = XCPair::instance().getPcmClockManager()->getFirstClockSource();
    if( cs ) {
        index->index[1] = cs->getUID();
        return 1;
    }
    return -1;
}

int PcmUseableClockSourceTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    ClockSource* cs = XCPair::instance().getPcmClockManager()->getNextClockSource(index->index[1]);
    if( cs ) {
        index->index[1] = cs->getUID();
        return 1;
    }
    return -1;
}

int CMibPcmUsealbeClk_index::CallbackGet(const index_info_T& index) {
    ClockSource* cs = XCPair::instance().getPcmClockManager()->getClockSource(index.index[1]);
    if( cs ) {
        return cs->getUID();
    }
    return -1;
}

int CMibPcmUsealbeClk_name::CallbackGet(const index_info_T& index, uint8* s, uint32* len) {
    ClockSource* cs = XCPair::instance().getPcmClockManager()->getClockSource(index.index[1]);
    if( cs ) {
        std::string name = cs->getName();
        *len = name.size();
        strcpy((char*)s, name.c_str());
        return 0x5A;
    }
    return -1;
}

int CMibPcmUsealbeClk_status::CallbackGet(const index_info_T& index) {
    ClockSource* cs = XCPair::instance().getPcmClockManager()->getClockSource(index.index[1]);
    if( cs ) {
        return cs->getStatus();
    }
    return -1;
}
