/*
 * VFCmdCoeWrite.h
 *
 *  Created on: 2015年5月13日
 *      Author: Administrator
 */

#ifndef VFCMDCOEWRITE_H_
#define VFCMDCOEWRITE_H_

#include "VFCommand.h"

class VFCmdCoeWrite: public VFCommand {
    VFCmdCoeWrite();
public:
    virtual ~VFCmdCoeWrite();
    VFCmdCoeWrite(uint8 chipID, uint8 chID, uint8 block, uint16* words, uint8 wordCount) {
        para[0] = chipID;
        para[1] = chID;
        para[2] = block;
        para[3] = wordCount;
        for (int i = 0; i < wordCount; ++i) {
            para[2*i+4] = words[i] >> 8;
            para[2*i+5] = words[i] & 0xff;
        }
     };

    virtual uint8 getNMByte(void) {
        return 0x8a;
    };
    virtual uint8 getParaLen(void) {
        return para[3]+4;
    };
    virtual uint8* getPara(void) {
        return para;
    };

private:
    uint8 para[8*2+4];
};

#endif /* VFCMDCOEWRITE_H_ */
