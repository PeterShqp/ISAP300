/*
 * os.h
 *
 *  Created on: 2013-9-23
 *      Author: Administrator
 */

#ifndef OS_H_
#define OS_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "os_def.h"

#define OS_INIT         __OS_INIT__
#define OS_TASK_CREAT(tsk,prio,stk,size)  os_tsk_create_user(tsk,prio,stk,size)


#if defined (__cplusplus)
}
#endif
#endif /* OS_H_ */
