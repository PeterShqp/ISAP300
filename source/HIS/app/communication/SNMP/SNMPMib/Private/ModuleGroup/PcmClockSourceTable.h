/*
 * PcmClockSourceTable.h
 *
 *  Created on: 2015Äê2ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef PCMCLOCKSOURCETABLE_H_
#define PCMCLOCKSOURCETABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    pcm_clk_pri,
    pcm_clk_index,
    pcm_clk_size
};


class PcmClockSourceTable : public CMibTable {
    PcmClockSourceTable();
public:
    PcmClockSourceTable(uint32*, uint32, table_info_T*);
    virtual ~PcmClockSourceTable();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[pcm_clk_size];
};


class CMibPcmClk_pri : public CMibTableColumn {
    CMibPcmClk_pri();
public:
    CMibPcmClk_pri(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmClk_pri() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibPcmClk_index : public CMibTableColumn {
    CMibPcmClk_index();
public:
    CMibPcmClk_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmClk_index() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* PCMCLOCKSOURCETABLE_H_ */
