/*
 * ChipCP1121A.h
 *
 *  Created on: 2013-11-26
 *      Author: Administrator
 */

#ifndef CHIPCP1121A_H_
#define CHIPCP1121A_H_

#include "BaseChip.h"
#include <map>

class RegisterAccess;
class CBaseSlot;

class ChipCP1121A : public BaseChip {
    const static uint32 ID          = 0x0000;
    const static uint32 MCR         = 0x0002;  //bit0 155(0) 622(1)
    const static uint32 CDRCTR      = 0x0007;
    const static uint32 BHLXMCTL    = 0x6000;
    const static uint32 HLXST       = 0x6001;
    const static uint32 HLXCR_PG0   = 0x6002;
    const static uint32 HLXCR_PG1   = 0x6042;
    const static uint32 HLXCM_PG0   = 0x7000;
    const static uint32 HLXCM_PG1   = 0x7040;

    const static uint32 TUTSCFG     = 0x4000;
    const static uint32 CCR         = 0x4001;
    const static uint32 PPSCR       = 0x4002;
    const static uint32 TV5K4LINA   = 0x4042;
    const static uint32 TV5K4LINB   = 0x4044;
    const static uint32 TJ2         = 0x4050;

    /* P reg in sop */
    const static uint32 RRSTMC      = 0x1001;   //bit 0 J0 Len receive
    const static uint32 RRSALM      = 0x1007;   //RITM(3) LOS(2) LOF(1) OOF(0)
    const static uint32 RMSALM      = 0x10A0;   //MSAIS(2) MSRDI(3)
    const static uint32 RRSBIPCL    = 0x1002;   //B1
    const static uint32 RRSBIPCH    = 0x1003;   //B1
    const static uint32 RMSBIPCL    = 0x1081;   //B2
    const static uint32 RMSBIPCH    = 0x1082;   //B2

    const static uint32 TRSCTL      = 0x1040;   //bit7 J0Len Transmit
    const static uint32 RRSEXPTM0   = 0x1030;   //J0 Expected byte0
    const static uint32 RRSRECTM0   = 0x1038;   //J0 Received byte0
    const static uint32 TRSTRATM0   = 0x1078;   //J0 Transmit byte0

    const static uint32 TRSJ0       = 0x1044;   //bit0~7 J0Byte, bit8~15 Z0byte

    /* P reg in path sop */

    const static uint32 RPBIPCL     = 0x1005;   //B3
    const static uint32 RPBIPCH     = 0x1006;   //B3
    const static uint32 RPTMC       = 0x100B;   //bit0 J1Len receive 16bytes(0) 64bytes(1)
    const static uint32 RPEXPTM0    = 0x1030;   //J1 Expected
    const static uint32 RPRECTM0    = 0x1050;   //J1 received
    const static uint32 TPTRATM0    = 0x10D0;   //J1 Transmit
    const static uint32 TPCTL       = 0x1080;   //bit7 J1Len Transmit
    const static uint32 RPALM1      = 0x1020;   //bit5 HPUNEQ
                                                //bit4 AUAIS
                                                //bit3 LOP
                                                //bit2 VCAIS
                                                //bit1 PSLM
                                                //bit0 PTIM



public:
    ChipCP1121A( CBaseSlot* ra);
    virtual ~ChipCP1121A();

    virtual Chip_INIT_RESULT ChipInit(void);

    int connectVC4(int srcSn, uint32 destSn);
    int connectVC12(int srcVC4Sn, int srcVC12Sn, uint32 destVC4Sn, uint32 destVC12Sn);


    /*status*/
    bool getLOS(int STMsn);
    bool getLOF(int STMsn);
    bool getOOF(int STMsn);
    bool getMSAIS(int STMsn);
    bool getMSRDI(int STMsn);
    bool getMSREI(int STMsn);

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

    /* HP */
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

    bool setLoopOut(int sn, uint8 en);

private:
    RegisterAccess* regAccess;
    int currentPage(void);
    void switchPageTo(int page);
    bool switchPage(void);
    int vc4RegAddr(int vc4sn); //��ȡ��ǰ��дҳ�ļĴ�����ַ
    int vc12RegAddr(int vc4sn, int vc12sn);

    const static uint16 CP1121A_ID = 0x0461;

    static uint16 PRegSOP(int sn, uint16 base) {
        uint16 offset = 0;
        if( sn == 0 ) {
            offset = 3 << 8;
        }
        else {
            offset = 11 << 8;
        }
        return offset | base;
    };

    static uint16 PRegSOPPath(int sn, uint16 base) {
        uint16 offset = 0;
        switch( sn ) {
        case 0:
            offset = 4 << 8;
            break;
        case 1:
            offset = 5 << 8;
            break;
        case 2:
            offset = 6 << 8;
            break;
        case 3:
            offset = 7 << 8;
            break;
        case 4:
            offset = 0xc << 8;
            break;
        case 5:
            offset = 0xd << 8;
            break;
        case 6:
            offset = 0xe << 8;
            break;
        case 7:
            offset = 0xf << 8;
            break;
        }
        return offset | base;
    };
};

#endif /* CHIPCP1121A_H_ */
