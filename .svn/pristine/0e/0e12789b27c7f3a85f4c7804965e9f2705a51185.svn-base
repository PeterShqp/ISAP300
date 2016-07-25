/*
 * TableSlot.h
 *
 *  Created on: 2013-7-10
 *      Author: Administrator
 */

#ifndef TABLESLOT_H_
#define TABLESLOT_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"
/*
 *
 */
enum {
	slot_index,
	card_name,
	card_typeID,
	card_desc,
	card_status,
	card_working,
	card_versioninfo,
	card_reset,
	table_slot_columns
};

class TableSlot : public CMibTable {
	TableSlot();
public:
	TableSlot(uint32*, uint32, table_info_T*);
	virtual ~TableSlot();

	virtual column_info_T* getColInfo(int sn);

	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[table_slot_columns];
};


class TableSlotCol_index : public CMibTableColumn {
	TableSlotCol_index();
public:
	TableSlotCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableSlotCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class TableSlotCol_name : public CMibTableColumn {
	TableSlotCol_name();
public:
	TableSlotCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableSlotCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableSlotCol_typeID : public CMibTableColumn {
	TableSlotCol_typeID();
public:
	TableSlotCol_typeID(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableSlotCol_typeID() {};

	virtual int CallbackGet(const index_info_T& index);
};


class TableSlotCol_desc : public CMibTableColumn {
	TableSlotCol_desc();
public:
	TableSlotCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableSlotCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
};

class TableSlotCol_status : public CMibTableColumn {
	TableSlotCol_status();
public:
	TableSlotCol_status(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableSlotCol_status() {};

	virtual int CallbackGet(const index_info_T& index);
};

class TableSlotCol_working : public CMibTableColumn {
    TableSlotCol_working();
public:
    TableSlotCol_working(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableSlotCol_working() {};

    virtual int CallbackGet(const index_info_T& index);
};

class TableSlotCol_verinfo : public CMibTableColumn {
	TableSlotCol_verinfo();
public:
	TableSlotCol_verinfo(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableSlotCol_verinfo() {};

	virtual int CallbackGet(const index_info_T& index,uint8*, uint32* len);
};

class TableSlotCol_reset : public CMibTableColumn {
	TableSlotCol_reset();
public:
	TableSlotCol_reset(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~TableSlotCol_reset() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};
#endif /* TABLESLOT_H_ */
