/*
 * CMibSTMOverheadTable.cpp
 *
 *  Created on: 2013-4-19
 *      Author: Administrator
 */

#include "CMibSTMOverheadTable.h"
#include "PairPortSTM.h"
//#include "DeviceLocal.h"
//#include "SDHGroup.h"
#include "CCommonDefine.h"
#include "string.h"
#include "PortSTM4.h"
#include "UID.h"

column_info_T CMibSTMOverheadTable::colInfo[stm_oh_size] = {
		{1, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{2, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
		{3, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
		{4, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {5, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {6, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {7, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibSTMOverheadTable::CMibSTMOverheadTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
	makeColumnOid();
}

CMibSTMOverheadTable::~CMibSTMOverheadTable() {
	// TODO Auto-generated destructor stub
}

column_info_T* CMibSTMOverheadTable::getColInfo(int sn) {
	return &colInfo[sn];
}

CMibNodeObject* CMibSTMOverheadTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case stm_oh_J0_Transmit:
		return new CMibSTMOverheadCol_J0Transmit(sn, oid, oidLen, this);
	case stm_oh_J0_expected:
		return new CMibSTMOverheadCol_J0Expected(sn, oid, oidLen, this);
	case stm_oh_J0_Receive:
		return new CMibSTMOverheadCol_J0Receive(sn, oid, oidLen, this);
	case stm_oh_B1_counter:
	    return new CMibSTMOverheadCol_B1(sn, oid, oidLen, this);
    case stm_oh_B2_counter:
        return new CMibSTMOverheadCol_B2(sn, oid, oidLen, this);
    case stm_oh_j0_TLen:
        return new CMibSTMOverheadCol_J0TLen(sn, oid, oidLen, this);
    case stm_oh_j0_RLen:
        return new CMibSTMOverheadCol_J0RLen(sn, oid, oidLen, this);
	default:
		return 0;
	}
}
int CMibSTMOverheadTable::getFirstIndex(index_info_T* index) {
//	index->index_number = getTableInfo()->table_index_num;
//	index->index[0] = CCommonDefine::uiConstDeviceIndex;
//    PairPortSTM* p = PairPortSTM::getFirstInstance();
//    if( p ) {
//       index->index[1] = (p->getUID() >> 24) + 1;
//       index->index[2] = p->getUID();
//        return 1;
//    }
//    return -1;
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairPortSTM* p = PairPortSTM::getFirstInstance();
    if( p ) {
       index->index[1] = (p->getUID() >> 24) + 1;
       index->index[2]  = p->getUID();
        return 1;
    }
    return -1;
}
int CMibSTMOverheadTable::getNextIndex(index_info_T* index) {
//	index->index_number = getTableInfo()->table_index_num;
//	index->index[0] = CCommonDefine::uiConstDeviceIndex;
//    PairPortSTM* p = PairPortSTM::getNextInstance(index->index[2]);
//    if( p ) {
//        index->index[1] = (p->getUID() >> 24) + 1;
//        index->index[2] = p->getUID();
//        return 1;
//    }
//    return -1;
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    uint8 slot = (index->index[2] >> 24) & 0xf;
    Resource* pp = 0;
    if( slot < 2 ) {
        pp = PairPortSTM::getNextInstance(index->index[2]);
        if( !pp ) {
            pp = PortSTM4::getNextInstance(UID::getPartnerUID(index->index[2]));
            if( !pp ) {
                pp = PortSTM4::getNextInstance(index->index[2]);
            }
        }

    }
    else {
        pp = PortSTM4::getNextInstance(index->index[2]);

    }
    if( pp ) {
        index->index[1] = (pp->getUID() >> 24) + 1;
        index->index[2] = pp->getUID();
        return 1;
    }
    return -1;
}


int CMibSTMOverheadCol_J0Transmit::CallbackGet(const index_info_T& index, uint8* j0, uint32* len) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
	if( pstm ) {
		uint32 dlen = 0;
		uint8* p = pstm->getJ0Transmit(&dlen);
		if( p ) {
			*len = dlen;
			memcpy(j0, p, dlen);
			return 1;
		}
		return 1;
	}
	return -1;
}
int CMibSTMOverheadCol_J0Transmit::callbackSet(const index_info_T& index, uint8* j0, uint32 len) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
	if( pstm ) {
		pstm->setJ0Transmit(j0, len);
		return 0x5A;
	}
	return -1;
}

int CMibSTMOverheadCol_J0Expected::CallbackGet(const index_info_T& index, uint8* j0, uint32* len) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
	if( pstm ) {
		uint32 dlen = 0;
		uint8* p = pstm->getJ0Expected(&dlen);
		if( p ) {
			*len = dlen;
			memcpy(j0, p, dlen);
			return 1;
		}
		return 1;
	}
	return -1;
}
int CMibSTMOverheadCol_J0Expected::callbackSet(const index_info_T& index, uint8* j0, uint32 len) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
	if( pstm ) {
		pstm->setJ0Expected(j0, len);
		return 0x5A;
	}
	return -1;
}

int CMibSTMOverheadCol_J0Receive::CallbackGet(const index_info_T& index, uint8* j0, uint32* len) {
    PortSTM4* pstm = PortSTM4::getInstance(index.index[2]);
	if( pstm ) {
		uint32 dlen = 0;
		uint8* p = pstm->getJ0Received(&dlen);
		if( p ) {
			*len = dlen;
			memcpy(j0, p, dlen);
			return 1;
		}
		return 1;
	}
	return -1;
}

int CMibSTMOverheadCol_B1::CallbackGet(const index_info_T& index) {
    PortSTM4* pstm = PortSTM4::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getB1Counter();
    }
    return -1;
}

int CMibSTMOverheadCol_B2::CallbackGet(const index_info_T& index) {
    PortSTM4* pstm = PortSTM4::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getB2Counter();
    }
    return -1;
}

int CMibSTMOverheadCol_J0TLen::CallbackGet(const index_info_T& index) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getJ0TLen();
    }
    return -1;
}

int CMibSTMOverheadCol_J0TLen::callbackSet( const index_info_T& index, uint32 mode) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
    if( pstm ) {
        pstm->setJ0TLen(mode);
        return 0x5A;
    }
    return -1;
}


int CMibSTMOverheadCol_J0RLen::CallbackGet(const index_info_T& index) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
    if( pstm ) {
        return pstm->getJ0RLen();
    }
    return -1;
}

int CMibSTMOverheadCol_J0RLen::callbackSet( const index_info_T& index, uint32 mode) {
    PairPortSTM* pstm = PairPortSTM::getInstance(index.index[2]);
    if( pstm ) {
        pstm->setJ0RLen(mode);
        return 0x5A;
    }
    return -1;
}
