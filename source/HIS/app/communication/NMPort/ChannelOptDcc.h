/*
 * ChannelOptDcc.h
 *
 *  Created on: 2016年10月24日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMMUNICATION_NMPORT_CHANNELOPTDCC_H_
#define SOURCE_HIS_APP_COMMUNICATION_NMPORT_CHANNELOPTDCC_H_

#include "NMChannel.h"
#include "DriverPCM.h"

class ChannelOptDcc: public NMChannel {
public:
    ChannelOptDcc(uint32 uid, DriverPCM& d);
    virtual ~ChannelOptDcc();

    virtual NM_Port_Mode_E getMode(void) {
        return dcc;
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
private:
    DriverPCM& chip;
    NM_CH_E hid;
};

#endif /* SOURCE_HIS_APP_COMMUNICATION_NMPORT_CHANNELOPTDCC_H_ */
