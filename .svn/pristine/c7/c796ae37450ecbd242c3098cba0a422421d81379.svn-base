/*
 * CMibHPTable.h
 *
 *  Created on: 2013-12-4
 *      Author: Administrator
 */

#ifndef CMIBHPTABLE_H_
#define CMIBHPTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    hp_bus_index,
    hp_bus_name,
    hp_bus_map_from,
    hp_bus_size

}Mib_HP_BUS_Column_E;

class CMibHPTable : public CMibTable {
    CMibHPTable();
public:
    CMibHPTable(uint32*, uint32, table_info_T*);
    virtual ~CMibHPTable();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[hp_bus_size];
};


class CMibHPBusCol_uid : public CMibTableColumn {
    CMibHPBusCol_uid();
public:
    CMibHPBusCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibHPBusCol_uid() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibHPBusCol_name : public CMibTableColumn {
    CMibHPBusCol_name();
public:
    CMibHPBusCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPBusCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibHPBusCol_mapFrom : public CMibTableColumn {
    CMibHPBusCol_mapFrom();
public:
    CMibHPBusCol_mapFrom(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPBusCol_mapFrom() {};

    virtual int CallbackGet(const index_info_T& index);
};

#endif /* CMIBHPTABLE_H_ */
