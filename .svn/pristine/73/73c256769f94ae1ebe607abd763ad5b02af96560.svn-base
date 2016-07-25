/*
 * CMibSTMOverheadTable.h
 *
 *  Created on: 2013-4-19
 *      Author: Administrator
 */

#ifndef CMIBSTMOVERHEADTABLE_H_
#define CMIBSTMOVERHEADTABLE_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	stm_oh_J0_Transmit,
	stm_oh_J0_expected,
	stm_oh_J0_Receive,
	stm_oh_B1_counter,
	stm_oh_B2_counter,
	stm_oh_j0_TLen,
	stm_oh_j0_RLen,
	stm_oh_size

}Mib_STM_overhead_Column_E;


class CMibSTMOverheadTable : public CMibTable{
	CMibSTMOverheadTable();
public:
	CMibSTMOverheadTable(uint32*, uint32, table_info_T*);
	virtual ~CMibSTMOverheadTable();

	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[stm_oh_size];
};

class CMibSTMOverheadCol_J0Transmit : public CMibTableColumn {
	CMibSTMOverheadCol_J0Transmit();
public:
	CMibSTMOverheadCol_J0Transmit(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMOverheadCol_J0Transmit() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};


class CMibSTMOverheadCol_J0Expected : public CMibTableColumn {
	CMibSTMOverheadCol_J0Expected();
public:
	CMibSTMOverheadCol_J0Expected(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMOverheadCol_J0Expected() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet(const index_info_T& index, uint8*, uint32 len);
};


class CMibSTMOverheadCol_J0Receive : public CMibTableColumn {
	CMibSTMOverheadCol_J0Receive();
public:
	CMibSTMOverheadCol_J0Receive(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
			: CMibTableColumn(sn, oid, oidLen, table) {};
	virtual ~CMibSTMOverheadCol_J0Receive() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class CMibSTMOverheadCol_B1 : public CMibTableColumn {
    CMibSTMOverheadCol_B1();
public:
    CMibSTMOverheadCol_B1(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSTMOverheadCol_B1() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSTMOverheadCol_B2 : public CMibTableColumn {
    CMibSTMOverheadCol_B2();
public:
    CMibSTMOverheadCol_B2(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSTMOverheadCol_B2() {};

    virtual int CallbackGet(const index_info_T& index);
};

class CMibSTMOverheadCol_J0TLen : public CMibTableColumn {
    CMibSTMOverheadCol_J0TLen();
public:
    CMibSTMOverheadCol_J0TLen(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSTMOverheadCol_J0TLen() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

class CMibSTMOverheadCol_J0RLen : public CMibTableColumn {
    CMibSTMOverheadCol_J0RLen();
public:
    CMibSTMOverheadCol_J0RLen(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
            : CMibTableColumn(sn, oid, oidLen, table) {};
    virtual ~CMibSTMOverheadCol_J0RLen() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBSTMOVERHEADTABLE_H_ */
