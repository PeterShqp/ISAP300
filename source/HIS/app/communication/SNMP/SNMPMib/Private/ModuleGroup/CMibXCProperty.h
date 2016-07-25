/*
 * CMibXCProperty.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBXCPROPERTY_H_
#define CMIBXCPROPERTY_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

typedef enum {
	xc_index,
	xc_src_id,
	xc_dest_id,
	xc_name,
	xc_description,
	xc_delete,
//	xc_sncp,
	xc_property_size

}Mib_XC_Property_Column_E;


class CMibXCProperty : public CMibTable {
	CMibXCProperty();
public:
	CMibXCProperty(uint32*, uint32, table_info_T*);
	virtual ~CMibXCProperty();
	virtual column_info_T* getColInfo(int sn);
	virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
	virtual int getFirstIndex(index_info_T*);
	virtual int getNextIndex(index_info_T*);
private:
	static column_info_T colInfo[xc_property_size];
};


class CMibXCPropertyCol_index : public CMibTableColumn {
	CMibXCPropertyCol_index();
public:
	CMibXCPropertyCol_index(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_index() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXCPropertyCol_srcid : public CMibTableColumn {
    CMibXCPropertyCol_srcid();
public:
    CMibXCPropertyCol_srcid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_srcid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXCPropertyCol_destid : public CMibTableColumn {
    CMibXCPropertyCol_destid();
public:
    CMibXCPropertyCol_destid(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_destid() {};

	virtual int CallbackGet(const index_info_T& index);
};

class CMibXCPropertyCol_name : public CMibTableColumn {
	CMibXCPropertyCol_name();
public:
	CMibXCPropertyCol_name(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_name() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibXCPropertyCol_desc : public CMibTableColumn {
	CMibXCPropertyCol_desc();
public:
	CMibXCPropertyCol_desc(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_desc() {};

	virtual int CallbackGet(const index_info_T& index, uint8*, uint32* len);
	virtual int callbackSet( const index_info_T& index, uint8*, uint32 len);
};

class CMibXCPropertyCol_delete : public CMibTableColumn {
	CMibXCPropertyCol_delete();
public:
	CMibXCPropertyCol_delete(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
				: CMibTableColumn(sn, oid, oidLen, table) {

	};
	virtual ~CMibXCPropertyCol_delete() {};

	virtual int callbackSet( const index_info_T& index, uint32 );
};


class CMibXCPropertyCol_sncp : public CMibTableColumn {
    CMibXCPropertyCol_sncp();
public:
    CMibXCPropertyCol_sncp(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~CMibXCPropertyCol_sncp() {};

    virtual int CallbackGet(const index_info_T& index);
    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* CMIBXCPROPERTY_H_ */
