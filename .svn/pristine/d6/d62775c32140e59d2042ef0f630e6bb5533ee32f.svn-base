/*
 * os_init.cpp
 *
 *  Created on: 2013-9-24
 *      Author: Administrator
 */

#include "os_def.h"
#include "SysInitial.h"

__task void init (void) {
    sys_init();     //板级系统初始化
    os_tsk_delete_self ();

}

/*
 * 设备上电首先要设置中断向量表、各个CPU模式的堆栈、C库环境初始化
 * 进入Main程序后的设备上电初始化由此开始
 * 1. 操作系统初始化，此步骤为其他任务运行的前提，必须首先执行os_sys_init（）
 * 2.
 */
void rtx_os_init(void) {

    os_sys_init(init);
    while(1);       //never run
}


