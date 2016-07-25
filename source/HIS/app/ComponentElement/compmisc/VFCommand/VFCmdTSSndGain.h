/*
 * VFCmdTSSndGain.h
 *
 *  Created on: 2014-3-25
 *      Author: Administrator
 */

#ifndef VFCMDTSSNDGAIN_H_
#define VFCMDTSSNDGAIN_H_

#include "VFCommand.h"

class VFCmdTSSndGain: public VFCommand {
    VFCmdTSSndGain();
public:
    VFCmdTSSndGain(uint8 tsID, uint8 gain) {
        para[0] = tsID;
        para[1] = gain;
    };
    virtual ~VFCmdTSSndGain();

    virtual uint8 getNMByte(void) {
        return 0x88;
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

#endif /* VFCMDTSSNDGAIN_H_ */
