/*
 * TableUseableClockSource.h
 *
 *  Created on: 2014-1-13
 *      Author: Administrator
 */

#ifndef TABLEUSEABLECLOCKSOURCE_H_
#define TABLEUSEABLECLOCKSOURCE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    clk_index,
    clk_name,
    clk_status,
    usable_clk_size
};


class TableUseableClockSource : public CMibTable {
    TableUseableClockSource();
public:
    TableUseableClockSource(uint32*, uint32, table_info_T*);
    virtual ~TableUseableClockSource();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[usable_clk_size];
};


class CMibUsealbeClk_index : public CMibTableColumn {
    CMibUsealbeClk_index();
public:
    CMibUsealbeClk_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibUsealbeClk_index() {};

    virtual int CallbackGet(const index_info_T& index);
};


class CMibUsealbeClk_name : public CMibTableColumn {
    CMibUsealbeClk_name();
public:
    CMibUsealbeClk_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibUsealbeClk_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibUsealbeClk_status : public CMibTableColumn {
    CMibUsealbeClk_status();
public:
    CMibUsealbeClk_status(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibUsealbeClk_status() {};

    virtual int CallbackGet(const index_info_T& index);
};

#endif /* TABLEUSEABLECLOCKSOURCE_H_ */
