/*
 * Chip30VFLogic.h
 *
 *  Created on: 2014-2-21
 *      Author: Administrator
 */

#ifndef CHIP30VFLOGIC_H_
#define CHIP30VFLOGIC_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;

class Chip30VFLogic  : public BaseChip {
//    static const int REG_INC_SND_ST  = 0; //1 IDLE, 0 BUSY
    static const int REG_INC_SND_BUF = 0x0100;
    static const int REG_INC_SND_START = REG_INC_SND_BUF + 31; //option write start

    static const int REG_INC_SND_RCV_ST  = 1; //bit1: 1 have Packet, 0 no packet
                                              //bit0: 1 IDLE, 0 BUSY
    static const int REG_INC_RCV_BUF = 0x0120;
    static const int REG_INC_RCV_OVER = REG_INC_RCV_BUF + 31; //option read over


public:
    Chip30VFLogic(CBaseSlot* slt);
    virtual ~Chip30VFLogic();

    virtual Chip_INIT_RESULT ChipInit(void);

    bool ifSendBusy(void);
    void sendPacket(uint8* data, uint8 len);

    bool ifHavePacket(void);
    void readPacket(uint8* data);
private:
    RegisterAccess* regAccess;
};

#endif /* CHIP30VFLOGIC_H_ */
