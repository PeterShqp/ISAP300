/*
 * CMibAlarm.cpp
 *
 *  Created on: 2014年8月27日
 *      Author: Administrator
 */

#include "CMibAlarm.h"
#include "GroupAlarmProperty.h"
#include "GroupAlarmRecord.h"

CMibAlarm::CMibAlarm() {
    // TODO Auto-generated constructor stub

}

CMibAlarm::~CMibAlarm() {
    // TODO Auto-generated destructor stub
}

uint32 CMibAlarm::InitialGroup(void) {
    //初始化
    uint32 uiInOID[] = {1,3,6,1,4,1,25449,1,1,4,0};
    uint32 TableIndex = 10;
    CSnmpVariable objMib(uiInOID,10);
    InitialNode(&objMib);

    //告警属性组
    uiInOID[TableIndex] = 1;
    GroupAlarmProperty* objpProperty = new GroupAlarmProperty(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
    InsertDownLinkNode(objpProperty);

    //告警记录组
    uiInOID[TableIndex] = 2;
    GroupAlarmRecord* objpRecord = new GroupAlarmRecord(uiInOID, sizeof(uiInOID)/sizeof(uiInOID[0]));
    InsertDownLinkNode(objpRecord);
	return 0;
}
