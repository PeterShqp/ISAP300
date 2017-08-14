/*
 * ChannelSabit.h
 *
 *  Created on: 2015年11月11日
 *      Author: Administrator
 */

#ifndef CHANNELSABIT_H_
#define CHANNELSABIT_H_

#include "NMChannel.h"

class DriverPCM;

class ChannelSabit: public NMChannel {
public:
    ChannelSabit(uint32 uid, DriverPCM& d);
    virtual ~ChannelSabit();

    virtual NM_Port_Mode_E getMode(void) {
        return sabit;
    };

    virtual uint16 getMTU(void) {
        return 250;
    };

    virtual void start(void); //开始收发数据
    virtual void stop(void);  //停止收发
    virtual void sendData(uint8* d, uint32 len);

    virtual bool havePacet(void);
    virtual int getPacketLen(void);
    virtual bool getPacketData(uint8*d, uint16 len = 0, uint16 startPos = 0);
    virtual void discardPacket();
private:
    DriverPCM& chip;
    uint8 hid;
};

#endif /* CHANNELSABIT_H_ */
