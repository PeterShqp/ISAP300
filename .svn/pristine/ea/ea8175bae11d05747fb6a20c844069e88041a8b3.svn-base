/*
 * CMibLPTable.cpp
 *
 *  Created on: 2013-12-4
 *      Author: Administrator
 */

#include "CMibLPTable.h"
#include "PairRscVC12.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibLPTable::colInfo[] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};



CMibLPTable::CMibLPTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibLPTable::~CMibLPTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibLPTable::getColInfo(int sn) {
    return &colInfo[sn];
}


/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* CMibLPTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case lp_bus_index:
        return new CMibLPBusCol_uid(sn, oid, oidLen, this);
    case lp_bus_name:
        return new CMibLPBusCol_name(sn, oid, oidLen, this);
    case lp_bus_map_from:
        return new CMibLPBusCol_mapFrom(sn, oid, oidLen, this);
    default:
        return 0;
    }
}


int CMibLPTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscVC12* p = PairRscVC12::getFirstInstance();
    if( p ) {
        index->index[1] = (p->getUID() >> 24) + 1;
        index->index[2] = p->getUID();
        return 1;
    }
    return -1;
}
int CMibLPTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscVC12* p = PairRscVC12::getNextInstance(index->index[2]);
    if( p ) {
        index->index[1] = (p->getUID() >> 24) + 1;
        index->index[2] = p->getUID();
        return 1;
    }
    return -1;

}


int CMibLPBusCol_uid::CallbackGet(const index_info_T& index) {
    PairRscVC12* pstm = PairRscVC12::getInstance(index.index[2]);
    if( pstm ) {
        return index.index[2];
    }
    else {
        return -1;
    }
}

int CMibLPBusCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    PairRscVC12* pstm = PairRscVC12::getInstance(index.index[2]);
    if( pstm ) {
        std::string s = pstm->getName();
        *len = s.size();
        strcpy((char*)name, s.c_str());
        return 1;
    }
    return -1;
}

int CMibLPBusCol_mapFrom::CallbackGet(const index_info_T& index) {
    PairRscVC12* pstm = PairRscVC12::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getConnectFrom();
    }
    else {
        return -1;
    }
}
