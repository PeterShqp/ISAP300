/*
 * CMibSDHChannelTable.h
 *
 *  Created on: 2013-12-3
 *      Author: Administrator
 */

#ifndef CMIBSDHCHANNELTABLE_H_
#define CMIBSDHCHANNELTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    sdh_ch_index,
    sdh_ch_down_id,
    sdh_ch_up_id,
    sdh_ch_name,
    sdh_ch_size

}Mib_SDH_Channel_Column_E;

class CMibSDHChannelTable : public CMibTable {
    CMibSDHChannelTable();
public:
    CMibSDHChannelTable(uint32*, uint32, table_info_T*);
    virtual ~CMibSDHChannelTable();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[sdh_ch_size];
};


class CMibSDHchCol_uid : public CMibTableColumn {
    CMibSDHchCol_uid();
public:
    CMibSDHchCol_uid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibSDHchCol_uid() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSDHchCol_up : public CMibTableColumn {
    CMibSDHchCol_up();
public:
    CMibSDHchCol_up(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSDHchCol_up() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSDHchCol_down : public CMibTableColumn {
    CMibSDHchCol_down();
public:
    CMibSDHchCol_down(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSDHchCol_down() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSDHchCol_name : public CMibTableColumn {
    CMibSDHchCol_name();
public:
    CMibSDHchCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSDHchCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

#endif /* CMIBSDHCHANNELTABLE_H_ */
