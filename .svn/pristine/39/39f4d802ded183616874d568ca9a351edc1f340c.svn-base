/*
 * DriverSDHXc.cpp
 *
 *  Created on: 2014-5-17
 *      Author: Administrator
 */

#include "DriverSDHXc.h"
#include "ChipCP1121A.h"
#include "DriverPCM.h"
#include "ChipUOPTLogic.h"

DriverSDHXc::DriverSDHXc(ChipCP1121A& chiSdh, DriverPCM& chipfpga, ChipUOPTLogic& chipUoptLogic)
        : sdh(chiSdh), fpga(chipfpga), cpld(chipUoptLogic) {

}

DriverSDHXc::~DriverSDHXc() {

}

int DriverSDHXc::connectVC4(int srcSn, uint32 destSn) {
    return sdh.connectVC4(srcSn, destSn);
}
int DriverSDHXc::connectVC12(int srcVC4Sn, int srcVC12Sn, uint32 destVC4Sn, uint32 destVC12Sn) {
    return sdh.connectVC12(srcVC4Sn, srcVC12Sn, destVC4Sn, destVC12Sn);
}

bool DriverSDHXc::getLOS(int STMsn) {
    return sdh.getLOS(STMsn) || cpld.ifSFPLos(STMsn);
}

bool DriverSDHXc::getLOF(int STMsn) {
    return sdh.getLOF(STMsn);
}
bool DriverSDHXc::getOOF(int STMsn) {
    return sdh.getOOF(STMsn);
}
bool DriverSDHXc::getMSAIS(int STMsn) {
    return sdh.getMSAIS(STMsn);
}
bool DriverSDHXc::getMSRDI(int STMsn) {
    return sdh.getMSRDI(STMsn);
}
bool DriverSDHXc::getMSREI(int STMsn) {
    return sdh.getMSREI(STMsn);
}



uint32 DriverSDHXc::getB1(int sn) {
    return sdh.getB1(sn);
}
uint32 DriverSDHXc::getB2(int sn) {
    return sdh.getB2(sn);
}
bool DriverSDHXc::getJ0T(int sn, uint8* j0) {
    return sdh.getJ0T(sn, j0);
}
bool DriverSDHXc::getJ0E(int sn, uint8* j0) {
    return sdh.getJ0E(sn, j0);
}
bool DriverSDHXc::getJ0R(int sn, uint8* j0) {
    return sdh.getJ0R(sn, j0);
}

bool DriverSDHXc::setJ0T(int sn, uint8* j0) {
    return sdh.setJ0T(sn, j0);
}
bool DriverSDHXc::setJ0E(int sn, uint8* j0) {
    return sdh.setJ0E(sn, j0);
}

bool DriverSDHXc::setJ0LenTransmit(int sn, uint8 mode) { //0 singleByte; 1 16 bytes
    return sdh.setJ0LenTransmit(sn, mode);
}
bool DriverSDHXc::setJ0LenExpected(int sn, uint8 mode) {
    return sdh.setJ0LenExpected(sn, mode);
}

bool DriverSDHXc::setSingleByteJ0T(int sn, uint8 j0) {
    return sdh.setSingleByteJ0T(sn, j0);
}


uint32 DriverSDHXc::getB3(int sn) {
    return sdh.getB3(sn);
}
bool DriverSDHXc::getJ1T(int sn, uint8* j1) {
    return sdh.getJ1T(sn, j1);
}
bool DriverSDHXc::getJ1E(int sn, uint8* j1) {
    return sdh.getJ1E(sn, j1);
}
bool DriverSDHXc::getJ1R(int sn, uint8* j1) {
    return sdh.getJ1R(sn, j1);
}

bool DriverSDHXc::setJ1T(int sn, uint8* j1) {
    return sdh.setJ1T(sn, j1);
}
bool DriverSDHXc::setJ1E(int sn, uint8* j1) {
    return sdh.setJ1E(sn, j1);
}

bool DriverSDHXc::setJ1LenTransmit(int sn, uint8 mode) { //0 singleByte; 1 16 bytes
    return sdh.setJ1LenTransmit(sn, mode);
}
bool DriverSDHXc::setJ1LenExpected(int sn, uint8 mode) {
    return sdh.setJ1LenExpected(sn, mode);
}

bool DriverSDHXc::setDCCOH(int ch, uint16 data) {
    return fpga.setDCCOH(ch, data);
}

bool DriverSDHXc::getAUAIS(int vc4) {
    return sdh.getAUAIS(vc4);
}
bool DriverSDHXc::getAULOP(int vc4) {
    return sdh.getAULOP(vc4);
}
bool DriverSDHXc::getHPRDI(int vc4) {
    return sdh.getHPRDI(vc4);
}
bool DriverSDHXc::getHPREI(int vc4) {
    return sdh.getHPREI(vc4);
}
bool DriverSDHXc::getHPTIM(int vc4) {
    return sdh.getHPTIM(vc4);
}
bool DriverSDHXc::getHPSLM(int vc4) {
    return sdh.getHPSLM(vc4);
}
bool DriverSDHXc::getHPUNEQ(int vc4) {
    return sdh.getHPUNEQ(vc4);
}
bool DriverSDHXc::setSTMPortTxEn(int STMsn, uint8 en) {
    cpld.setSFPTxDisable(STMsn, !en);
    return true;
}
bool DriverSDHXc::setSTMAlsEn(int STMsn, uint8 en) {
    return true;
}

bool DriverSDHXc::setLoopInOnly(int STMsn) {
    return false;
}
bool DriverSDHXc::setLoopOutOnly(int STMsn) {
    return sdh.setLoopOut(STMsn, 1);
}
bool DriverSDHXc::setLoopInAndOut(int STMsn) {
    return sdh.setLoopOut(STMsn, 1);
}
bool DriverSDHXc::setLoopClear(int STMsn) {
    return sdh.setLoopOut(STMsn, 0);
}
