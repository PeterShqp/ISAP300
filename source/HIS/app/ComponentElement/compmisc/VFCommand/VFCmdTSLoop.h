/*
 * VFCmdTSLoop.h
 *
 *  Created on: 2014-3-24
 *      Author: Administrator
 */

#ifndef VFCMDTSLOOP_H_
#define VFCMDTSLOOP_H_

#include "VFCommand.h"

class VFCmdTSLoop: public VFCommand {
    VFCmdTSLoop();
public:
    VFCmdTSLoop(uint8 tsID, uint8 loop) {
        para[0] = tsID;
        para[1] = loop;
    };
    virtual ~VFCmdTSLoop();

    virtual uint8 getNMByte(void) {
        return 0x82;
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

#endif /* VFCMDTSLOOP_H_ */
