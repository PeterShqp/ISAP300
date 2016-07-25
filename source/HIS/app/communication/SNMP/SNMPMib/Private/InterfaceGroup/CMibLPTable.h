/*
 * CMibLPTable.h
 *
 *  Created on: 2013-12-4
 *      Author: Administrator
 */

#ifndef CMIBLPTABLE_H_
#define CMIBLPTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    lp_bus_index,
    lp_bus_name,
    lp_bus_map_from,
    lp_bus_size

}Mib_LP_BUS_Column_E;

class CMibLPTable : public CMibTable {
    CMibLPTable();
public:
    CMibLPTable(uint32*, uint32, table_info_T*);
    virtual ~CMibLPTable();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[lp_bus_size];
};


class CMibLPBusCol_uid : public CMibTableColumn {
    CMibLPBusCol_uid();
public:
    CMibLPBusCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibLPBusCol_uid() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibLPBusCol_name : public CMibTableColumn {
    CMibLPBusCol_name();
public:
    CMibLPBusCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibLPBusCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibLPBusCol_mapFrom : public CMibTableColumn {
    CMibLPBusCol_mapFrom();
public:
    CMibLPBusCol_mapFrom(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibLPBusCol_mapFrom() {};

    virtual int CallbackGet(const index_info_T& index);
};
#endif /* CMIBLPTABLE_H_ */
