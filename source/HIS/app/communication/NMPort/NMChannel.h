/*
 * NMChannel.h
 *
 *  Created on: 2015年10月12日
 *      Author: Administrator
 */

#ifndef NMCHANNEL_H_
#define NMCHANNEL_H_

#include "Resource.h"
#include <vector>

typedef enum {
    dcc,
    dcn
}NM_Port_Mode_E;

class NMPort;

class NMChannel : public Resource {
public:
    NMChannel(uint32 uid);
    virtual ~NMChannel();

    virtual NM_Port_Mode_E getMode(void) = 0;
    virtual uint16 getMTU(void) = 0;
    virtual void start(void) = 0; //开始收发数据
    virtual void stop(void) = 0;  //停止收发
    virtual bool receivData(void);
    virtual void sendData(uint8* d, uint32 len) = 0;

    virtual bool setTSMap(uint32) { //只有dcn通道需要重载此函数
        return false;
    };
    virtual uint32 getTSMap(void) {
        return false;
    };
//
    virtual bool havePacet(void) = 0;
    virtual int getPacketLen(void) = 0;
    virtual bool getPacketData(uint8*d, uint16 len = 0, uint16 startPos = 0) = 0;
    virtual void discardPacket() = 0;

    void setBelongPort(NMPort* port) {
        belongPort = port;
    };
private:
    NMPort* belongPort;
    NM_Port_Mode_E WorkMode;
};

#endif /* NMCHANNEL_H_ */
