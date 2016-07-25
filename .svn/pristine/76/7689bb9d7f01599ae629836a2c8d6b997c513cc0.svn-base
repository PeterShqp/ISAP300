/*
 * CMibHPTable.cpp
 *
 *  Created on: 2013-12-4
 *      Author: Administrator
 */

#include "CMibHPTable.h"
#include "PairRscVC4.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibHPTable::colInfo[] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};



CMibHPTable::CMibHPTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibHPTable::~CMibHPTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibHPTable::getColInfo(int sn) {
    return &colInfo[sn];
}


/*
 * STMConfig table 工厂方法
 */
CMibNodeObject* CMibHPTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case hp_bus_index:
        return new CMibHPBusCol_uid(sn, oid, oidLen, this);
    case hp_bus_name:
        return new CMibHPBusCol_name(sn, oid, oidLen, this);
    case hp_bus_map_from:
        return new CMibHPBusCol_mapFrom(sn, oid, oidLen, this);
    default:
        return 0;
    }
}


int CMibHPTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscVC4* p = PairRscVC4::getFirstInstance();
    if( p ) {
        index->index[1] = (p->getUID() >> 24) + 1;
        index->index[2] = p->getUID();
        return 1;
    }
    return -1;
}
int CMibHPTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscVC4* p = PairRscVC4::getNextInstance(index->index[2]);
    if( p ) {
       index->index[1] = (p->getUID() >> 24) + 1;
       index->index[2] = p->getUID();
        return 1;
    }
    return -1;

}


int CMibHPBusCol_uid::CallbackGet(const index_info_T& index) {
    PairRscVC4* pstm = PairRscVC4::getInstance(index.index[2]);
    if( pstm ) {
        return index.index[2];
    }
    else {
        return -1;
    }
}

int CMibHPBusCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    PairRscVC4* pstm = PairRscVC4::getInstance(index.index[2]);
    if( pstm ) {
        std::string s = pstm->getName();
        *len = s.size();
        strcpy((char*)name, s.c_str());
        return 1;
    }
    return -1;
}

int CMibHPBusCol_mapFrom::CallbackGet(const index_info_T& index) {
    PairRscVC4* pstm = PairRscVC4::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getConnectFrom();
    }
    else {
        return -1;
    }
}
