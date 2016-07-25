/*
 * VFCmdTsType.h
 *
 *  Created on: 2014-3-24
 *      Author: Administrator
 */

#ifndef VFCMDTSTYPE_H_
#define VFCMDTSTYPE_H_

#include "VFCommand.h"

class VFCmdTsType: public VFCommand {
    VFCmdTsType();
public:
    VFCmdTsType(uint8 tsID) {
        para[0] = tsID;
    };
    virtual ~VFCmdTsType();

    virtual uint8 getNMByte(void) {
        return 0x03;
    };
    virtual uint8 getParaLen(void) {
        return 1;
    };
    virtual uint8* getPara(void) {
        return para;
    };

private:
    uint8 para[1];
};

#endif /* VFCMDTSTYPE_H_ */
