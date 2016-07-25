/*
 * TableTopoStatus.cpp
 *
 *  Created on: 2013-7-12
 *      Author: Administrator
 */

#include "TableTopoStatus.h"
#include "CCommonDefine.h"
#include <string.h>
#include "NMPort.h"

column_info_T TableTopoStatus::colInfo[topo_status_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{2, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
		{3, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},

};


TableTopoStatus::TableTopoStatus(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

TableTopoStatus::~TableTopoStatus() {
	// TODO Auto-generated destructor stub
}

column_info_T* TableTopoStatus::getColInfo(int sn) {
	return &colInfo[sn];
}


/*
 * STMConfig table ��������
 */
CMibNodeObject* TableTopoStatus::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case NM_Channel_uid:
		return new ColTopoStatus_uid(sn, oid, oidLen, this);
	case upstream_port_uid:
		return new ColTopoStatus_port(sn, oid, oidLen, this);
	case upStream_device_ip:
		return new ColTopoStatus_ip(sn, oid, oidLen, this);
	case local_port_speed:
		return new ColTopoStatus_speed(sn, oid, oidLen, this);
	default:
		return 0;
	}
}


int TableTopoStatus::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	NMPort* ch = NMPort::getFirstInstance();
	if( ch ) {
		index->index[1] = ch->getUID();
		return 1;
	}
	return -1;
}
int TableTopoStatus::getNextIndex(index_info_T* index) {
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	NMPort* ch = NMPort::getNextInstance(index->index[1]);
	if( ch ) {
		index->index[1] = ch->getUID();
		return 1;
	}
	return -1;
}

int ColTopoStatus_uid::CallbackGet(const index_info_T& index) {
	NMPort* ch = NMPort::getInstance(index.index[1]);
	if( ch ) {
		return ch->getUID();
	}
	return -1;
}

int ColTopoStatus_port::CallbackGet(const index_info_T& index) {
	NMPort* ch = NMPort::getInstance(index.index[1]);
	if( ch ) {
		return ch->getUpStreamPortUid();
	}
	return -1;
}

int ColTopoStatus_ip::CallbackGet(const index_info_T& index, uint8* buf, uint32* len) {
	NMPort* ch = NMPort::getInstance(index.index[1]);
	if( ch ) {
		*len = 4;
		memcpy( buf, ch->getUpStreamIP(), 4 );
		return 1;
	}
	return -1;
}

int ColTopoStatus_speed::CallbackGet(const index_info_T& index) {
	return 0;
}
