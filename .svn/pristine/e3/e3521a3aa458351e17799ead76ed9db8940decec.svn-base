/*
 * DriverSDH.h
 *
 *  Created on: 2014-5-17
 *      Author: Administrator
 */

#ifndef DRIVERSDH_H_
#define DRIVERSDH_H_

#include "EZ_types.h"



class DriverSDH {
public:
    DriverSDH();
    virtual ~DriverSDH();

    virtual int connectVC4(int srcSn, uint32 destSn) = 0;
    virtual int connectVC12(int srcVC4Sn, int srcVC12Sn, uint32 destVC4Sn, uint32 destVC12Sn) = 0;


    /*status*/
    virtual bool getLOS(int STMsn) = 0;
    virtual bool getLOF(int STMsn) = 0;
    virtual bool getOOF(int STMsn) = 0;
    virtual bool getMSAIS(int STMsn) = 0;
    virtual bool getMSRDI(int STMsn) = 0;
    virtual bool getMSREI(int STMsn) = 0;

    virtual uint32 getB1(int sn) = 0;
    virtual uint32 getB2(int sn) = 0;
    virtual bool getJ0T(int sn, uint8* j0) = 0;
    virtual bool getJ0E(int sn, uint8* j0) = 0;
    virtual bool getJ0R(int sn, uint8* j0) = 0;

    virtual bool setJ0T(int sn, uint8* j0) = 0;
    virtual bool setJ0E(int sn, uint8* j0) = 0;

    virtual bool setJ0LenTransmit(int sn, uint8 mode) = 0; //0 singleByte; 1 16 bytes
    virtual bool setJ0LenExpected(int sn, uint8 mode) = 0;

    virtual bool setSingleByteJ0T(int sn, uint8 j0) = 0;

    /* HP */
    virtual uint32 getB3(int sn) = 0;
    virtual bool getJ1T(int sn, uint8* j1) = 0;
    virtual bool getJ1E(int sn, uint8* j1) = 0;
    virtual bool getJ1R(int sn, uint8* j1) = 0;

    virtual bool setJ1T(int sn, uint8* j1) = 0;
    virtual bool setJ1E(int sn, uint8* j1) = 0;



    virtual bool setJ1LenTransmit(int sn, uint8 mode) = 0; //0 singleByte; 1 16 bytes
    virtual bool setJ1LenExpected(int sn, uint8 mode) = 0;

    virtual bool setDCCOH(int ch, uint16 data) = 0;

    /*HP Status*/
    virtual bool getAUAIS(int vc4) = 0;
    virtual bool getAULOP(int vc4) = 0;
    virtual bool getHPRDI(int vc4) = 0;
    virtual bool getHPREI(int vc4) = 0;
    virtual bool getHPTIM(int vc4) = 0;
    virtual bool getHPSLM(int vc4) = 0;
    virtual bool getHPUNEQ(int vc4) = 0;

    /*configuration*/
    virtual bool setSTMPortTxEn(int STMsn, uint8 en) = 0;
    virtual bool setSTMAlsEn(int STMsn, uint8 en) = 0;

    virtual bool setLoopInOnly(int STMsn) = 0;
    virtual bool setLoopOutOnly(int STMsn) = 0;
    virtual bool setLoopInAndOut(int STMsn) = 0;
    virtual bool setLoopClear(int STMsn) = 0;
};

#endif /* DRIVERSDH_H_ */
