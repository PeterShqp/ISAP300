/*
 * VFCmdCardInit.h
 *
 *  Created on: 2015年6月10日
 *      Author: Administrator
 */

#ifndef VFCMDCARDINIT_H_
#define VFCMDCARDINIT_H_

#include "VFCommand.h"

class VFCmdCardInit: public VFCommand {
public:
    VFCmdCardInit();
    virtual ~VFCmdCardInit();

    virtual uint8 getNMByte(void) {
        return 0xa5;
    }
    virtual uint8 getParaLen(void) {
        return 0;
    }
    virtual uint8* getPara(void) {
        return 0;
    }
};

#endif /* VFCMDCARDINIT_H_ */
