/*
 * CMibHPOverheadTable.cpp
 *
 *  Created on: 2014-4-12
 *      Author: Administrator
 */

#include "CMibHPOverheadTable.h"
#include "PairRscVC4.h"
#include "CCommonDefine.h"
#include <string.h>
#include "RscVC4.h"

column_info_T CMibHPOverheadTable::colInfo[hp_oh_size] = {
        {1, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
        {2, Mib_read_write, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {4, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {5, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {6, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {7, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {8, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {9, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
};


CMibHPOverheadTable::CMibHPOverheadTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibHPOverheadTable::~CMibHPOverheadTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibHPOverheadTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* CMibHPOverheadTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case hp_oh_J1_Transmit:
        return new CMibHPOverheadCol_J1Transmit(sn, oid, oidLen, this);
    case hp_oh_J1_expected:
        return new CMibHPOverheadCol_J1Expected(sn, oid, oidLen, this);
    case hp_oh_J1_Receive:
        return new CMibHPOverheadCol_J1Receive(sn, oid, oidLen, this);
    case hp_oh_C2_Transmit:
        return new CMibHPOverheadCol_C2Transmit(sn, oid, oidLen, this);
    case hp_oh_C2_Expected:
        return new CMibHPOverheadCol_C2Expected(sn, oid, oidLen, this);
    case hp_oh_C2_Received:
        return new CMibHPOverheadCol_C2Receive(sn, oid, oidLen, this);
    case hp_oh_B3_Counter:
        return new CMibHPOverheadCol_B3(sn, oid, oidLen, this);
    case hp_oh_j1_TLen:
        return new CMibHPOverheadCol_J1TLen(sn, oid, oidLen, this);
    case hp_oh_j1_RLen:
        return new CMibHPOverheadCol_J1RLen(sn, oid, oidLen, this);
    default:
        return 0;
    }
}
int CMibHPOverheadTable::getFirstIndex(index_info_T* index) {
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
int CMibHPOverheadTable::getNextIndex(index_info_T* index) {
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


int CMibHPOverheadCol_J1Transmit::CallbackGet(const index_info_T& index, uint8* j1, uint32* len) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        uint8* d = p->getJ1Transmit(len);
        memcpy(j1, d, *len);
        return 1;
    }
    return -1;
}
int CMibHPOverheadCol_J1Transmit::callbackSet(const index_info_T& index, uint8* j1, uint32 len) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        if( p->setJ1Transmit(j1, len) ) {
            return 0x5A;
        }
    }
    return -1;
}

int CMibHPOverheadCol_J1Expected::CallbackGet(const index_info_T& index, uint8* j1, uint32* len) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        uint8* d = p->getJ1Expected(len);
        memcpy(j1, d, *len);
        return 1;
    }
    return -1;
}

int CMibHPOverheadCol_J1Expected::callbackSet(const index_info_T& index, uint8* j1, uint32 len) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        if( p->setJ1Expected(j1, len) ) {
            return 0x5A;
        }
    }
    return -1;
}

int CMibHPOverheadCol_J1Receive::CallbackGet(const index_info_T& index, uint8* j1, uint32* len) {
    RscVC4* p = RscVC4::getInstance(index.index[2]);
    if( p ) {
        uint8* d = p->getJ1Received(len);
        memcpy(j1, d, *len);
        return 1;
    }
    return -1;
}


int CMibHPOverheadCol_C2Transmit::CallbackGet(const index_info_T& index) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {

    }
    return -1;
}
int CMibHPOverheadCol_C2Transmit::callbackSet( const index_info_T& index, uint32 ) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {

    }
    return -1;

}

int CMibHPOverheadCol_C2Expected::CallbackGet(const index_info_T& index) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {

    }
    return -1;
}
int CMibHPOverheadCol_C2Expected::callbackSet( const index_info_T& index, uint32 ) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {

    }
    return -1;

}
int CMibHPOverheadCol_C2Receive::CallbackGet(const index_info_T& index) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {

    }
    return -1;
}

int CMibHPOverheadCol_B3::CallbackGet(const index_info_T& index) {
    RscVC4* p = RscVC4::getInstance(index.index[2]);
    if( p ) {
        return p->getB3Counter();
    }
    return -1;
}


int CMibHPOverheadCol_J1TLen::CallbackGet(const index_info_T& index) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        return p->getJ1TLen();
    }
    return -1;
}

int CMibHPOverheadCol_J1TLen::callbackSet( const index_info_T& index, uint32 v) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        if( p->setJ1TLen(v) ) {
            return 0x5A;
        }
    }
    return -1;

}


int CMibHPOverheadCol_J1RLen::CallbackGet(const index_info_T& index) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        return p->getJ1RLen();
    }
    return -1;
}

int CMibHPOverheadCol_J1RLen::callbackSet( const index_info_T& index, uint32 v) {
    PairRscVC4* p = PairRscVC4::getInstance(index.index[2]);
    if( p ) {
        if( p->setJ1RLen(v) ) {
            return 0x5A;
        }
    }
    return -1;

}
