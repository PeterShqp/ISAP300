/*
 * TableDeviceFiles.h
 *
 *  Created on: 2015年12月11日
 *      Author: Administrator
 */

#ifndef TABLEDEVICEFILES_H_
#define TABLEDEVICEFILES_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    file_sn,
    file_name,
    file_bytes,
    file_size
};


class TableDeviceFiles : public CMibTable {
    TableDeviceFiles();
public:
    TableDeviceFiles(uint32*, uint32, table_info_T*);
    virtual ~TableDeviceFiles();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[file_size];
};

class TableDeviceFiles_index : public CMibTableColumn {
    TableDeviceFiles_index();
public:
    TableDeviceFiles_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceFiles_index() {};

    virtual int CallbackGet(const index_info_T& index);
};


class TableDeviceFiles_name : public CMibTableColumn {
    TableDeviceFiles_name();
public:
    TableDeviceFiles_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceFiles_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableDeviceFiles_size : public CMibTableColumn {
    TableDeviceFiles_size();
public:
    TableDeviceFiles_size(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableDeviceFiles_size() {};

    virtual int CallbackGet(const index_info_T& index);
};


#endif /* TABLEDEVICEFILES_H_ */
