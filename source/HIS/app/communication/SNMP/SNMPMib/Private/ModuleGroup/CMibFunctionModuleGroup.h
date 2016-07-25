/*
 * CMibFunctionModuleGroup.h
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#ifndef CMIBFUNCTIONMODULEGROUP_H_
#define CMIBFUNCTIONMODULEGROUP_H_

#include "CMibGroup.h"

typedef enum {
	table_cross_option,
	table_cross_property,
	table_loop_option,
	table_loop_property,
	table_loopable_port,
	table_useable_clock,
	table_clock_option,
	table_dev_clock,
    table_useable_pcmclock,
    table_pcmclock_option,
    table_pcm_clock,
    table_device_files,
    table_device_bitfiles,
    table_module_size
}Mib_Module_Table_E;


class CMibFunctionModuleGroup : public CMibGroup {
	CMibFunctionModuleGroup();
public:
	CMibFunctionModuleGroup(uint32* oid, uint8 oidlen);
	virtual ~CMibFunctionModuleGroup();
	virtual CMibEntry* MakeTable(int sn, uint32* oid, uint32 oidLen);
private:
	static table_info_T tableInfo[table_module_size];
};
#endif /* CMIBFUNCTIONMODULEGROUP_H_ */
