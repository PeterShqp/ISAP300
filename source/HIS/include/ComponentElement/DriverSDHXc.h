/*
 * DriverSDHXc.h
 *
 *  Created on: 2014-5-17
 *      Author: Administrator
 */

#ifndef DRIVERSDHXC_H_
#define DRIVERSDHXC_H_

#include "DriverSDH.h"

class ChipCP1121A;
class DriverPCM;
class ChipUOPTLogic;

class DriverSDHXc: public DriverSDH {
    DriverSDHXc();
public:
    DriverSDHXc(ChipCP1121A&, DriverPCM&, ChipUOPTLogic&);
    virtual ~DriverSDHXc();

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
    ChipCP1121A& sdh;
    DriverPCM& fpga;
    ChipUOPTLogic& cpld;
};

#endif /* DRIVERSDHXC_H_ */
