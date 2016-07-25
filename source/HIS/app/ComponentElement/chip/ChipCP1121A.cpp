/*
 * ChipCP1121A.cpp
 *
 *  Created on: 2013-11-26
 *      Author: Administrator
 */

#include "ChipCP1121A.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "TimeSlot2ITUT.h"
#include "ObjectReference.h"
//#include <sstream>
//#include "CPPTools.h"
//#include <stdio.h>

static const std::string chipName = "CP1121A";

ChipCP1121A::ChipCP1121A( CBaseSlot* slt ) : BaseChip( chipName) {
    // TODO Auto-generated constructor stub
    regAccess = slt->getRegisterAccess();
//    initState = ChipInit();

}

ChipCP1121A::~ChipCP1121A() {
    // TODO Auto-generated destructor stub
}


//uint8 ChipCP1121A::getDataWide(void) {
//    return 16;
//}

/*
 * if srcSn < 0, insert IDLE
 */
int ChipCP1121A::connectVC4(int srcSn, uint32 destSn) {
    uint32 regAddr = vc4RegAddr(destSn);
    uint32 regData = srcSn | 0x40;
    if( srcSn < 0 ) {
        regData = 0x20; // insert IDLE
    }
    regAccess->writeReg(regAddr, regData);
    if( switchPage() ) {
        regAddr = vc4RegAddr(destSn);
        regAccess->writeReg(regAddr, regData);
        return 1;
    }

    return -1;
}

/*
 * if srcVC4Sn < 0 || srcVC12Sn < 0, insert IDLE
 */
int ChipCP1121A::connectVC12(int srcVC4Sn, int srcVC12Sn, uint32 destVC4Sn, uint32 destVC12Sn) {
    connectVC4(-1, destVC4Sn);  //���VC4���𽻲�
    uint32 regAddr = vc12RegAddr(destVC4Sn, destVC12Sn);
    uint16 regData = srcVC4Sn | ((srcVC12Sn+1) << 5);
    if( srcVC4Sn < 0 || srcVC12Sn < 0 ) {
        regData = regAccess->readReg(regAddr);
        regData |= (1 << 11); //insert IDLE
    }
    regAccess->writeReg(regAddr, regData);
    if( switchPage() ) {
        regAddr = vc12RegAddr(destVC4Sn, destVC12Sn);
        regAccess->writeReg(regAddr, regData);
    }
    return 1;
}

bool ChipCP1121A::getLOS(int STMsn) {
    uint16 regData = regAccess->readReg(PRegSOP(STMsn, RRSALM));
    if( (regData >> 2) & 1 != 0 ) {
        return true;
    }
    return false;
}

bool ChipCP1121A::getLOF(int STMsn) {
    uint16 regData = regAccess->readReg(PRegSOP(STMsn, RRSALM));
    if( (regData >> 1) & 1 != 0 ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getOOF(int STMsn) {
    uint16 regData = regAccess->readReg(PRegSOP(STMsn, RRSALM));
    if( (regData >> 0) & 1 != 0 ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getMSAIS(int STMsn) {
    uint16 regData = regAccess->readReg(PRegSOP(STMsn, RMSALM));
    if( (regData >> 2) & 1 != 0 ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getMSRDI(int STMsn) {
    uint16 regData = regAccess->readReg(PRegSOP(STMsn, RMSALM));
    if( (regData >> 3) & 1 != 0 ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getMSREI(int STMsn) {
    return false;
}

uint32 ChipCP1121A::getB1(int sn) {
    uint16 high16 = regAccess->readReg(PRegSOP(sn, RRSBIPCH));
    uint16 low16 = regAccess->readReg(PRegSOP(sn, RRSBIPCL));
    return (high16 << 16) | low16;
}

uint32 ChipCP1121A::getB2(int sn) {
    uint16 high16 = regAccess->readReg(PRegSOP(sn, RMSBIPCH));
    uint16 low16 = regAccess->readReg(PRegSOP(sn, RMSBIPCL));
    return (high16 << 16) | low16;
}


/* private tool function */

bool ChipCP1121A::switchPage(void) {
    int page = currentPage();
    page ^= 1;
    switchPageTo(page);
    while( page != currentPage() ) {
		switchPageTo(page);
	}
    return true;
}
int ChipCP1121A::vc4RegAddr(int vc4sn) {
    if( currentPage() == 0 ) {
        return HLXCR_PG1 + vc4sn;
    }
    return HLXCR_PG0 + vc4sn;
}
int ChipCP1121A::vc12RegAddr(int vc4sn, int vc12sn) {
    if( currentPage() == 0 ) {
        return HLXCM_PG1 | (vc4sn << 7) | (vc12sn+1);
    }
	return HLXCM_PG0 | (vc4sn << 7) | (vc12sn+1);
}

int ChipCP1121A::currentPage(void) {
    return regAccess->readReg(HLXST);
}

void ChipCP1121A::switchPageTo(int page) {
    regAccess->writeReg(BHLXMCTL, (page<<1));
}

Chip_INIT_RESULT ChipCP1121A::ChipInit(void) {
    uint16 id = regAccess->readReg(ID);
    if( id != CP1121A_ID ) {
        id = regAccess->readReg(ID);
        if( id != CP1121A_ID ) {
            id = regAccess->readReg(ID);
            if( id != CP1121A_ID ) {
                return failed;
            }
        }
    }
    /* top level */
    if( ObjectReference::getOPTMode() ) {
        regAccess->writeReg(MCR, 0x58); // 77.76MHz mode, STM-1 mode, H12H4A, H12H4B
    }
    else {
        regAccess->writeReg(MCR, 0x59); // 77.76MHz mode, STM-4 mode, H12H4A, H12H4B
    }
    regAccess->writeReg(0x0006, 0x0781);
    regAccess->writeReg(0x0007, 0x1890); //0x1888
    id = regAccess->readReg(BHLXMCTL);
    id &= 0xfffe;
    regAccess->writeReg(BHLXMCTL, id); //the idle code type is all 0

    /* ��ʼ�������Ĵ��� */
    uint16 firstPage = 0;
    uint16 secondPage = 0;
    if( currentPage() == 0 ) {
        firstPage = HLXCM_PG1;
        secondPage = HLXCM_PG0;
    }
    else {
        firstPage = HLXCM_PG0;
        secondPage = HLXCM_PG1;
    }
    static int defultOH[] = {4,5,6,7,0,1,2,3,0,1,2,3,4,5,6,7,0,4};
    for( int i = 0; i < 18; i++ ) {
        regAccess->writeReg(firstPage+(i<<7), defultOH[i]);
        for( int j = 0; j < 63; j++ ) {
            uint16 regAddr = firstPage+(i<<7)+j+1;
            uint16 regValue = ((j+1)<<5) | i | (1<<11);
            regAccess->writeReg(regAddr, regValue);
        }
    }
    switchPage();
    for( int i = 0; i < 18; i++ ) {
        regAccess->writeReg(secondPage+(i<<7), defultOH[i]);
        for( int j = 0; j < 63; j++ ) {
            uint16 regAddr = secondPage+(i<<7)+j+1;
            uint16 regValue = ((j+1)<<5) | i | (1<<11);
            regAccess->writeReg(regAddr, regValue);
        }
    }



    /* ��ʼ������Ĵ��� */
    for(int i = 0; i < 18; i++ ) {

        for( int j = 0; j < 63; j++ ) {
            connectVC12(-1, -1, i, j);
        }
    }


    /* ��ʼ��MAP�Ĵ��� */
    for(int i = 0; i < 21; i++ ) {
        ITUT_T& t = TimeSlot2ITUT::itutFrom(i+1);
        uint16 regData = (t.tug3<<5) | (t.tug2 << 2) | t.tug1;
        regData |= (regData << 8);
        regAccess->writeReg(TUTSCFG+(i+1)*128, regData);
        regAccess->writeReg(CCR+(i+1)*128, 0x00f9);
        regAccess->writeReg(PPSCR+(i+1)*128, 0x0004);
        regAccess->writeReg(TV5K4LINA+(i+1)*128, 0x0004);
        regAccess->writeReg(TV5K4LINB+(i+1)*128, 0x0004);
        regAccess->writeReg(TJ2+(i+1)*128, 0x0089);
    }

    /* ��ʼ��oh�Ĵ��� */
    regAccess->writeReg(0x1480, 0xf010);
    regAccess->writeReg(0x1580, 0xf010);
    regAccess->writeReg(0x1680, 0xf010);
    regAccess->writeReg(0x1780, 0xf010);
    regAccess->writeReg(0x1c80, 0xf010);
    regAccess->writeReg(0x1d80, 0xf010);
    regAccess->writeReg(0x1e80, 0xf010);
    regAccess->writeReg(0x1f80, 0xf010);
    regAccess->writeReg(0x14d0, 0x0089);
    regAccess->writeReg(0x15d0, 0x0089);
    regAccess->writeReg(0x16d0, 0x0089);
    regAccess->writeReg(0x17d0, 0x0089);
    regAccess->writeReg(0x1cd0, 0x0089);
    regAccess->writeReg(0x1dd0, 0x0089);
    regAccess->writeReg(0x1ed0, 0x0089);
    regAccess->writeReg(0x1fd0, 0x0089);
    regAccess->writeReg(0x1482, 0x0002);
    regAccess->writeReg(0x1582, 0x0002);
    regAccess->writeReg(0x1682, 0x0002);
    regAccess->writeReg(0x1782, 0x0002);
    regAccess->writeReg(0x1c82, 0x0002);
    regAccess->writeReg(0x1d82, 0x0002);
    regAccess->writeReg(0x1e82, 0x0002);
    regAccess->writeReg(0x1f82, 0x0002);

    regAccess->writeReg(0x3101, 0x0020);
    regAccess->writeReg(0x3201, 0x0020);
    regAccess->writeReg(0x3301, 0x0020);
    regAccess->writeReg(0x3401, 0x0020);
    regAccess->writeReg(0x3501, 0x0020);
    regAccess->writeReg(0x3601, 0x0020);
    regAccess->writeReg(0x3701, 0x0020);
    regAccess->writeReg(0x3801, 0x0020);

    /*��ʼ��DCC�Ĵ���*/
    regAccess->writeReg(0x1020, 0x0000);
    regAccess->writeReg(0x1345, 0x3fee);
    regAccess->writeReg(0x1B45, 0x3fee);

    return succeed;
}


bool ChipCP1121A::getJ0T(int sn, uint8* j0) {
    if( j0 == 0 ) {
        return false;
    }
    for (int i = 0; i < 8; ++i) {
        uint16 temp = regAccess->readReg(PRegSOP(sn, TRSTRATM0) + i);
        j0[2*i] = (uint8)(temp & 0xff);
        j0[2*i + 1] = (uint8)(temp >> 8);
    }
    return true;
}

bool ChipCP1121A::getJ0E(int sn, uint8* j0) {
    if( j0 == 0 ) {
        return false;
    }
    for (int i = 0; i < 8; ++i) {
        uint16 temp = regAccess->readReg(PRegSOP(sn, RRSEXPTM0) + i);
        j0[2*i] = (uint8)(temp & 0xff);
        j0[2*i + 1] = (uint8)(temp >> 8);
    }
    return true;
}

bool ChipCP1121A::getJ0R(int sn, uint8* j0) {
    if( j0 == 0 ) {
        return false;
    }
    for (int i = 0; i < 8; ++i) {
        uint16 temp = regAccess->readReg(PRegSOP(sn, RRSRECTM0) + i);
        j0[2*i] = (uint8)(temp & 0xff);
        j0[2*i + 1] = (uint8)(temp >> 8);
    }
    return true;
}

bool ChipCP1121A::setJ0T(int sn, uint8* j0) {
    if( j0 == 0 ) {
        return false;
    }
    for (int i = 0; i < 8; ++i) {
        uint16 temp = (j0[2*i+1] << 8) | j0[2*i];
        regAccess->writeReg(PRegSOP(sn, TRSTRATM0+i), temp);
    }
    return true;
}

bool ChipCP1121A::setJ0E(int sn, uint8* j0) {
    if( j0 == 0 ) {
        return false;
    }
    for (int i = 0; i < 8; ++i) {
        uint16 temp = (j0[2*i+1] << 8) | j0[2*i];
        regAccess->writeReg(PRegSOP(sn, RRSEXPTM0+i), temp);
    }
    return true;

}

bool ChipCP1121A::setJ0LenTransmit(int sn, uint8 mode) { //0 singleByte; 1 16 bytes
    uint16 temp = regAccess->readReg(PRegSOP(sn, TRSCTL));
    temp &= ~(1 << 7);
    temp |= mode << 7;
    regAccess->writeReg(PRegSOP(sn, TRSCTL), temp);
    return true;
}

bool ChipCP1121A::setJ0LenExpected(int sn, uint8 mode) {
    uint16 temp = regAccess->readReg(PRegSOP(sn, RRSTMC));
    temp &= ~(1 << 0);
    temp |= mode << 0;
    regAccess->writeReg(PRegSOP(sn, RRSTMC), temp);
    return true;
}

bool ChipCP1121A::setSingleByteJ0T(int sn, uint8 j0) {
    uint16 temp = regAccess->readReg(PRegSOP(sn, TRSJ0));
    temp &= ~0xff;
    temp |= j0;
    regAccess->writeReg(PRegSOP(sn, TRSJ0), temp);
    return true;
}


uint32 ChipCP1121A::getB3(int sn) {
    uint16 high16 = regAccess->readReg(PRegSOPPath(sn, RPBIPCH));
    uint16 low16 = regAccess->readReg(PRegSOPPath(sn, RPBIPCL));
    return (high16 << 16) | low16;

}
bool ChipCP1121A::getJ1T(int sn, uint8* j1) {
    if( j1 == 0 ) {
        return false;
    }
    for (int i = 0; i < 32; ++i) {
        uint16 temp = regAccess->readReg(PRegSOPPath(sn, TPTRATM0) + i);
        j1[2*i] = (uint8)(temp & 0xff);
        j1[2*i + 1] = (uint8)(temp >> 8);
    }
    return true;
}
bool ChipCP1121A::getJ1E(int sn, uint8* j1) {
    if( j1 == 0 ) {
        return false;
    }
    for (int i = 0; i < 32; ++i) {
        uint16 temp = regAccess->readReg(PRegSOPPath(sn, RPEXPTM0) + i);
        j1[2*i] = (uint8)(temp & 0xff);
        j1[2*i + 1] = (uint8)(temp >> 8);
    }
    return true;

}
bool ChipCP1121A::getJ1R(int sn, uint8* j1) {
    if( j1 == 0 ) {
        return false;
    }
    for (int i = 0; i < 32; ++i) {
        uint16 temp = regAccess->readReg(PRegSOPPath(sn, RPRECTM0) + i);
        j1[2*i] = (uint8)(temp & 0xff);
        j1[2*i + 1] = (uint8)(temp >> 8);
    }
    return true;

}

bool ChipCP1121A::setJ1T(int sn, uint8* j1) {
    if( j1 == 0 ) {
        return false;
    }
    for (int i = 0; i < 32; ++i) {
        uint16 temp = (j1[2*i+1] << 8) | j1[2*i];
        regAccess->writeReg(PRegSOPPath(sn, TPTRATM0+i), temp);
    }
    return true;

}
bool ChipCP1121A::setJ1E(int sn, uint8* j1) {
    if( j1 == 0 ) {
        return false;
    }
    for (int i = 0; i < 32; ++i) {
        uint16 temp = (j1[2*i+1] << 8) | j1[2*i];
        regAccess->writeReg(PRegSOPPath(sn, RPEXPTM0+i), temp);
    }
    return true;


}

bool ChipCP1121A::setJ1LenTransmit(int sn, uint8 mode) { //0 singleByte; 1 16 bytes
    uint16 temp = regAccess->readReg(PRegSOPPath(sn, TPCTL));
    temp &= ~(1 << 7);
    temp |= mode << 7;
    regAccess->writeReg(PRegSOPPath(sn, TPCTL), temp);
    return true;
}
bool ChipCP1121A::setJ1LenExpected(int sn, uint8 mode) {
    uint16 temp = regAccess->readReg(PRegSOPPath(sn, RPTMC));
    temp &= ~(1 << 0);
    temp |= mode << 0;
    regAccess->writeReg(PRegSOPPath(sn, RPTMC), temp);
    return true;
}


bool ChipCP1121A::getAUAIS(int vc4) {
    uint16 temp = regAccess->readReg(PRegSOPPath(vc4, RPALM1));
    temp &= (1 << 4);
    if( temp ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getAULOP(int vc4) {
    uint16 temp = regAccess->readReg(PRegSOPPath(vc4, RPALM1));
    temp &= (1 << 3);
    if( temp ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getHPRDI(int vc4) {
    return false;

}
bool ChipCP1121A::getHPREI(int vc4) {
    return false;
}
bool ChipCP1121A::getHPTIM(int vc4) {
    uint16 temp = regAccess->readReg(PRegSOPPath(vc4, RPALM1));
    temp &= (1 << 0);
    if( temp ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getHPSLM(int vc4) {
    uint16 temp = regAccess->readReg(PRegSOPPath(vc4, RPALM1));
    temp &= (1 << 1);
    if( temp ) {
        return true;
    }
    return false;
}
bool ChipCP1121A::getHPUNEQ(int vc4) {
    uint16 temp = regAccess->readReg(PRegSOPPath(vc4, RPALM1));
    temp &= (1 << 5);
    if( temp ) {
        return true;
    }
    return false;

}
bool ChipCP1121A::setLoopOut(int sn, uint8 en) {
    uint16 temp = regAccess->readReg(CDRCTR);
    uint16 bitmask = (1 << 9);
    if( sn == 1 ) {
        bitmask = 1 << 10;
    }
    if( en == 1 ) {
        temp |= bitmask;
    }
    else {
        temp &= ~bitmask;
    }
    regAccess->writeReg(CDRCTR, temp);
    return true;
}
