/*
 * CMibSltchTable.h
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#ifndef CMIBSLTCHTABLE_H_
#define CMIBSLTCHTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    sltch_index,
    sltch_name,
    sltch_upstream,
    sltch_downstream,
    sltch_size

}Mib_sltch_Column_E;


class CMibSltchTable : public CMibTable {
    CMibSltchTable();
public:
    CMibSltchTable(uint32*, uint32, table_info_T*);
    virtual ~CMibSltchTable();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[sltch_size];
};

class CMibSlot155ChannelCol_index : public CMibTableColumn {
    CMibSlot155ChannelCol_index();
public:
    CMibSlot155ChannelCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSlot155ChannelCol_index() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSlot155ChannelCol_name : public CMibTableColumn {
    CMibSlot155ChannelCol_name();
public:
    CMibSlot155ChannelCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibSlot155ChannelCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibSlot155ChannelCol_up : public CMibTableColumn {
    CMibSlot155ChannelCol_up();
public:
    CMibSlot155ChannelCol_up(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibSlot155ChannelCol_up() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSlot155ChannelCol_down : public CMibTableColumn {
    CMibSlot155ChannelCol_down();
public:
    CMibSlot155ChannelCol_down(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibSlot155ChannelCol_down() {};

    virtual int CallbackGet(const index_info_T& index);
};



#endif /* CMIBSLTCHTABLE_H_ */
