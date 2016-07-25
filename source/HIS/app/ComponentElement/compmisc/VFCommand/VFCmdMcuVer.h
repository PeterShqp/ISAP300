/*
 * VFCmdMcuVer.h
 *
 *  Created on: 2015年9月29日
 *      Author: Administrator
 */

#ifndef VFCMDMCUVER_H_
#define VFCMDMCUVER_H_

#include "VFCommand.h"

class VFCmdMcuVer: public VFCommand {
public:
    VFCmdMcuVer();
    virtual ~VFCmdMcuVer();
    virtual uint8 getNMByte(void) {
        return 0xa6;
    }
    virtual uint8 getParaLen(void) {
        return 0;
    }
    virtual uint8* getPara(void) {
        return 0;
    }
};

#endif /* VFCMDMCUVER_H_ */
