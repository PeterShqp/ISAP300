/*
 * TableDeviceFiles.cpp
 *
 *  Created on: 2015年12月11日
 *      Author: Administrator
 */

#include "TableDeviceFiles.h"
#include "CCommonDefine.h"
#include "os.h"
#include <string.h>

column_info_T TableDeviceFiles::colInfo[file_size] = {
        {1, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
        {2, Mib_read_only, CSnmpConstDefine::ucConstOctetString},
        {3, Mib_read_only, CSnmpConstDefine::ucConstInteger32},
};


TableDeviceFiles::TableDeviceFiles(uint32* oid, uint32 oidLen, table_info_T* tInfo) : CMibTable(oid, oidLen, tInfo) {
    makeColumnOid();
}

TableDeviceFiles::~TableDeviceFiles() {
    // TODO Auto-generated destructor stub
}

column_info_T* TableDeviceFiles::getColInfo(int sn) {
    return &colInfo[sn];
}

CMibNodeObject* TableDeviceFiles::MakeColumn(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case file_sn:
        return new TableDeviceFiles_index(sn, oid, oidLen, this);
    case file_name:
        return new TableDeviceFiles_name(sn, oid, oidLen, this);
    case file_bytes:
        return new TableDeviceFiles_size(sn, oid, oidLen, this);
    default:
        return 0;
    }
}

int TableDeviceFiles::getFirstIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    FINFO info;
    info.fileID  = 0;
    char* mask = "*.cfg";
    if( ffind (mask,&info) == 0 ) {
     index->index[1] = info.fileID;
     return 1;
    }
    return -1;
}

int TableDeviceFiles::getNextIndex(index_info_T* index) {
    index->index_number = getTableInfo()->table_index_num;
    index->index[0] = CCommonDefine::uiConstDeviceIndex;
    FINFO info;
    info.fileID  = 0;
    char* mask = "*.cfg";
    while( ffind (mask,&info) == 0 ) {
        if( index->index[1] == info.fileID ) {
            if( ffind (mask,&info) == 0 ) {
                index->index[1] = info.fileID;
                return 1;
            }
        }
    }
    return -1;
}

int TableDeviceFiles_index::CallbackGet(const index_info_T& index) {
    return index.index[1];
}

int TableDeviceFiles_name::CallbackGet(const index_info_T& index, uint8* name, uint32* len) {
    FINFO info;
    info.fileID  = 0;
    char* mask = "*.cfg";
    while( ffind (mask,&info) == 0 ) {
        if( index.index[1] == info.fileID ) {
            *len = strlen((char*)info.name);
            strcpy((char*)name, (char*)info.name);
            return 1;
        }
    }
    return -1;
}

int TableDeviceFiles_size::CallbackGet(const index_info_T& index) {
    FINFO info;
    info.fileID  = 0;
    char* mask = "*.cfg";
    while( ffind (mask,&info) == 0 ) {
        if( index.index[1] == info.fileID ) {
            return info.size;
        }
    }
    return -1;

}
