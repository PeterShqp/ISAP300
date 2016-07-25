/*
 * CMibSDHChannelTable.cpp
 *
 *  Created on: 2013-12-3
 *      Author: Administrator
 */

#include "CMibSDHChannelTable.h"
#include "PairRscSDHChannel.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibSDHChannelTable::colInfo[sdh_ch_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {4, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
};



CMibSDHChannelTable::CMibSDHChannelTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibSDHChannelTable::~CMibSDHChannelTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibSDHChannelTable::getColInfo(int sn) {
    return &colInfo[sn];
}


/*
 * STMConfig table ��������
 */
CMibNodeObject* CMibSDHChannelTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case sdh_ch_index:
        return new CMibSDHchCol_uid(sn, oid, oidLen, this);
    case sdh_ch_down_id:
        return new CMibSDHchCol_down(sn, oid, oidLen, this);
    case sdh_ch_up_id:
        return new CMibSDHchCol_up(sn, oid, oidLen, this);
    case sdh_ch_name:
        return new CMibSDHchCol_name(sn, oid, oidLen, this);
    default:
        return 0;
    }
}


int CMibSDHChannelTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscSDHChannel* p = PairRscSDHChannel::getFirstInstance();
    if( p ) {
        index->index[1] = (p->getUID() >> 24) + 1;
        index->index[2] = p->getUID();
        return 1;
    }
    return -1;
}
int CMibSDHChannelTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairRscSDHChannel* p = PairRscSDHChannel::getNextInstance(index->index[2]);
    if( p ) {
        index->index[1] = (p->getUID() >> 24) + 1;
        index->index[2] = p->getUID();
        return 1;
    }
    return -1;

}


int CMibSDHchCol_uid::CallbackGet(const index_info_T& index) {
    PairRscSDHChannel* pstm = PairRscSDHChannel::getInstance(index.index[2]);
    if( pstm ) {
        return index.index[2];
    }
    else {
        return -1;
    }
}

int CMibSDHchCol_up::CallbackGet(const index_info_T& index) {
    PairRscSDHChannel* pstm = PairRscSDHChannel::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getConnectFrom();
    }
    else {
        return -1;
    }
}

int CMibSDHchCol_down::CallbackGet(const index_info_T& index) {
    PairRscSDHChannel* pstm = PairRscSDHChannel::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getDownStream();
    }
    else {
        return -1;
    }
}

int CMibSDHchCol_name::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
    PairRscSDHChannel* pstm = PairRscSDHChannel::getInstance(index.index[2]);
    if( pstm ) {
        std::string& name = pstm->getName();
        *len = name.size();
        strcpy((char*)buf, name.c_str());
        return 1;
    }
    else {
        return -1;
    }
}
