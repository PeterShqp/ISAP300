/*
 * TableClockSourceOption.h
 *
 *  Created on: 2014-1-16
 *      Author: Administrator
 */

#ifndef TABLECLOCKSOURCEOPTION_H_
#define TABLECLOCKSOURCEOPTION_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    back_clk_num,
    cur_clk,
    assign_clk,
    clk_option_size
};


class TableClockSourceOption : public CMibTable {
    TableClockSourceOption();
public:
    TableClockSourceOption(uint32*, uint32, table_info_T*);
    virtual ~TableClockSourceOption();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[clk_option_size];
};


class CMibclkoption_number : public CMibTableColumn {
    CMibclkoption_number();
public:
    CMibclkoption_number(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibclkoption_number() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibclkoption_curclk : public CMibTableColumn {
    CMibclkoption_curclk();
public:
    CMibclkoption_curclk(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibclkoption_curclk() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibclkoption_assign : public CMibTableColumn {
    CMibclkoption_assign();
public:
    CMibclkoption_assign(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibclkoption_assign() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* TABLECLOCKSOURCEOPTION_H_ */
