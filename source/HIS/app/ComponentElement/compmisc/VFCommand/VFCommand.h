/*
 * VFCommand.h
 *
 *  Created on: 2014-3-24
 *      Author: Administrator
 */

#ifndef VFCOMMAND_H_
#define VFCOMMAND_H_

#include "EZ_types.h"

class VFCommand {
public:
    VFCommand();
    virtual ~VFCommand();

    /* ��ȡ����֡���ֽ��� */
    uint8* toByteStream(void) {
        SendBuff[0] = getParaLen() + 1;
        SendBuff[1] = getNMByte();
        uint8* para = getPara();
        if( para ) {
            for(int i = 0; i < getParaLen(); i++ ) {
                SendBuff[i+2] = para[i];
            }
        }
        return SendBuff;
    };

    /* ��ȡ����֡���ֽڳ��� */
    int bytes() {
        return getParaLen() + 2;
    };


    /* ��ȡ�忨��Ӧ��Ч��� */
    uint8* getResult(void) {
        return &ResultBuff[2];
    };

    uint8 getResultLen(void) {
        return ResultBuff[0]-1;
    };

    /* for result write */
    uint8* getResultBuff(void) {
        return ResultBuff;
    };


    /* ��ͬ����ֱ�ʵ�� */
    virtual uint8 getNMByte(void) = 0;
    virtual uint8 getParaLen(void) = 0;
    virtual uint8* getPara(void) = 0;
private:
    uint8 ResultBuff[32];
    uint8 SendBuff[32];
};

#endif /* VFCOMMAND_H_ */
