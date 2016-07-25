/*
 * CMibVcgMemberTable.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibVcgMemberTable.h"
#include "VCG.h"
#include "CHVC.h"
#include "CCommonDefine.h"
#include "UID.h"

column_info_T CMibVcgMemberTable::colInfo[vcg_member_size] = {
		{1, Mib_read_only, CSnmpConstDefine::ucConstInteger32}
};


CMibVcgMemberTable::CMibVcgMemberTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibVcgMemberTable::~CMibVcgMemberTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibVcgMemberTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibVcgMemberTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case vcg_member_index:
		return new CMibVCGMemberCol_index(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibVcgMemberTable::getFirstIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;
	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	VCG* vcg = VCG::getFirstInstance();

	while( vcg ) {
        index->index[1] = (vcg->getUID() >> 24) + 1;
	    index->index[2] = vcg->getUID();
	    CHVC* member = vcg->getFirstMember();
	    if( member ) {
            index->index[3] = member->getUID();
	        return 1;
	    }
	    vcg = VCG::getNextInstance(index->index[2]);
	}

	return -1;

}
int CMibVcgMemberTable::getNextIndex(index_info_T* index) {
	index->index_number = getTableInfo()->table_index_num;

	index->index[0] = CCommonDefine::uiConstDeviceIndex;
	VCG* pvcg = VCG::getInstance(index->index[2]);
	if( pvcg == 0 ) {
	    pvcg = VCG::getFirstInstance();
	}
	while( pvcg ) {
        index->index[1] = (pvcg->getUID() >> 24) + 1;
        index->index[2] = pvcg->getUID();
	    CHVC* pmember = pvcg->getNextMember(index->index[3]);
	    if( pmember ) {
	        index->index[3] = pmember->getUID();
	        return 1;
	    }
	    pvcg = VCG::getNextInstance(index->index[2]);
	}
	return -1;


}


int CMibVCGMemberCol_index::CallbackGet(const index_info_T& index) {
	VCG* vcg = VCG::getInstance(index.index[2]);
	if( vcg ) {
	    CHVC* member = vcg->getMemberInstance(index.index[3]);
	    if( member ) {
	        return member->getUID();
	    }
	}
	return -1;
}


