/*
 * DriverPCM.h
 *
 *  Created on: 2015年6月4日
 *      Author: Administrator
 */

#ifndef DRIVERPCM_H_
#define DRIVERPCM_H_

#include "EZ_types.h"
#include "ClockSourceDefine.h"

typedef enum {
    DCC_A,
    DCC_B,
    DCN_A,
    DCN_B

}NM_CH_E;

typedef enum {
    type_2Mbit,
    type_2MHz,
    type_frameE1
}ExtClock_type_E;

class DriverPCM {
public:
    DriverPCM();
    virtual ~DriverPCM();

    /*SDH Clock*/
    virtual void resetClockChip(void) = 0;
    virtual void selectClockSource(USEABLE_RCLOCK cs) = 0;
    virtual void setExtClockMode(USEABLE_RCLOCK c, ExtClock_type_E mode) = 0;

    virtual void selectPCMClock(uint8 src) = 0;

    /*64K cross connect*/
    virtual bool CreatCrossConnection(uint32 toCh, uint32 toTs, uint32 fromCh, uint32 fromTs) = 0;
    virtual bool RemoveCrossConnection(uint32 Ch, uint32 Ts) = 0;
    virtual uint16 getHID(uint32 uid) = 0;

    /*port state*/
    virtual bool itsLOS(int e1) = 0;
    virtual bool itsAIS(int e1) = 0;
    virtual bool itsLOF(int e1) = 0;
    virtual bool itsLOMF(int e1) = 0;
    /*
     * for DCC
     */
    virtual bool setDCCOH(int ch, uint16 data) = 0;

    virtual bool ifHavePacket(NM_CH_E ch) = 0;
    virtual int getPacketLen(NM_CH_E ch) = 0;
    virtual uint32 GetDCCPacket(NM_CH_E ch, uint8* buff, uint16 len, uint16 startPos = 0) = 0;
    virtual void DccSendPacket(NM_CH_E ch, uint8* data, uint16 len) = 0;
    virtual void clearDccRdBufForce(NM_CH_E ch) = 0;

    /*
     * for Sabit
     */
    virtual void setSabitInterruptEnable(uint8 ch, uint8 en) = 0;
    bool ifSaHavePacket(uint8 ch);
    virtual bool ifSaHavePacket(void) = 0;
    virtual uint8 getSourceCh(void) = 0;
    virtual int getSaPacketLen(void) = 0;
    virtual bool getSaPacket(uint8* buff, uint16 len, uint16 startPos = 0) = 0;
    virtual void readSaPacketOver(void) = 0;

    virtual void sendSaPacket(uint8 ch, uint8* data, uint16 len) = 0;


    /*
     * for dcn
     */
    virtual void setDcnInterruptEnable(uint8 ch, uint8 en) = 0;
    virtual bool selectDcnTs(uint8 ch, uint32 tsmap) = 0;
    virtual uint32 getDcnTsMap(uint8 ch) = 0;
    virtual bool ifDcnHavePacket(uint8 ch) = 0;
    virtual int getDcnPacketLen(uint8 ch) = 0;
    virtual bool getDcnPacket(uint8 ch, uint8* buff, uint16 len) = 0;
    virtual void readDcnPacketOver(uint8 ch) = 0;

    virtual void sendDcnPacket(uint8 ch, uint8* data, uint16 len) = 0;



    /*
     * for protected
     */
    virtual void setAlarm(uint8 remote, uint8 local) = 0;
    virtual void protectFSMStart(void) = 0;

    /*
     * for loop
     */
    virtual void setPortLoopOut(uint8 ch, uint8 loop) = 0;
    virtual void setPortLoopIn(uint8 ch, uint8 loop) = 0;

    /*
     * for led
     */
    virtual void turnOnLedWork(uint8 sn, bool on) {};
    virtual void turnOnLedAlm(uint8 sn, bool on) {};

    virtual void setPortEnable(uint8 port, uint8 en) {return;};
};

#endif /* DRIVERPCM_H_ */
