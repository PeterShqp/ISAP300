/*
 * RegisterAccess.h
 *
 *  Created on: 2013-12-1
 *      Author: Administrator
 */

#ifndef REGISTERACCESS_H_
#define REGISTERACCESS_H_

#include "EZ_types.h"

class RegisterAccess {
public:
    RegisterAccess();
    virtual ~RegisterAccess();

    virtual uint16 readReg(uint16 regAddr) = 0;
    virtual void writeReg(uint16 regAddr, uint16 newData, int opt = 1, uint16 verifyBitMask = 0xffff) = 0;

    bool readRegCheck(uint16 regAddr, uint16* regValue, int retry = 3);
    bool readRegCheck3(uint16 regAddr, uint16* regValue, uint16 bitmask = 0xffff);
};

#endif /* REGISTERACCESS_H_ */
