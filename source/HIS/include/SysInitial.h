/*
 * SysInitial.h
 *
 *  Created on: 2013-9-24
 *      Author: Administrator
 */

#ifndef SYSINITIAL_H_
#define SYSINITIAL_H_

#if defined (__cplusplus)
extern "C"
{
#endif

int sys_init(void);

class ProtectCell {
public:
    ProtectCell();
    ~ProtectCell();
};

#if defined (__cplusplus)
}
#endif
#endif /* SYSINITIAL_H_ */
