/*
 * VFCmdTSRcvGain.h
 *
 *  Created on: 2014-3-25
 *      Author: Administrator
 */

#ifndef VFCMDTSRCVGAIN_H_
#define VFCMDTSRCVGAIN_H_

#include "VFCommand.h"



class VFCmdTSRcvGain: public VFCommand {
    VFCmdTSRcvGain();
public:
    VFCmdTSRcvGain(uint8 tsID, uint8 gain) {
        para[0] = tsID;
        para[1] = gain;
    };
    virtual ~VFCmdTSRcvGain();

    virtual uint8 getNMByte(void) {
        return 0x87;
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

#endif /* VFCMDTSRCVGAIN_H_ */
