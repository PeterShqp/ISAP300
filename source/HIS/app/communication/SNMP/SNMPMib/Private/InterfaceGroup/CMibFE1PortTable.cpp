/*
 * CMibFE1PortTable.cpp
 *
 *  Created on: 2015年7月4日
 *      Author: Administrator
 */

#include "CMibFE1PortTable.h"
#include "PairPortFE1.h"
#include "CCommonDefine.h"
#include "UID.h"
#include <string.h>
#include "PortFE1.h"

column_info_T CMibFE1PortTable::colInfo[fe1_port_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_write, CSnmpConstDefine::ucConstInteger32},
        {4, Mib_read_write, CSnmpConstDefine::ucConstOctetString},

};

CMibFE1PortTable::CMibFE1PortTable(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

CMibFE1PortTable::~CMibFE1PortTable() {
    // TODO Auto-generated destructor stub
}

column_info_T* CMibFE1PortTable::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* CMibFE1PortTable::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case fe1_port_index:
        return new CMibFE1PortCol_index(sn, oid, oidLen, this);
    case fe1_port_name:
        return new CMibFE1PortCol_name(sn, oid, oidLen, this);
    case fe1_port_enable:
        return new CMibFE1PortCol_enable(sn, oid, oidLen, this);
    case fe1_port_desc:
        return new CMibFE1PortCol_desc(sn, oid, oidLen, this);
    default:
        return 0;
    }
}
int CMibFE1PortTable::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    PairPortFE1* p = PairPortFE1::getFirstInstance();
    if( p ) {
       index->index[1] = (p->getUID() >> 24) + 1;
       index->index[2]  = p->getUID();
        return 1;
    }
    return -1;
}
int CMibFE1PortTable::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    uint8 slot = (index->index[2] >> 24) & 0xf;
    Resource* pp = 0;
    if( slot < 2 ) {
        pp = PairPortFE1::getNextInstance(index->index[2]);
        if( !pp ) {
            pp = PortFE1::getFirstInstance();
        }

    }
    else {
        pp = PortFE1::getNextInstance(index->index[2]);

    }
    if( pp ) {
        uint32 uid = pp->getUID();
        index->index[1] = (uid >> 24) + 1;
        index->index[2] = uid;
        return 1;
    }
    return -1;
}

int CMibFE1PortCol_index::CallbackGet(const index_info_T& index) {
    uint8 slot = (index.index[2] >> 24) & 0xf;
    if( slot < 2 ) {
        PairPortFE1* e1 = PairPortFE1::getInstance(index.index[2]);
        if( e1 ) {
            return e1->getUID();
        }
    }
    else {
        PortFE1* e1 = PortFE1::getInstance(index.index[2]);
        if( e1 ) {
            return e1->getUID();
        }
    }
    return -1;
}

int CMibFE1PortCol_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    uint8 slot = (index.index[2] >> 24) & 0xf;
    if( slot < 2 ) {
        PairPortFE1* e1 = PairPortFE1::getInstance(index.index[2]);
        if( e1 ) {
            std::string s = e1->getName();
            *len = s.size();
            strcpy((char*)name, s.c_str());
            return 1;
        }
    }
    else {
        PortFE1* e1 = PortFE1::getInstance(index.index[2]);
        if( e1 ) {
            std::string s = e1->getName();
            *len = s.size();
            strcpy((char*)name, s.c_str());
            return 1;
        }
    }
    return -1;
}

int CMibFE1PortCol_enable::CallbackGet(const index_info_T& index) {
    uint8 slot = (index.index[2] >> 24) & 0xf;
    if( slot < 2 ) {
        PairPortFE1* e1 = PairPortFE1::getInstance(index.index[2]);
        if( e1 ) {
            return e1->getPortEnable();
        }
    }
    else {
        PortFE1* e1 = PortFE1::getInstance(index.index[2]);
        if( e1 ) {
            return e1->getPortEnable();
        }
    }
    return -1;
}

int CMibFE1PortCol_enable::callbackSet( const index_info_T& index, uint32 en) {
    uint8 slot = (index.index[2] >> 24) & 0xf;
    if( slot < 2 ) {
        PairPortFE1* e1 = PairPortFE1::getInstance(index.index[2]);
        if( e1 ) {
            if( e1->setPortEnable((uint8)en) ) {
                return 0x5A;
            }
        }
    }
    else {
        PortFE1* e1 = PortFE1::getInstance(index.index[2]);
        if( e1 ) {
            if( e1->setPortEnable((uint8)en) ) {
                return 0x5A;
            }
        }
    }
    return -1;
}

int CMibFE1PortCol_desc::CallbackGet(const index_info_T& index, uint8* desc, uint32* len) {
    uint8 slot = (index.index[2] >> 24) & 0xf;
    if( slot < 2 ) {
        PairPortFE1* e1 = PairPortFE1::getInstance(index.index[2]);
        if( e1 ) {
            char* s = e1->getDescription(len);
            strcpy((char*)desc, s);
            return 1;
        }
    }
    else {
        PortFE1* e1 = PortFE1::getInstance(index.index[2]);
        if( e1 ) {
            char* s = e1->getDescription(len);
            strcpy((char*)desc, s);
            return 1;
        }
    }
    return -1;
}
int CMibFE1PortCol_desc::callbackSet(const index_info_T& index, uint8*desc, uint32 len) {
    uint8 slot = (index.index[2] >> 24) & 0xf;
    if( slot < 2 ) {
        PairPortFE1* e1 = PairPortFE1::getInstance(index.index[2]);
        if( e1 ) {
            if( e1->setDescription((char*)desc, len) ) {
                return 0x5A;
            }
        }
    }
    else {
        PortFE1* e1 = PortFE1::getInstance(index.index[2]);
        if( e1 ) {
            if( e1->setDescription((char*)desc, len) ) {
                return 0x5A;
            }
        }
    }
    return -1;
}
