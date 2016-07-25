
/*
 * VFCmdTSPolarTurn.h
 *
 *  Created on: 2014-3-31
 *      Author: Administrator
 */

#ifndef VFCMDTSPOLARTURN_H_
#define VFCMDTSPOLARTURN_H_

#include "VFCommand.h"

class VFCmdTSPolarTurn: public VFCommand {
    VFCmdTSPolarTurn();
public:
    VFCmdTSPolarTurn(uint8 tsID, uint8 polar) {
        para[0] = tsID;
        para[1] = polar;
    };
    virtual ~VFCmdTSPolarTurn();
    virtual uint8 getNMByte(void) {
        return 0x86;
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

#endif /* VFCMDTSPOLARTURN_H_ */
