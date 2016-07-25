/*
 * TableDeviceClockSource.h
 *
 *  Created on: 2014-1-16
 *      Author: Administrator
 */

#ifndef TABLEDEVICECLOCKSOURCE_H_
#define TABLEDEVICECLOCKSOURCE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    dev_clk_pri,
    dev_clk_index,
    dev_clk_size
};


class TableDeviceClockSource : public CMibTable {
    TableDeviceClockSource();
public:
    TableDeviceClockSource(uint32*, uint32, table_info_T*);
    virtual ~TableDeviceClockSource();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[dev_clk_size];
};


class CMibDevClk_pri : public CMibTableColumn {
    CMibDevClk_pri();
public:
    CMibDevClk_pri(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibDevClk_pri() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibDevClk_index : public CMibTableColumn {
    CMibDevClk_index();
public:
    CMibDevClk_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibDevClk_index() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* TABLEDEVICECLOCKSOURCE_H_ */
