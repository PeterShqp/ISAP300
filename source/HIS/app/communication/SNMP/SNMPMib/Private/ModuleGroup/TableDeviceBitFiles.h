/*
 * TableDeviceBitFiles.h
 *
 *  Created on: 2016年6月16日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMMUNICATION_SNMP_SNMPMIB_PRIVATE_MODULEGROUP_TABLEDEVICEBITFILES_H_
#define SOURCE_HIS_APP_COMMUNICATION_SNMP_SNMPMIB_PRIVATE_MODULEGROUP_TABLEDEVICEBITFILES_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    bfile_sn,
    bfile_name,
    bfile_bytes,
    bfile_crcsta,
    bfile_cmp,
    bfile_sync2B,
    bfile_syncP,
    bfile_size
};


class TableDeviceBitFiles : public CMibTable {
    TableDeviceBitFiles();
public:
    TableDeviceBitFiles(uint32*, uint32, table_info_T*);
    virtual ~TableDeviceBitFiles();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[bfile_size];
};

class TableDeviceBitFiles_index : public CMibTableColumn {
    TableDeviceBitFiles_index();
public:
    TableDeviceBitFiles_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceBitFiles_index() {};

    virtual int CallbackGet(const index_info_T& index);
};


class TableDeviceBitFiles_name : public CMibTableColumn {
    TableDeviceBitFiles_name();
public:
    TableDeviceBitFiles_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceBitFiles_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableDeviceBitFiles_size : public CMibTableColumn {
    TableDeviceBitFiles_size();
public:
    TableDeviceBitFiles_size(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceBitFiles_size() {};

    virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceBitFiles_crcsta : public CMibTableColumn {
    TableDeviceBitFiles_crcsta();
public:
    TableDeviceBitFiles_crcsta(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceBitFiles_crcsta() {};

    virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceBitFiles_cmp : public CMibTableColumn {
    TableDeviceBitFiles_cmp();
public:
    TableDeviceBitFiles_cmp(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceBitFiles_cmp() {};

    virtual int CallbackGet(const index_info_T& index);
};

class TableDeviceBitFiles_sync2b : public CMibTableColumn {
    TableDeviceBitFiles_sync2b();
public:
    TableDeviceBitFiles_sync2b(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceBitFiles_sync2b() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

class TableDeviceBitFiles_syncp : public CMibTableColumn {
    TableDeviceBitFiles_syncp();
public:
    TableDeviceBitFiles_syncp(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceBitFiles_syncp() {};

    virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};


#endif /* SOURCE_HIS_APP_COMMUNICATION_SNMP_SNMPMIB_PRIVATE_MODULEGROUP_TABLEDEVICEBITFILES_H_ */
