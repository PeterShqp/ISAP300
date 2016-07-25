/*
 * CMibChvcTable.h
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#ifndef CMIBCHVCTABLE_H_
#define CMIBCHVCTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
    chvc_index,
    chvc_name,
    chvc_upstream,
    chvc_downstream,
    chvc_protect_partner,
    chvc_sncp,
    chvc_size

}Mib_CHVC_Column_E;


class CMibChvcTable : public CMibTable {
    CMibChvcTable();
public:
    CMibChvcTable(uint32*, uint32, table_info_T*);
    virtual ~CMibChvcTable();
    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[chvc_size];
};

class CMibCHVCCol_index : public CMibTableColumn {
    CMibCHVCCol_index();
public:
    CMibCHVCCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibCHVCCol_index() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibCHVCCol_name : public CMibTableColumn {
    CMibCHVCCol_name();
public:
    CMibCHVCCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibCHVCCol_name() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibCHVCCol_up : public CMibTableColumn {
    CMibCHVCCol_up();
public:
    CMibCHVCCol_up(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibCHVCCol_up() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibCHVCCol_down : public CMibTableColumn {
    CMibCHVCCol_down();
public:
    CMibCHVCCol_down(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibCHVCCol_down() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibCHVCCol_protect : public CMibTableColumn {
    CMibCHVCCol_protect();
public:
    CMibCHVCCol_protect(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibCHVCCol_protect() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibCHVCCol_sncp : public CMibTableColumn {
    CMibCHVCCol_sncp();
public:
    CMibCHVCCol_sncp(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibCHVCCol_sncp() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBCHVCTABLE_H_ */
