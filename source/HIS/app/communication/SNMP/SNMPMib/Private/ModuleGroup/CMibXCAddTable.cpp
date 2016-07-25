/*
 * CMibXCAddTable.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibXCAddTable.h"

#include "CCommonDefine.h"
#include "CrossConnectionManager.h"

column_info_T CMibXCAddTable::colInfo[xc_add_size] = {
		{1, Mib_write_only, CSnmpConstDefine::ucConstOctetString},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_write_only, CSnmpConstDefine::ucConstOctetString},
};


CMibXCAddTable::CMibXCAddTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibXCAddTable::~CMibXCAddTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibXCAddTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibXCAddTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case xc_add:
		return new CMibXCCol_add(sn, oid, oidLen, this);
	case xc_count:
		return new CMibXCCol_count(sn, oid, oidLen, this);
	case xc_clear:
	    return new CMibXCCol_clear(sn, oid, oidLen, this);
	case xc_biadd:
	    return new CMibXCCol_biadd(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibXCAddTable::getFirstIndex(index_info_T* index) {
    CrossConnectionManager* cm = CrossConnectionManager::getFirstInstance();
    if( cm ) {
        index->index_number = getTableInfo()->table_index_num;
        index->index[0] = CCommonDefine::uiConstDeviceIndex;
        index->index[1] = cm->getSlotSn() + 1;
        return 1;
    }
	return -1;
}

int CMibXCAddTable::getNextIndex(index_info_T* index) {
    CrossConnectionManager* cm = CrossConnectionManager::getNextInstance(index->index[1]-1);
    if( cm ) {
        index->index[1] = cm->getSlotSn() + 1;
        return 1;
    }
	return -1;
}

int CMibXCCol_add::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
	if( buf == 0 || len < 8 ) {
		return -1;
	}
	uint32 uiWestNode = (buf[0] << 24 ) | (buf[1] << 16 ) | (buf[2] << 8 ) | buf[3];
	uint32 uiEastNode = (buf[4] << 24 ) | (buf[5] << 16 ) | (buf[6] << 8 ) | buf[7];
	CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
	if( cm ) {
	    return cm->CreatConnection(uiWestNode, uiEastNode);
	}
	return -1;
}

int CMibXCCol_count::CallbackGet(const index_info_T& index) {
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    if( cm ) {
        return cm->count();
    }
    return -1;
}

int CMibXCCol_clear::callbackSet( const index_info_T& index, uint32 value ) {
    if( value != 0x454242) {
        return 0xee;
    }
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    if( cm ) {
        cm->clearAll();
        cm = CrossConnectionManager::getNextInstance(cm->getSlotSn());
        return 0x5A;
    }
    return 0xee;
}

int CMibXCCol_biadd::callbackSet( const index_info_T& index, uint8* buf, uint32 len) {
    if( buf == 0 || len < 8 ) {
        return -1;
    }
    uint32 uiWestNode = (buf[0] << 24 ) | (buf[1] << 16 ) | (buf[2] << 8 ) | buf[3];
    uint32 uiEastNode = (buf[4] << 24 ) | (buf[5] << 16 ) | (buf[6] << 8 ) | buf[7];
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    if( cm ) {
        return cm->CreatBiConnection(uiWestNode, uiEastNode);
    }
    return -1;
}
