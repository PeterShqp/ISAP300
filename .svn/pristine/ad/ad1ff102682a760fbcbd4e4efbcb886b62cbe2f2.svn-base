/*
 * CMibHPOverheadTable.h
 *
 *  Created on: 2014-4-12
 *      Author: Administrator
 */

#ifndef CMIBHPOVERHEADTABLE_H_
#define CMIBHPOVERHEADTABLE_H_


#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    hp_oh_J1_Transmit,
    hp_oh_J1_expected,
    hp_oh_J1_Receive,
    hp_oh_C2_Transmit,
    hp_oh_C2_Expected,
    hp_oh_C2_Received,
    hp_oh_B3_Counter,
    hp_oh_j1_TLen,
    hp_oh_j1_RLen,
    hp_oh_size

};


class CMibHPOverheadTable : public CMibTable{
    CMibHPOverheadTable();
public:
    CMibHPOverheadTable(uint32*, uint32, table_info_T*);
    virtual ~CMibHPOverheadTable();

    virtual column_info_T* getColInfo(int sn);
    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[hp_oh_size];
};

class CMibHPOverheadCol_J1Transmit : public CMibTableColumn {
    CMibHPOverheadCol_J1Transmit();
public:
    CMibHPOverheadCol_J1Transmit(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_J1Transmit() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
    virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};


class CMibHPOverheadCol_J1Expected : public CMibTableColumn {
    CMibHPOverheadCol_J1Expected();
public:
    CMibHPOverheadCol_J1Expected(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_J1Expected() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
    virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};


class CMibHPOverheadCol_J1Receive : public CMibTableColumn {
    CMibHPOverheadCol_J1Receive();
public:
    CMibHPOverheadCol_J1Receive(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_J1Receive() {};

    virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};


class CMibHPOverheadCol_C2Transmit : public CMibTableColumn {
    CMibHPOverheadCol_C2Transmit();
public:
    CMibHPOverheadCol_C2Transmit(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_C2Transmit() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibHPOverheadCol_C2Expected : public CMibTableColumn {
    CMibHPOverheadCol_C2Expected();
public:
    CMibHPOverheadCol_C2Expected(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_C2Expected() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibHPOverheadCol_C2Receive : public CMibTableColumn {
    CMibHPOverheadCol_C2Receive();
public:
    CMibHPOverheadCol_C2Receive(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_C2Receive() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibHPOverheadCol_B3 : public CMibTableColumn {
    CMibHPOverheadCol_B3();
public:
    CMibHPOverheadCol_B3(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_B3() {};

    virtual int CallbackGet(const index_info_T& index);
};


class CMibHPOverheadCol_J1TLen : public CMibTableColumn {
    CMibHPOverheadCol_J1TLen();
public:
    CMibHPOverheadCol_J1TLen(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_J1TLen() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibHPOverheadCol_J1RLen : public CMibTableColumn {
    CMibHPOverheadCol_J1RLen();
public:
    CMibHPOverheadCol_J1RLen(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibHPOverheadCol_J1RLen() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBHPOVERHEADTABLE_H_ */
