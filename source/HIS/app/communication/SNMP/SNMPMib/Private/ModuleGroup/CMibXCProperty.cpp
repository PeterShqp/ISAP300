/*
 * CMibXCProperty.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibXCProperty.h"
#include "CCommonDefine.h"
#include <string>
#include "CrossConnectionManager.h"
#include <string.h>
#include "CCrossConnection.h"

column_info_T CMibXCProperty::colInfo[xc_property_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{4, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{5, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{6, Mib_write_only, CSnmpConstDefine::ucConstInteger32},
//		{7, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibXCProperty::CMibXCProperty(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibXCProperty::~CMibXCProperty() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibXCProperty::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibXCProperty::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case xc_index:
		return new CMibXCPropertyCol_index(sn, oid, oidLen, this);
	case xc_src_id:
		return new CMibXCPropertyCol_srcid(sn, oid, oidLen, this);
	case xc_dest_id:
		return new CMibXCPropertyCol_destid(sn, oid, oidLen, this);
	case xc_name:
		return new CMibXCPropertyCol_name(sn, oid, oidLen, this);
	case xc_description:
		return new CMibXCPropertyCol_desc(sn, oid, oidLen, this);
	case xc_delete:
		return new CMibXCPropertyCol_delete(sn, oid, oidLen, this);
//	case xc_sncp:
//	    return new CMibXCPropertyCol_sncp(sn, oid, oidLen, this);
	default:
		return 0;
	}
}

int CMibXCProperty::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	CrossConnectionManager* cm = CrossConnectionManager::getFirstInstance();
	while( cm ) {
	    index->index[1] = cm->getSlotSn() + 1;
	    index->index[2] = cm->GetFirstSnOfConnection();
        if( index->index[2] != 0 ) {
            return 1;
        }
        else {
            cm = CrossConnectionManager::getNextInstance(cm->getSlotSn());
        }
	}
	return -1;
}

int CMibXCProperty::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index->index[1]-1);
    bool cmExchange = false;
    while( cm ) {
        if( cmExchange ) {
            index->index[2] = cm->GetFirstSnOfConnection();
            cmExchange = false;
        }
        else {
            index->index[2] = cm->GetNextSnConnection(index->index[2]);
        }
        if( index->index[2] != 0 ) {
            index->index[1] = cm->getSlotSn() + 1;
            return 1;
        }
        else {
            cm = CrossConnectionManager::getNextInstance(cm->getSlotSn());
            cmExchange = true;
        }
    }
	return -1;
}

int CMibXCPropertyCol_index::CallbackGet(const index_info_T& index) {
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    CCrossConnection* c = 0;
    if( cm ) {
        c = cm->getCC(index.index[2]);
    }
    if( c ) {
        return c->GetSn();
    }
	return -1;
}

int CMibXCPropertyCol_srcid::CallbackGet(const index_info_T& index) {
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    CCrossConnection* c = 0;
    if( cm ) {
        c = cm->getCC(index.index[2]);
    }
	if( c )
		return c->GetSrcUID();
	return -1;
}
int CMibXCPropertyCol_destid::CallbackGet(const index_info_T& index) {
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    CCrossConnection* c = 0;
    if( cm ) {
        c = cm->getCC(index.index[2]);
    }
	if( c )
		return c->GetdestUID();
	return -1;
}

int CMibXCPropertyCol_name::CallbackGet(const index_info_T& index, uint8* data, uint32* len) {
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    CCrossConnection* c = 0;
    if( cm ) {
        c = cm->getCC(index.index[2]);
    }
    if( c ) {
        std::string& name = c->GetName();
        *len = name.size();
        memcpy( data, name.c_str(), (uint32)name.size() );
        return 1;
    }
    return -1;
}
int CMibXCPropertyCol_name::callbackSet( const index_info_T& index, uint8* data, uint32 len) {
	std::string name((char*)data, len);
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    if( cm ) {
        if( cm->SetXcName(index.index[2], name) ) {
            return 0x5A;
        }
    }
	return -1;
}

int CMibXCPropertyCol_desc::CallbackGet(const index_info_T& index, uint8* data, uint32* len) {
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    CCrossConnection* c = 0;
    if( cm ) {
        c = cm->getCC(index.index[2]);
    }
    if( c ) {
        std::string& desc = c->GetDescription();
        *len = desc.size();
        memcpy( data, desc.c_str(), (uint32)desc.size() );
        return 1;
    }
    return -1;
}
int CMibXCPropertyCol_desc::callbackSet( const index_info_T& index, uint8* data, uint32 len) {
    std::string desc((char*)data, len);
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    if( cm ) {
        if( cm->SetXcDescription(index.index[2], desc) ) {
            return 0x5A;
        }
    }
    return -1;
}

int CMibXCPropertyCol_delete::callbackSet( const index_info_T& index, uint32 mapid) {
    CrossConnectionManager* cm = CrossConnectionManager::getInstance(index.index[1]-1);
    if( cm ) {
        if( cm->deleteConnection(index.index[2]) ) {
            return 0x5A;
        }
    }
	return -1;
}

//int CMibXCPropertyCol_sncp::CallbackGet(const index_info_T& index) {
//    return 0;
//}
//int CMibXCPropertyCol_sncp::callbackSet( const index_info_T& index, uint32 ) {
//    return -1;
//}
