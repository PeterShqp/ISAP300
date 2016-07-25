/*
 * SysCLI.cpp
 *
 *  Created on: 2013-11-12
 *      Author: Administrator
 */

#include "SysCLI.h"
#include "TerminalUart.h"
#include "Mid_CLI.h"
#include "os.h"


__task void T_CLI_Process(void) {
    while(1) {
        CLI_Process();
    }
}


void cli_init(void) {
    TerminalUARTInit();
    CliManagerInit();
    os_tsk_create(T_CLI_Process, P_CLI_Process);
}

