/*
 * CLoopModule.cpp
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#include "CLoopModule.h"

CLoopModule CLoopModule::loopModule;

TASK void T_Loop_Check(void );

CLoopModule::CLoopModule() {
	// TODO Auto-generated constructor stub
    t_loop_check = 0;
}

CLoopModule::~CLoopModule() {
	// TODO Auto-generated destructor stub
}


void CLoopModule::start() {
    os_mut_init(mut);
    t_loop_check = os_tsk_create(T_Loop_Check, P_Loop_Process);
}

void CLoopModule::stop(void) {
    os_tsk_delete(t_loop_check);
}

TASK void T_Loop_Check(void ) {
    while( 1 ) {
        os_dly_wait(100);

        /* Loop Check */
        CLoopModule::instance().runLoopCheck();
    }
}


