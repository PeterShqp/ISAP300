/*
 * EZbus.h
 *
 *  Created on: 2013-11-30
 *      Author: Administrator
 */

#ifndef EZBUS_H_
#define EZBUS_H_

#include "RegisterAccess.h"

class EZbus : public RegisterAccess {
public:
    EZbus(uint32 slt);
    virtual ~EZbus();

    /* 16bit ��EZbus�Ĳ�λĬ�Ϸ����������λ���д */
    virtual uint16 readReg(uint16 regAddr);
    virtual void writeReg(uint16 regAddr, uint16 newData, int opt = 1, uint16 verifyBitMask = 0xffff);
private:
    uint32 sltSn;
};

#endif /* EZBUS_H_ */
