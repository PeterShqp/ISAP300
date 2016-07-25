/*
 * VFCmdTSEnable.h
 *
 *  Created on: 2014-3-24
 *      Author: Administrator
 */

#ifndef VFCMDTSENABLE_H_
#define VFCMDTSENABLE_H_

#include "VFCommand.h"

class VFCmdTSEnable: public VFCommand {
    VFCmdTSEnable();
public:
    VFCmdTSEnable(uint8 tsID, uint8 en) {
        para[0] = tsID;
        para[1] = en;
    };
    virtual ~VFCmdTSEnable();

    virtual uint8 getNMByte(void) {
        return 0x84;
    };
    virtual uint8 getParaLen(void) {
        return 2;
    };
    virtual uint8* getPara(void) {
        return para;
    };

private:
    uint8 para[2];
};

#endif /* VFCMDTSENABLE_H_ */
