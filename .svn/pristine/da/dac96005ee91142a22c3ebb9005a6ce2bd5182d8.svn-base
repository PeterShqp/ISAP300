/*
 * TableAlarmPropertyTemplateOperation.h
 *
 *  Created on: 2014Äê8ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef TABLEALARMPROPERTYTEMPLATEOPERATION_H_
#define TABLEALARMPROPERTYTEMPLATEOPERATION_H_

#include "CMibTable.h"
#include "CMibTableColumn.h"

enum {
    template_new,
    template_operation_columns
};

class TableAlarmPropertyTemplateOperation : public CMibTable {
    TableAlarmPropertyTemplateOperation();
public:
    TableAlarmPropertyTemplateOperation(uint32*, uint32, table_info_T*);
    virtual ~TableAlarmPropertyTemplateOperation();

    virtual column_info_T* getColInfo(int sn);

    virtual CMibNodeObject* MakeColumn(int sn, uint32* oid, uint32 oidLen);
    virtual int getFirstIndex(index_info_T*);
    virtual int getNextIndex(index_info_T*);
private:
    static column_info_T colInfo[template_operation_columns];
};


class TableAlarmPropertyTemplateOperation_new : public CMibTableColumn {
    TableAlarmPropertyTemplateOperation_new();
public:
    TableAlarmPropertyTemplateOperation_new(int sn, uint32* oid, uint32 oidLen, CMibTable* table)
                : CMibTableColumn(sn, oid, oidLen, table) {

    };
    virtual ~TableAlarmPropertyTemplateOperation_new() {};

    virtual int callbackSet( const index_info_T& index, uint32 );
};

#endif /* TABLEALARMPROPERTYTEMPLATEOPERATION_H_ */
