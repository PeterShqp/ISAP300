/*
 * CMibCrossResource.h
 *
 *  Created on: 2013-12-3
 *      Author: Administrator
 */

#ifndef CMIBCROSSRESOURCE_H_
#define CMIBCROSSRESOURCE_H_


#include "CMibGroup.h"

typedef enum {
//  table_stm_alarm_property,
    table_SDH_bus,
    table_SDH_channel,
    table_SltCH,
    table_SDH_size
}Mib_SDH_Table_E;

class CMibCrossResource : public CMibGroup {
    CMibCrossResource();
public:
    CMibCrossResource(uint32* oid, uint8 oidlen);
    virtual ~CMibCrossResource();

//  virtual table_info_T* getTableInfo(int sn);
    virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
    static table_info_T tableInfo[table_SDH_size];
};

#endif /* CMIBCROSSRESOURCE_H_ */
