/*
 * GroupAlarmProperty.cpp
 *
 *  Created on: 2014Äê8ÔÂ27ÈÕ
 *      Author: Administrator
 */

#include "GroupAlarmProperty.h"
#include "TableAlarmPropertyConfig.h"
#include "TableAlarmPropertyTemplateOperation.h"
#include "TableAlarmPropertyTemplateConfig.h"

table_info_T GroupAlarmProperty::tableInfo[table_almproperty_size] = {
        {1, table_alm_ppt_config_columns, 4},//sn, col number, index number
        {2, template_operation_columns, 1},
        {3, table_template_config_columns, 2}
};

GroupAlarmProperty::~GroupAlarmProperty() {
    // TODO Auto-generated destructor stub
}


GroupAlarmProperty::GroupAlarmProperty(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
    creatTables(tableInfo, table_almproperty_size);
}

CMibEntry* GroupAlarmProperty::MakeTable(int sn, uint32* oid, uint32 oidLen) {
    switch( sn ) {
    case table_alarm_property_config:
        return new TableAlarmPropertyConfig(oid, oidLen, &tableInfo[sn]);
    case table_alarm_property_template_operation:
        return new TableAlarmPropertyTemplateOperation(oid, oidLen, &tableInfo[sn]);
    case table_alarm_property_template_config:
        return new TableAlarmPropertyTemplateConfig(oid, oidLen, &tableInfo[sn]);
    default:
        return 0;
    }
}
