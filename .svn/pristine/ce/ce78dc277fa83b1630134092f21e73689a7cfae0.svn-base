/*
 * DriverTrib4STM1.cpp
 *
 *  Created on: 2014��8��12��
 *      Author: Administrator
 */


#include "DriverTrib4STM1.h"
#include "ChipRC7883.h"
#include "Chip8STM1Logic1.h"
#include "Chip8STM1Logic2.h"

DriverTrib4STM1::DriverTrib4STM1(ChipRC7883& rc78831, ChipRC7883& rc78832, Chip8STM1Logic1& stmlogic1, Chip8STM1Logic2& stmlogic2)
    : chip1(rc78831), chip2(rc78832), fpga1(stmlogic1), fpga2(stmlogic2) {
    // TODO Auto-generated constructor stub

}

DriverTrib4STM1::~DriverTrib4STM1() {
    // TODO Auto-generated destructor stub
}

int DriverTrib4STM1::connectVC4(int srcSn, uint32 destSn) {
    return -1;
}
int DriverTrib4STM1::connectVC12(int srcVC4Sn, int srcVC12Sn, uint32 destVC4Sn, uint32 destVC12Sn) {
    if( destVC4Sn == 0 || destVC4Sn == 1 ) {

        if( srcVC4Sn < 0 || srcVC12Sn < 0 ) {
            return fpga1.sdhBusSel(destVC4Sn, destVC12Sn, 0);
        }
        return fpga1.sdhBusSel(destVC4Sn, destVC12Sn, ((srcVC4Sn-2) / 2) | 4);
    }
    return 1;
}

bool DriverTrib4STM1::getLOS(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.getLOS(STMsn % 2);
    }
    return chip1.getLOS(STMsn % 2);
}

bool DriverTrib4STM1::getLOF(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.getLOF(STMsn % 2);
    }
    return chip1.getLOF(STMsn % 2);
}
bool DriverTrib4STM1::getOOF(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.getOOF(STMsn % 2);
    }
    return chip1.getOOF(STMsn % 2);
}
bool DriverTrib4STM1::getMSAIS(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.getMSAIS(STMsn % 2);
    }
    return chip1.getMSAIS(STMsn % 2);
}
bool DriverTrib4STM1::getMSRDI(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.getMSRDI(STMsn % 2);
    }
    return chip1.getMSRDI(STMsn % 2);
}
bool DriverTrib4STM1::getMSREI(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.getMSREI(STMsn % 2);
    }
    return chip1.getMSREI(STMsn % 2);
}


uint32 DriverTrib4STM1::getB1(int sn) {
    if( sn / 2 ) {
        return chip2.getB1(sn % 2);
    }
    return chip1.getB1(sn % 2);
}
uint32 DriverTrib4STM1::getB2(int sn) {
    if( sn / 2 ) {
        return chip2.getB2(sn % 2);
    }
    return chip1.getB2(sn % 2);
}
bool DriverTrib4STM1::getJ0T(int sn, uint8* j0) {
    if( sn / 2 ) {
        return chip2.getJ0T(sn % 2, j0);
    }
    return chip1.getJ0T(sn % 2, j0);
}
bool DriverTrib4STM1::getJ0E(int sn, uint8* j0) {
    if( sn / 2 ) {
        return chip2.getJ0E(sn % 2, j0);
    }
    return chip1.getJ0E(sn % 2, j0);
}
bool DriverTrib4STM1::getJ0R(int sn, uint8* j0) {
    if( sn / 2 ) {
        return chip2.getJ0R(sn % 2, j0);
    }
    return chip1.getJ0R(sn % 2, j0);
}

bool DriverTrib4STM1::setJ0T(int sn, uint8* j0) {
    if( sn / 2 ) {
        return chip2.getJ0T(sn % 2, j0);
    }
    return chip1.getJ0T(sn % 2, j0);
}
bool DriverTrib4STM1::setJ0E(int sn, uint8* j0) {
    if( sn / 2 ) {
        return chip2.getJ0E(sn % 2, j0);
    }
    return chip1.getJ0E(sn % 2, j0);
}

bool DriverTrib4STM1::setJ0LenTransmit(int sn, uint8 mode) { //0 singleByte; 1 16 bytes
    if( sn / 2 ) {
        return chip2.setJ0LenTransmit(sn % 2, mode);
    }
    return chip1.setJ0LenTransmit(sn % 2, mode);
}
bool DriverTrib4STM1::setJ0LenExpected(int sn, uint8 mode) {
    if( sn / 2 ) {
        return chip2.setJ0LenExpected(sn % 2, mode);
    }
    return chip1.setJ0LenExpected(sn % 2, mode);
}

bool DriverTrib4STM1::setSingleByteJ0T(int sn, uint8 j0) {
    if( sn / 2 ) {
        return chip2.setSingleByteJ0T(sn % 2, j0);
    }
    return chip1.setSingleByteJ0T(sn % 2, j0);
}


uint32 DriverTrib4STM1::getB3(int sn) {
    if( sn / 2 ) {
        return chip2.getB3(sn % 2);
    }
    return chip1.getB3(sn % 2);
}
bool DriverTrib4STM1::getJ1T(int sn, uint8* j1) {
    if( sn / 2 ) {
        return chip2.getJ1T(sn % 2, j1);
    }
    return chip1.getJ1T(sn % 2, j1);
}
bool DriverTrib4STM1::getJ1E(int sn, uint8* j1) {
    if( sn / 2 ) {
        return chip2.getJ1E(sn % 2, j1);
    }
    return chip1.getJ1E(sn % 2, j1);
}
bool DriverTrib4STM1::getJ1R(int sn, uint8* j1) {
    if( sn / 2 ) {
        return chip2.getJ1R(sn % 2, j1);
    }
    return chip1.getJ1R(sn % 2, j1);
}

bool DriverTrib4STM1::setJ1T(int sn, uint8* j1) {
    if( sn / 2 ) {
        return chip2.setJ1T(sn % 2, j1);
    }
    return chip1.setJ1T(sn % 2, j1);
}
bool DriverTrib4STM1::setJ1E(int sn, uint8* j1) {
    if( sn / 2 ) {
        return chip2.setJ1E(sn % 2, j1);
    }
    return chip1.setJ1E(sn % 2, j1);
}

bool DriverTrib4STM1::setJ1LenTransmit(int sn, uint8 mode) { //0 singleByte; 1 16 bytes
    if( sn / 2 ) {
        return chip2.setJ1LenTransmit(sn % 2, mode);
    }
    return chip1.setJ1LenTransmit(sn % 2, mode);
}
bool DriverTrib4STM1::setJ1LenExpected(int sn, uint8 mode) {
    if( sn / 2 ) {
        return chip2.setJ1LenExpected(sn % 2, mode);
    }
    return chip1.setJ1LenExpected(sn % 2, mode);
}

bool DriverTrib4STM1::setDCCOH(int ch, uint16 data) {
    return fpga2.setDCCOH(ch, data);
}

bool DriverTrib4STM1::getAUAIS(int vc4) {
    if( vc4 / 2 ) {
        return chip2.getAUAIS(vc4 % 2);
    }
    return chip1.getAUAIS(vc4 % 2);
}
bool DriverTrib4STM1::getAULOP(int vc4) {
    if( vc4 / 2 ) {
        return chip2.getAULOP(vc4 % 2);
    }
    return chip1.getAULOP(vc4 % 2);

}
bool DriverTrib4STM1::getHPRDI(int vc4) {
    if( vc4 / 2 ) {
        return chip2.getHPRDI(vc4 % 2);
    }
    return chip1.getHPRDI(vc4 % 2);
}
bool DriverTrib4STM1::getHPREI(int vc4) {
    if( vc4 / 2 ) {
        return chip2.getHPREI(vc4 % 2);
    }
    return chip1.getHPREI(vc4 % 2);
}
bool DriverTrib4STM1::getHPTIM(int vc4) {
    if( vc4 / 2 ) {
        return chip2.getHPTIM(vc4 % 2);
    }
    return chip1.getHPTIM(vc4 % 2);
}
bool DriverTrib4STM1::getHPSLM(int vc4) {
    if( vc4 / 2 ) {
        return chip2.getHPSLM(vc4 % 2);
    }
    return chip1.getHPSLM(vc4 % 2);
}
bool DriverTrib4STM1::getHPUNEQ(int vc4) {
    if( vc4 / 2 ) {
        return chip2.getHPUNEQ(vc4 % 2);
    }
    return chip1.getHPUNEQ(vc4 % 2);
}

bool DriverTrib4STM1::setSTMPortTxEn(int STMsn, uint8 en) {
    return true;
}
bool DriverTrib4STM1::setSTMAlsEn(int STMsn, uint8 en) {
    return true;
}

bool DriverTrib4STM1::setLoopInOnly(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.setPortLoopInOnly(STMsn % 2);
    }
    return chip1.setPortLoopInOnly(STMsn % 2);
}
bool DriverTrib4STM1::setLoopOutOnly(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.setPortLoopOutOnly(STMsn % 2);
    }
    return chip1.setPortLoopOutOnly(STMsn % 2);
}
bool DriverTrib4STM1::setLoopInAndOut(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.setPortLoopOutAndIn(STMsn % 2);
    }
    return chip1.setPortLoopOutAndIn(STMsn % 2);
}
bool DriverTrib4STM1::setLoopClear(int STMsn) {
    if( STMsn / 2 ) {
        return chip2.setPortLoopClear(STMsn % 2);
    }
    return chip1.setPortLoopClear(STMsn % 2);
}
