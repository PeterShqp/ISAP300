/*
 * GroupAlarmProperty.h
 *
 *  Created on: 2014Äê8ÔÂ27ÈÕ
 *      Author: Administrator
 */

#ifndef GROUPALARMPROPERTY_H_
#define GROUPALARMPROPERTY_H_

#include "CMibGroup.h"

enum {
    table_alarm_property_config,
    table_alarm_property_template_operation,
    table_alarm_property_template_config,
    table_almproperty_size
};

class GroupAlarmProperty : public CMibGroup {
    GroupAlarmProperty();
public:
    GroupAlarmProperty(uint32* oid, uint8 oidlen);
    virtual ~GroupAlarmProperty();

//  virtual table_info_T* getTableInfo(int sn);
    virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
    static table_info_T tableInfo[table_almproperty_size];
};

#endif /* GROUPALARMPROPERTY_H_ */
