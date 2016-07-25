/*
 * PcmUseableClockSourceTable.h
 *
 *  Created on: 2015Äê2ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef PCMUSEABLECLOCKSOURCETABLE_H_
#define PCMUSEABLECLOCKSOURCETABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    pcm_useable_clk_index,
    pcm_clk_name,
    pcm_clk_status,
    pcm_usable_clk_size
};


class PcmUseableClockSourceTable : public CMibTable {
    PcmUseableClockSourceTable();
public:
    PcmUseableClockSourceTable(uint32*, uint32, table_info_T*);
    virtual ~PcmUseableClockSourceTable();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[pcm_usable_clk_size];
};


class CMibPcmUsealbeClk_index : public CMibTableColumn {
    CMibPcmUsealbeClk_index();
public:
    CMibPcmUsealbeClk_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmUsealbeClk_index() {};

    virtual int CallbackGet(const index_info_T& index);
};


class CMibPcmUsealbeClk_name : public CMibTableColumn {
    CMibPcmUsealbeClk_name();
public:
    CMibPcmUsealbeClk_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmUsealbeClk_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibPcmUsealbeClk_status : public CMibTableColumn {
    CMibPcmUsealbeClk_status();
public:
    CMibPcmUsealbeClk_status(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibPcmUsealbeClk_status() {};

    virtual int CallbackGet(const index_info_T& index);
};

#endif /* PCMUSEABLECLOCKSOURCETABLE_H_ */
