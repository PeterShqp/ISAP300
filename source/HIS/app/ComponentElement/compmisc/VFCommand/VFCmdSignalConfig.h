/*
 * VFCmdSignalConfig.h
 *
 *  Created on: 2016年8月23日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_VFCOMMAND_VFCMDSIGNALCONFIG_H_
#define SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_VFCOMMAND_VFCMDSIGNALCONFIG_H_

#include "VFCommand.h"

class VFCmdSignalConfig: public VFCommand {
    VFCmdSignalConfig();
public:
    VFCmdSignalConfig(uint8 tsID, uint8 offHook, uint8 onHook) {
        para[0] = tsID;
        para[1] = offHook;
        para[2] = onHook;
    };
    virtual ~VFCmdSignalConfig();

    virtual uint8 getNMByte(void) {
        return 0x8b;
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

#endif /* SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_VFCOMMAND_VFCMDSIGNALCONFIG_H_ */
