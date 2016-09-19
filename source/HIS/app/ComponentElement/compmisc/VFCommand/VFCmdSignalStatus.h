/*
 * VFCmdSignalStatus.h
 *
 *  Created on: 2016年9月12日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_VFCOMMAND_VFCMDSIGNALSTATUS_H_
#define SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_VFCOMMAND_VFCMDSIGNALSTATUS_H_

#include "VFCommand.h"

class VFCmdSignalStatus: public VFCommand {
    VFCmdSignalStatus();
public:
    VFCmdSignalStatus(uint8 tsID) {
        para[0] = tsID;
    };
    virtual ~VFCmdSignalStatus();
    virtual uint8 getNMByte(void) {
        return 0x8c;
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

#endif /* SOURCE_HIS_APP_COMPONENTELEMENT_COMPMISC_VFCOMMAND_VFCMDSIGNALSTATUS_H_ */
