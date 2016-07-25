/*
 * CMibFE1PortTable.h
 *
 *  Created on: 2015年7月4日
 *      Author: Administrator
 */

#ifndef CMIBFE1PORTTABLE_H_
#define CMIBFE1PORTTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    fe1_port_index,
    fe1_port_name,
    fe1_port_enable,
    fe1_port_desc,
    fe1_port_size

}Mib_FE1_Port_Column_E;


class CMibFE1PortTable : public CMibTable {
    CMibFE1PortTable();
public:
    CMibFE1PortTable(uint32*, uint32, table_info_T*);
    virtual ~CMibFE1PortTable();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[fe1_port_size];
};

class CMibFE1PortCol_index : public CMibTableColumn {
    CMibFE1PortCol_index();
public:
    CMibFE1PortCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibFE1PortCol_index() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibFE1PortCol_name : public CMibTableColumn {
    CMibFE1PortCol_name();
public:
    CMibFE1PortCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibFE1PortCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibFE1PortCol_enable : public CMibTableColumn {
    CMibFE1PortCol_enable();
public:
    CMibFE1PortCol_enable(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibFE1PortCol_enable() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibFE1PortCol_desc : public CMibTableColumn {
    CMibFE1PortCol_desc();
public:
    CMibFE1PortCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibFE1PortCol_desc() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
    virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};
#endif /* CMIBFE1PORTTABLE_H_ */
