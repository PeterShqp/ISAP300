/*
 * ChannelTsDcn.h
 *
 *  Created on: 2015年11月11日
 *      Author: Administrator
 */

#ifndef CHANNELTSDCN_H_
#define CHANNELTSDCN_H_

#include "NMChannel.h"

class DriverPCM;

class ChannelTsDcn: public NMChannel {
public:
    ChannelTsDcn(uint32 uid, DriverPCM& d);
    virtual ~ChannelTsDcn();

    virtual NM_Port_Mode_E getMode(void) {
        return dcn;
    };
    virtual uint16 getMTU(void) {
        return 1000;
    };

    virtual void start(void); //开始收发数据
    virtual void stop(void);  //停止收发
    virtual void sendData(uint8* d, uint32 len);

    virtual bool havePacet(void);
    virtual int getPacketLen(void);
    virtual bool getPacketData(uint8*d, uint16 len = 0, uint16 startPos = 0);
    virtual void discardPacket();

    virtual bool setTSMap(uint32);
    virtual uint32 getTSMap(void);
private:
    DriverPCM& chip;
    uint8 hid;
};

#endif /* CHANNELTSDCN_H_ */
