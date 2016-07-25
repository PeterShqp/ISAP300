/*
 * DriverSDH8STM1.h
 *
 *  Created on: 2014-5-17
 *      Author: Administrator
 */

#ifndef DRIVERSDH8STM1_H_
#define DRIVERSDH8STM1_H_

#include "DriverSDH.h"

class ChipRC7883;
class Chip8STM1Logic1;
class Chip8STM1Logic2;

class DriverSDH8STM1: public DriverSDH {
public:
    DriverSDH8STM1(ChipRC7883&, ChipRC7883&, ChipRC7883&, ChipRC7883&, Chip8STM1Logic1&, Chip8STM1Logic2&);
    virtual ~DriverSDH8STM1();

    virtual int connectVC4(int srcSn, uint32 destSn);
    virtual int connectVC12(int srcVC4Sn, int srcVC12Sn, uint32 destVC4Sn, uint32 destVC12Sn);

    /*status*/
    virtual bool getLOS(int STMsn);
    virtual bool getLOF(int STMsn);
    virtual bool getOOF(int STMsn);
    virtual bool getMSAIS(int STMsn);
    virtual bool getMSRDI(int STMsn);
    virtual bool getMSREI(int STMsn);

    virtual uint32 getB1(int sn);
    virtual uint32 getB2(int sn);
    virtual bool getJ0T(int sn, uint8* j0);
    virtual bool getJ0E(int sn, uint8* j0);
    virtual bool getJ0R(int sn, uint8* j0);

    virtual bool setJ0T(int sn, uint8* j0);
    virtual bool setJ0E(int sn, uint8* j0);

    virtual bool setJ0LenTransmit(int sn, uint8 mode); //0 singleByte; 1 16 bytes
    virtual bool setJ0LenExpected(int sn, uint8 mode);

    virtual bool setSingleByteJ0T(int sn, uint8 j0);

    /* HP */
    virtual uint32 getB3(int sn);
    virtual bool getJ1T(int sn, uint8* j1);
    virtual bool getJ1E(int sn, uint8* j1);
    virtual bool getJ1R(int sn, uint8* j1);

    virtual bool setJ1T(int sn, uint8* j1);
    virtual bool setJ1E(int sn, uint8* j1);

    virtual bool setJ1LenTransmit(int sn, uint8 mode); //0 singleByte; 1 16 bytes
    virtual bool setJ1LenExpected(int sn, uint8 mode);

    virtual bool setDCCOH(int ch, uint16 data);

    /*HP Status*/
    virtual bool getAUAIS(int vc4);
    virtual bool getAULOP(int vc4);
    virtual bool getHPRDI(int vc4);
    virtual bool getHPREI(int vc4);
    virtual bool getHPTIM(int vc4);
    virtual bool getHPSLM(int vc4);
    virtual bool getHPUNEQ(int vc4);

    /*configuration*/
    virtual bool setSTMPortTxEn(int STMsn, uint8 en);
    virtual bool setSTMAlsEn(int STMsn, uint8 en);

    virtual bool setLoopInOnly(int STMsn);
    virtual bool setLoopOutOnly(int STMsn);
    virtual bool setLoopInAndOut(int STMsn);
    virtual bool setLoopClear(int STMsn);
private:
    ChipRC7883& chip1;
    ChipRC7883& chip2;
    ChipRC7883& chip3;
    ChipRC7883& chip4;
    Chip8STM1Logic1& fpga1;
    Chip8STM1Logic2& fpga2;
};

#endif /* DRIVERSDH8STM1_H_ */
