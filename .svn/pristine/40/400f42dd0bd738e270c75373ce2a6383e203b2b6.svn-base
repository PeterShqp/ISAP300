/*
 * CMibSDHBusTable.cpp
 *
 *  Created on: 2013-12-3
 *      Author: Administrator
 */

#include "CMibSDHBusTable.h"
#include "PairRscSDHBus.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibSDHBusTable::colInfo[] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};



CMibSDHBusTable::CMibSDHBusTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibSDHBusTable::~CMibSDHBusTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibSDHBusTable::getColInfo(int sn) {
    return &colInfo[sn];
}


/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* CMibSDHBusTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case sdh_bus_index:
        return new CMibSDHBusCol_uid(sn, oid, oidLen, this);
    case sdh_bus_name:
        return new CMibSDHBusCol_name(sn, oid, oidLen, this);
    case sdh_bus_map_from:
        return new CMibSDHBusCol_mapFrom(sn, oid, oidLen, this);
    default:
        return 0;
    }
}


int CMibSDHBusTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscSDHBus* p = PairRscSDHBus::getFirstInstance();
    if( p ) {
        index->index[1] = (p->getUID() >> 24) + 1;
        index->index[2] = p->getUID();
        return 1;
    }
    return -1;
}
int CMibSDHBusTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscSDHBus* p = PairRscSDHBus::getNextInstance(index->index[2]);
    if( p ) {
        index->index[1] = (p->getUID() >> 24) + 1;
        index->index[2] = p->getUID();
        return 1;
    }
    return -1;

}


int CMibSDHBusCol_uid::CallbackGet(const index_info_T& index) {
    PairRscSDHBus* pstm = PairRscSDHBus::getInstance(index.index[2]);
    if( pstm ) {
        return index.index[2];
    }
    else {
        return -1;
    }
}

int CMibSDHBusCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    PairRscSDHBus* pstm = PairRscSDHBus::getInstance(index.index[2]);
    if( pstm ) {
        std::string s = pstm->getName();
        *len = s.size();
        strcpy((char*)name, s.c_str());
        return 1;
    }
    return -1;
}

int CMibSDHBusCol_mapFrom::CallbackGet(const index_info_T& index) {
    PairRscSDHBus* pstm = PairRscSDHBus::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getConnectFrom();
    }
    else {
        return -1;
    }
}
