/*
 * CMibCrossResource.cpp
 *
 *  Created on: 2013-12-3
 *      Author: Administrator
 */

#include "CMibCrossResource.h"
#include "CMibSDHBusTable.h"
#include "CMibSDHChannelTable.h"
#include "CMibSltchTable.h"

table_info_T CMibCrossResource::tableInfo[] = {
//      {3, stm_Alarm_size, 4},
        {1, sdh_bus_size, 3}, //sn, col number, index number
        {2, sdh_ch_size, 3},
        {3, sltch_size, 3},
};

CMibCrossResource::~CMibCrossResource() {
    // TODO Auto-generated destructor stub
}

//CMibCrossResource::CMibCrossResource(uint8* oid, uint8 oidlen) : CMibEntry( oid, oidlen){
//
//}

CMibCrossResource::CMibCrossResource(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
    creatTables(tableInfo, table_SDH_size);
}

//table_info_T* CMibCrossResource::getTableInfo(int sn) {
//  return &tableInfo[sn];
//}

CMibEntry* CMibCrossResource::MakeTable(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
//  case table_stm_alarm_property:
//      return new CMibCrossResourceAlarmProperty(oid, oidLen, &tableInfo[sn]);
    case table_SDH_bus: {
        return new CMibSDHBusTable(oid, oidLen, &tableInfo[sn]);
    }
    case table_SDH_channel:
        return new CMibSDHChannelTable(oid, oidLen, &tableInfo[sn]);
    case table_SltCH:
        return new CMibSltchTable(oid, oidLen, &tableInfo[sn]);
    default:
        return 0;
    }
}
