/*
 * CMibSDHBusTable.h
 *
 *  Created on: 2013-12-3
 *      Author: Administrator
 */

#ifndef CMIBSDHBUSTABLE_H_
#define CMIBSDHBUSTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    sdh_bus_index,
    sdh_bus_name,
    sdh_bus_map_from,
    sdh_bus_size

}Mib_SDH_BUS_Column_E;

class CMibSDHBusTable : public CMibTable {
    CMibSDHBusTable();
public:
    CMibSDHBusTable(uint32*, uint32, table_info_T*);
    virtual ~CMibSDHBusTable();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[sdh_bus_size];
};


class CMibSDHBusCol_uid : public CMibTableColumn {
    CMibSDHBusCol_uid();
public:
    CMibSDHBusCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibSDHBusCol_uid() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSDHBusCol_name : public CMibTableColumn {
    CMibSDHBusCol_name();
public:
    CMibSDHBusCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSDHBusCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibSDHBusCol_mapFrom : public CMibTableColumn {
    CMibSDHBusCol_mapFrom();
public:
    CMibSDHBusCol_mapFrom(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSDHBusCol_mapFrom() {};

    virtual int CallbackGet(const index_info_T& index);
};

#endif /* CMIBSDHBUSTABLE_H_ */
