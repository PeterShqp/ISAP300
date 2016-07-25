/*
 * VFCmdTSMode.h
 *
 *  Created on: 2014-3-25
 *      Author: Administrator
 */

#ifndef VFCMDTSMODE_H_
#define VFCMDTSMODE_H_

#include "VFCommand.h"

class VFCmdTSMode: public VFCommand {
    VFCmdTSMode();
public:
    VFCmdTSMode(uint8 tsID, uint8 mode) {
        para[0] = tsID;
        para[1] = mode;
    };
    virtual ~VFCmdTSMode();
    virtual uint8 getNMByte(void) {
        return 0x85;
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

#endif /* VFCMDTSMODE_H_ */
