/*
 * VFCmdRegRead.h
 *
 *  Created on: 2014-3-24
 *      Author: Administrator
 */

#ifndef VFCMDREGREAD_H_
#define VFCMDREGREAD_H_

#include "VFCommand.h"

class VFCmdRegRead: public VFCommand {
    VFCmdRegRead();
public:
    VFCmdRegRead(uint8 chipID, uint8 regType, uint8 regAddr) {
        para[0] = chipID;
        para[1] = regType;
        para[2] = regAddr;

    };
    virtual ~VFCmdRegRead();

    virtual uint8 getNMByte(void) {
        return 0x01;
    };
    virtual uint8 getParaLen(void) {
        return 3;
    };
    virtual uint8* getPara(void) {
        return para;
    };

private:
    uint8 para[3];
};

#endif /* VFCMDREGREAD_H_ */
