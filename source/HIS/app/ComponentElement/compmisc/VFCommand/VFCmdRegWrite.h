/*
 * VFCmdRegWrite.h
 *
 *  Created on: 2014-3-25
 *      Author: Administrator
 */

#ifndef VFCMDREGWRITE_H_
#define VFCMDREGWRITE_H_

#include "VFCommand.h"

class VFCmdRegWrite: public VFCommand {
    VFCmdRegWrite();
public:
    virtual ~VFCmdRegWrite();
    VFCmdRegWrite(uint8 chipID, uint8 regType, uint8 regAddr, uint8 regValue) {
        para[0] = chipID;
        para[1] = regType;
        para[2] = regAddr;
        para[3] = regValue;
    };
    virtual uint8 getNMByte(void) {
        return 0x81;
    };
    virtual uint8 getParaLen(void) {
        return 4;
    };
    virtual uint8* getPara(void) {
        return para;
    };

private:
    uint8 para[4];
};

#endif /* VFCMDREGWRITE_H_ */
