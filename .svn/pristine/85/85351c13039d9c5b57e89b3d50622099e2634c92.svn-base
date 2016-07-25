/*
 * ChipRC7883.h
 *
 *  Created on: 2013-12-27
 *      Author: Administrator
 */

#ifndef CHIPRC7883_H_
#define CHIPRC7883_H_

#include "BaseChip.h"
#include "rc7880RegDriverfuncLib.h"
#include "os.h"

class RegisterAccess;
class CBaseSlot;

typedef enum {
    mode_MAP,
    mode_TM,
    mode_PHY,
    mode_MAP_2,
}RC7883_Work_Mode_E;

class ChipRC7883 : public BaseChip {
    uint32 RC7880_ADDR;

public:
    ChipRC7883(CBaseSlot* slt, uint32 baseAddr, RC7883_Work_Mode_E mode);
    virtual ~ChipRC7883();

    virtual Chip_INIT_RESULT ChipInit(void);

    bool setPortEnable(int port, int en);
    bool setSNCP(int port, int en);

    bool setPortLoopOutAndIn(int port);
    bool setPortLoopInOnly(int port);
    bool setPortLoopOutOnly(int port);
    bool setPortLoopClear(int port);


    /**/
    /*status*/
    bool getLOS(int STMsn); // stmsn 0~1
    bool getLOF(int STMsn);
    bool getOOF(int STMsn);
    bool getMSAIS(int STMsn);
    bool getMSRDI(int STMsn);
    bool getMSREI(int STMsn);

    bool ifAlarm(int STMsn);

    uint32 getB1(int sn);
    uint32 getB2(int sn);
    bool getJ0T(int sn, uint8* j0);
    bool getJ0E(int sn, uint8* j0);
    bool getJ0R(int sn, uint8* j0);

    bool setJ0T(int sn, uint8* j0);
    bool setJ0E(int sn, uint8* j0);

    bool setJ0LenTransmit(int sn, uint8 mode); //0 singleByte; 1 16 bytes
    bool setJ0LenExpected(int sn, uint8 mode);

    bool setSingleByteJ0T(int sn, uint8 j0);


    uint32 getB3(int sn);
    bool getJ1T(int sn, uint8* j1);
    bool getJ1E(int sn, uint8* j1);
    bool getJ1R(int sn, uint8* j1);

    bool setJ1T(int sn, uint8* j1);
    bool setJ1E(int sn, uint8* j1);

    bool setJ1LenTransmit(int sn, uint8 mode); //0 singleByte; 1 16 bytes
    bool setJ1LenExpected(int sn, uint8 mode);

    bool getAUAIS(int vc4);
    bool getAULOP(int vc4);
    bool getHPRDI(int vc4);
    bool getHPREI(int vc4);
    bool getHPTIM(int vc4);
    bool getHPSLM(int vc4);
    bool getHPUNEQ(int vc4);

    /*E1 status*/
    bool getE1Los(int e1sn);

private:
    RegisterAccess* ra;
    OS_MUT mut_7880;//������
    RC7883_Work_Mode_E Wmode;

    BYTE readRc7880RegByte(WORD addr);
    int writeRegByte(WORD addr , BYTE data);
    int writeRc7880RegByte(WORD addr , BYTE data);
    int writeRc7880RegLock(void);
    int writeRc7880RegUnlock(void);


    int RC7880Tu12UnitTsSelectWrite(BYTE    tu12Id , BYTE select);
    int RC7880Tu12UnitV5SendWrite(BYTE tu12Id , BYTE sendData);
    int RC7880Tu12V5ExpectWrite(BYTE tu12Id , BYTE v5Expect);
    int RC7880Tu12UnitTu12LoopWrite(BYTE  tu12Id , BYTE lineLoop , BYTE devLoop);

    int RC7880Tu12UnitProtectModeWrite(BYTE tu12Id , BYTE protectMode /*, BYTE startFlag*/);
    int RC7880DrvVC4UnitAlarmRead (BYTE vc4Id , BYTE *iA0P , BYTE *iA1P , BYTE *iA2P);
    int RC7880DrvVC4UniteB1PerformRead(BYTE vc4Id , WORD *counterB1P);

    int RC7880OHUnitOtherDxcWrite(BYTE  startAddr , BYTE  endAddr , BYTE     startSrcAddr);
    int clearOHDXC(void);
    int RC7880DrvVC4UnitRcvOverHeadRead(
                                BYTE    vc4Id ,
                                Vc4UnitOverHead_t *overHeadP);
    int RC7880DrvVC4UnitSendOverHeadWrite(
                                BYTE    vc4Id ,
                                Vc4UnitOverHead_t *overHeadP ,
                                BYTE    j0CrcEnable ,
                                BYTE    j1CrcEnable);

    int RC7880DrvVC4UnitExceptOverHeadWrite(
                                BYTE    vc4Id ,
                                Vc4UnitExceptOverHead_t *overHeadP ,
                                BYTE    j0CrcEnable ,
                                BYTE    j1CrcEnable);
    BYTE RC7880DrvCRC7Func(const BYTE *pSrc , DWORD cnt);
    void RC7880DrvReadNewJxBytes(BYTE *jxCharP , BYTE *jxByteP , BYTE jxLen);
    void RC7880DrvWriteNewJxBytes(BYTE *jxCharP , BYTE *jxByteP , BYTE jxLen);

    int RC7880DrvTU12UnitAlarmRead(BYTE tu12Id, BYTE *e1P, BYTE *dropA, BYTE *DropB);


};

#endif /* CHIPRC7883_H_ */
