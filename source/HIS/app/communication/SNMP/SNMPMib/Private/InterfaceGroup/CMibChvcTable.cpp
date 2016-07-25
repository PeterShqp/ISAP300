/*
 * CMibChvcTable.cpp
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#include "CMibChvcTable.h"
#include "CHVC.h"
#include "CCommonDefine.h"
#include <string.h>

column_info_T CMibChvcTable::colInfo[chvc_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {5, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {6, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibChvcTable::CMibChvcTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibChvcTable::~CMibChvcTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibChvcTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* CMibChvcTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case chvc_index:
        return new CMibCHVCCol_index(sn, oid, oidLen, this);
    case chvc_name:
        return new CMibCHVCCol_name(sn, oid, oidLen, this);
    case chvc_upstream:
        return new CMibCHVCCol_up(sn, oid, oidLen, this);
    case chvc_downstream:
       return new CMibCHVCCol_down(sn, oid, oidLen, this);
    case chvc_protect_partner:
        return new CMibCHVCCol_protect(sn, oid, oidLen, this);
    case chvc_sncp:
        return new CMibCHVCCol_sncp(sn, oid, oidLen, this);
    default:
        return 0;
    }
}
int CMibChvcTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    CHVC* pvc = CHVC::getFirstInstance();
    if( pvc ) {
        uint32 uid = pvc->getUID();
        index->index[1] = (uid >> 24) + 1;
        index->index[2] = uid;
        return 1;
    }
    return -1;

}
int CMibChvcTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;

    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    CHVC* pvc = CHVC::getNextInstance(index->index[2]);
    if( pvc ) {
        uint32 uid = pvc->getUID();
        index->index[1] = (uid >> 24) + 1;
        index->index[2] = uid;
        return 1;
    }
    return -1;
}

int CMibCHVCCol_index::CallbackGet(const index_info_T& index) {
    return index.index[2];
}

int CMibCHVCCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    CHVC* pchvc = CHVC::getInstance(index.index[2]);
    if( pchvc ) {
        std::string& nm = pchvc->getName();
        strcpy((char*)name, nm.c_str());
        *len = nm.size();
        return 1;
    }
    return -1;
}

int CMibCHVCCol_up::CallbackGet(const index_info_T& index) {
    CHVC* pchvc = CHVC::getInstance(index.index[2]);
    if( pchvc ) {
        return pchvc->getUpStream();
    }
    return -1;
}

int CMibCHVCCol_down::CallbackGet(const index_info_T& index) {
    CHVC* pchvc = CHVC::getInstance(index.index[2]);
    if( pchvc ) {
        return pchvc->getDownStream();
    }
    return -1;
}

int CMibCHVCCol_protect::CallbackGet(const index_info_T& index) {
    CHVC* pchvc = CHVC::getInstance(index.index[2]);
    if( pchvc ) {
        return pchvc->getProtectPartner();
    }
    return -1;
}

int CMibCHVCCol_sncp::CallbackGet(const index_info_T& index) {
    CHVC* pchvc = CHVC::getInstance(index.index[2]);
    if( pchvc ) {
        return pchvc->getSNCP();
    }
    return -1;
}
int CMibCHVCCol_sncp::callbackSet( const index_info_T& index, uint32 value) {
    CHVC* pchvc = CHVC::getInstance(index.index[2]);
    if( pchvc ) {
        pchvc->setSNCP(value);
        return 0x5A;
    }
    return -1;
}
