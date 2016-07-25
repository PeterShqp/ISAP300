/*
 * VFCmdCoeRead.h
 *
 *  Created on: 2015年5月13日
 *      Author: Administrator
 */

#ifndef VFCMDCOEREAD_H_
#define VFCMDCOEREAD_H_

#include "VFCommand.h"

class VFCmdCoeRead: public VFCommand {
    VFCmdCoeRead();
public:
    virtual ~VFCmdCoeRead();
    VFCmdCoeRead(uint8 chipID, uint8 chID, uint8 block, uint8 wordCount) {
        para[0] = chipID;
        para[1] = chID;
        para[2] = block;
        para[3] = wordCount;

    };

    virtual uint8 getNMByte(void) {
        return 0x89;
    };
    virtual uint8 getParaLen(void) {
        return 4;
    };
    virtual uint8* getPara(void) {
        return para;
    };

private:
    uint8 para[4];
};

#endif /* VFCMDCOEREAD_H_ */
