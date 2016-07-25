/*
 * CMibFunctionModuleGroup.cpp
 *
 *  Created on: 2013-4-28
 *      Author: Administrator
 */

#include "CMibFunctionModuleGroup.h"
#include "CMibXCAddTable.h"
#include "CMibXCProperty.h"
#include "CMibLoopAddTable.h"
#include "CMibLoopPropertyTable.h"
#include "CMibLoopablePortTable.h"
#include "TableUseableClockSource.h"
#include "TableClockSourceOption.h"
#include "TableDeviceClockSource.h"
#include "PcmClockOptionTable.h"
#include "PcmClockSourceTable.h"
#include "PcmUseableClockSourceTable.h"
#include "TableDeviceFiles.h"
#include "TableDeviceBitFiles.h"

table_info_T CMibFunctionModuleGroup::tableInfo[table_module_size] = {
		{1, xc_add_size, 2},
		{2, xc_property_size, 3},
		{7, loop_add_size, 1},
		{8, loop_col_size, 2},
		{9, loopable_port_size, 2},
		{10, usable_clk_size, 2},
		{11, clk_option_size, 1},
		{12, dev_clk_size, 2},
        {13, pcm_usable_clk_size, 2},
        {14, pcm_clk_option_size, 1},
        {15, pcm_clk_size, 2},
        {16, file_size, 2},
        {17, bfile_size, 2},
};


CMibFunctionModuleGroup::CMibFunctionModuleGroup(uint32* oid, uint8 oidlen) : CMibGroup(oid, oidlen){
	// TODO Auto-generated constructor stub
	creatTables(tableInfo, table_module_size);
}

CMibFunctionModuleGroup::~CMibFunctionModuleGroup() {
	// TODO Auto-generated destructor stub
}

CMibEntry* CMibFunctionModuleGroup::MakeTable(int sn, uint32* oid, uint32 oidLen) {
	switch( sn ) {
	case table_cross_option:
		return new CMibXCAddTable(oid, oidLen, &tableInfo[sn]);
	case table_cross_property:
		return new CMibXCProperty(oid, oidLen, &tableInfo[sn]);
	case table_loop_option:
		return new CMibLoopAddTable(oid, oidLen, &tableInfo[sn]);
	case table_loop_property:
		return new CMibLoopPropertyTable(oid, oidLen, &tableInfo[sn]);
	case table_loopable_port:
		return new CMibLoopablePortTable(oid, oidLen, &tableInfo[sn]);
	case table_useable_clock:
	    return new TableUseableClockSource(oid, oidLen, &tableInfo[sn]);
	case table_clock_option:
	    return new TableClockSourceOption(oid, oidLen, &tableInfo[sn]);
	case table_dev_clock:
        return new TableDeviceClockSource(oid, oidLen, &tableInfo[sn]);
    case table_useable_pcmclock:
        return new PcmUseableClockSourceTable(oid, oidLen, &tableInfo[sn]);
    case table_pcmclock_option:
        return new PcmClockOptionTable(oid, oidLen, &tableInfo[sn]);
    case table_pcm_clock:
        return new PcmClockSourceTable(oid, oidLen, &tableInfo[sn]);
    case table_device_files:
        return new TableDeviceFiles(oid, oidLen, &tableInfo[sn]);
    case table_device_bitfiles:
        return new TableDeviceBitFiles(oid, oidLen, &tableInfo[sn]);
	default:
		return 0;
	}
}
