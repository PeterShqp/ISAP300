/*
 * SysInitial.cpp
 *
 *  Created on: 2013-9-24
 *      Author: Shqp
 */

#include "SysInitial.h"
#include "SysCLI.h"
#include "NAND_File.h"
#include "ProtectAssistCell.h"
#include "Uart1.h"
int sys_init(void) {
    cli_init();
	huartInit();
    NandFile_init();

    ProtectAssistCell::instance().start();
    return 0;
}



