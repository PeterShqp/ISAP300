/*
 * PcmClockOptionTable.h
 *
 *  Created on: 2015Äê2ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef PCMCLOCKOPTIONTABLE_H_
#define PCMCLOCKOPTIONTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    pcm_back_clk_num,
    pcm_cur_clk,
    pcm_assign_clk,
    pcm_clk_option_size
};


class PcmClockOptionTable : public CMibTable {
    PcmClockOptionTable();
public:
    PcmClockOptionTable(uint32*, uint32, table_info_T*);
    virtual ~PcmClockOptionTable();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[pcm_clk_option_size];
};


class CMibPcmclkoption_number : public CMibTableColumn {
    CMibPcmclkoption_number();
public:
    CMibPcmclkoption_number(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmclkoption_number() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibPcmclkoption_curclk : public CMibTableColumn {
    CMibPcmclkoption_curclk();
public:
    CMibPcmclkoption_curclk(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmclkoption_curclk() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibPcmclkoption_assign : public CMibTableColumn {
    CMibPcmclkoption_assign();
public:
    CMibPcmclkoption_assign(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmclkoption_assign() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* PCMCLOCKOPTIONTABLE_H_ */
