/*
 * CMibSltchTable.cpp
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#include "CMibSltchTable.h"
#include "Slot155Channel.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibSltchTable::colInfo[sltch_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


CMibSltchTable::CMibSltchTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibSltchTable::~CMibSltchTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibSltchTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* CMibSltchTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case sltch_index:
        return new CMibSlot155ChannelCol_index(sn, oid, oidLen, this);
    case sltch_name:
        return new CMibSlot155ChannelCol_name(sn, oid, oidLen, this);
    case sltch_upstream:
        return new CMibSlot155ChannelCol_up(sn, oid, oidLen, this);
    case sltch_downstream:
       return new CMibSlot155ChannelCol_down(sn, oid, oidLen, this);
    default:
        return 0;
    }
}
int CMibSltchTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    Slot155Channel* pvc = Slot155Channel::getFirstInstance();
    if( pvc ) {
        uint32 uid = pvc->getUID();
        index->index[1] = (uid >> 24) + 1;
        index->index[2] = uid;
        return 1;
    }
    return -1;

}
int CMibSltchTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;

    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    Slot155Channel* pvc = Slot155Channel::getNextInstance(index->index[2]);
    if( pvc ) {
        uint32 uid = pvc->getUID();
        index->index[1] = (uid >> 24) + 1;
        index->index[2] = uid;
        return 1;
    }
    return -1;
}

int CMibSlot155ChannelCol_index::CallbackGet(const index_info_T& index) {
    return index.index[2];
}

int CMibSlot155ChannelCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    Slot155Channel* pSlot155Channel = Slot155Channel::getInstance(index.index[2]);
    if( pSlot155Channel ) {
        std::string& nm = pSlot155Channel->getName();
        strcpy((char*)name, nm.c_str());
        *len = nm.size();
        return 1;
    }
    return -1;
}

int CMibSlot155ChannelCol_up::CallbackGet(const index_info_T& index) {
    Slot155Channel* pSlot155Channel = Slot155Channel::getInstance(index.index[2]);
    if( pSlot155Channel ) {
        return pSlot155Channel->getUpStream();
    }
    return -1;
}

int CMibSlot155ChannelCol_down::CallbackGet(const index_info_T& index) {
    Slot155Channel* pSlot155Channel = Slot155Channel::getInstance(index.index[2]);
    if( pSlot155Channel ) {
        return pSlot155Channel->getDownStream();
    }
    return -1;
}


