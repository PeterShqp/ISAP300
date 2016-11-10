/*
 * ChipDXCLogic.cpp
 *
 *  Created on: 2015年6月15日
 *      Author: Administrator
 */

#include "ChipDXCLogic.h"
#include "RegisterAccess.h"
#include "CPPTools.h"
#include "UID.h"
#include "os.h"
#include <stdio.h>


static const std::string chipName = "DXCLogic";
static const uint8 slotStbusHIDMapping[] = {0, 0, 16, 17, 18, 19, 20};
static const uint8 slotExtStbusHIDBaseMapping[] = {0, 0, 48, 64, 80, 96, 112};

ChipDXCLogic::ChipDXCLogic(CBaseSlot* slot) : FPGAChip(chipName, slot, 0x2000){
    // TODO Auto-generated constructor stub

}

ChipDXCLogic::~ChipDXCLogic() {
    // TODO Auto-generated destructor stub
}


std::string ChipDXCLogic::GetChipVerInfo(const std::string ChipName,
        const uint16 Reg_Ver_Addr) {
    if (Reg_Ver_Addr != 0x0011)
        ChipVerInfo = ChipName + "V"
                + CPPTools::number2string(regAccess->readReg(Reg_Ver_Addr) >> 12 & 0xf)
                + "."
                + CPPTools::number2string(regAccess->readReg(Reg_Ver_Addr) >> 8 & 0x7)
                + "."
                + CPPTools::number2string(regAccess->readReg(Reg_Ver_Addr) & 0xff);
    else if (Reg_Ver_Addr == 0x0011)
        ChipVerInfo = ChipName + "V"
                + CPPTools::number2string(
                        (*(uint32*) (0xe2000000 + Reg_Ver_Addr - 1)) >> 4 & 0xf)
                + "."\

                + CPPTools::number2string(
                        (*(uint32*) (0xe2000000 + Reg_Ver_Addr - 1)) & 0xf)
                + "."\

                + CPPTools::number2string(
                        (*(uint32*) (0xe2000000 + Reg_Ver_Addr)) & 0xff);
    return ChipVerInfo;
}

std::string  ChipDXCLogic::GetVerInfo() {
    return  (GetChipVerInfo("PCB-1:",REG_VER_CPLD_GENERALLOGIC_Z)).erase(10,2)+","\
            +GetChipVerInfo("CPLD-1:",REG_VER_CPLD_GENERALLOGIC_Z)+","\
            +(GetChipVerInfo("PCB-2:",REG_VER_CPLD_UOPTLOGIC)).erase(10,2)+","\
            +GetChipVerInfo("CPLD-2:",REG_VER_CPLD_UOPTLOGIC)+","\
            +GetChipVerInfo("FPGA-1:",VER)+","\
            ;
}

Chip_INIT_RESULT ChipDXCLogic::ChipInit(void) {
    Chip_INIT_RESULT rtn = updataFPGA();
    if( rtn == succeed ) {
        uint8 stbusnumber = 64;
//        if( regAccess->readReg(VER) < 0x100a ) {
//            stbusnumber = 128;
//        }
        for( int i = 0; i < stbusnumber; i++ ) {
            for( int j = 0; j < 32; j++ ) {
                uint16 reg = getCrossRegAddr(i,j);
                regAccess->writeReg( REG_64K_CROSS_BASE | reg, reg );
            }
        }

        selectPCMClock(0);
        regAccess->writeReg(REG_PCM_CLOCK_START, 0x00, 0); //start pcm clock generator
        protectFSMStart();
    }
    return rtn;
}

void ChipDXCLogic::selectPCMClock(uint8 src) {
    if( src == 0 ) {
        regAccess->writeReg(REG_PCM_CLOCK_SEL, 0x80);
    }
    else if( src < 9 ) {
        regAccess->writeReg(REG_PCM_CLOCK_SEL, src-1);
    }
}

void ChipDXCLogic::protectFSMStart(void) {
    regAccess->writeReg(REG_FSM_Start, 1);
}

void ChipDXCLogic::setSabitInterruptEnable(uint8 ch, uint8 en) {
    uint16 regV = regAccess->readReg(REG_SABIT_INTRR_EN);
    regV &= ~(1<<ch);
    regV |= (en << ch);
    regAccess->writeReg(REG_SABIT_INTRR_EN, regV);
}

bool ChipDXCLogic::ifSaHavePacket(void) {
    uint16 temp = regAccess->readReg(REG_SABIT_R_STA);
    if( temp & 1 ) {
        return true;
    }
    return false;
}
uint8 ChipDXCLogic::getSourceCh(void) {
    return regAccess->readReg(REG_SABIT_R_CH);
}
int ChipDXCLogic::getSaPacketLen(void) {
    return regAccess->readReg(REG_SABIT_R_LEN);
}
bool ChipDXCLogic::getSaPacket(uint8* buff, uint16 len, uint16 startPos) {
    for (int i = 0; i < len; ++i) {
        buff[i] = (uint8)regAccess->readReg(REG_SABIT_R_BUF+i+startPos);
    }
    return true;
}
void ChipDXCLogic::readSaPacketOver(void) {
    regAccess->writeReg(REG_SABIT_R_OVER, 0x46, 0);
}

void ChipDXCLogic::sendSaPacket(uint8 ch, uint8* data, uint16 len) {
    if( itsLOS(ch) ) {
        return;
    }
    uint8 chmask = 1 << ch;
    for (int i = 0; i < 20; ++i) {
//        if( (regAccess->readReg(REG_SABIT_T_STA)&1) == 1 ) {
            if( (regAccess->readReg(REG_SABIT_T_CH_STA) & chmask) != 0 ) {
                break;
            }
//        }
        os_dly_wait(1);
        if( i == 19 ) {
#ifdef EZ_DEBUG
            printf("\n!!! sabit channel-%d busy!!!\n", ch+1);
#endif
            return;
        }
    }
#ifdef SW_DEBUG
    printf("\nsabit start send at ch:%d, len:%d, ticks:%d\n", ch, len, os_time_get());
#endif
    regAccess->writeReg(REG_SABIT_T_CH, ch);
    regAccess->writeReg(REG_SABIT_T_LEN, len, 0);
    for (int i = 0; i < len; ++i) {
        regAccess->writeReg(REG_SABIT_T_BUF+i, data[i], 0);
    }
    regAccess->writeReg(REG_SABIT_T_OVER, 0x46, 0);
#ifdef SW_DEBUG
    printf("\nsabit send over! ticks:%d\n", os_time_get());
#endif
}


bool ChipDXCLogic::CreatCrossConnection(uint32 toCh, uint32 toTs, uint32 fromCh, uint32 fromTs) {
    uint16 toReg = getCrossRegAddr(toCh, toTs);
    uint16 fromValue = getCrossRegAddr(fromCh, fromTs);

    regAccess->writeReg(REG_64K_CROSS_BASE|toReg, fromValue);
    return true;
}
bool ChipDXCLogic::RemoveCrossConnection(uint32 Ch, uint32 Ts) {
    uint16 toReg = getCrossRegAddr(Ch, Ts);
    regAccess->writeReg(REG_64K_CROSS_BASE|toReg, toReg);
	return true;
}

uint16 ChipDXCLogic::getHID(uint32 uid) {
    UN_Info info = UID::breakUID(uid);
    if( info.ts.slot == 0 || info.ts.slot == 1 ) {
        return (info.ts.E1 << 8) | (info.ts.TS);
    }
    else if( info.ts.E1 == 0 ) {
        return (slotStbusHIDMapping[info.ts.slot] << 8) | info.ts.TS;
    }
    else {
        return ((slotExtStbusHIDBaseMapping[info.ts.slot] + info.ts.E1 - 1) << 8) | info.ts.TS;
    }
}

bool ChipDXCLogic::itsLOS(int e1) {
    uint16 reg = getE1RegAddr(e1) | REG_E1_ALARM_OFFSET;
    uint16 regvalue = regAccess->readReg(reg);
    return (regvalue & (1<<0)) == 0;
}
bool ChipDXCLogic::itsAIS(int e1) {
    uint16 reg = getE1RegAddr(e1) | REG_E1_ALARM_OFFSET;
    uint16 regvalue = regAccess->readReg(reg);
    return (regvalue & (1<<1)) != 0;
}
bool ChipDXCLogic::itsLOF(int e1) {
    uint16 reg = getE1RegAddr(e1) | REG_E1_ALARM_OFFSET;
    uint16 regvalue = regAccess->readReg(reg);
    return (regvalue & (1<<2)) == 0;
}
bool ChipDXCLogic::itsLOMF(int e1) {
    uint16 reg = getE1RegAddr(e1) | REG_E1_ALARM_OFFSET;
    uint16 regvalue = regAccess->readReg(reg);
    return (regvalue & (1<<3)) != 0;
}

void ChipDXCLogic::turnOnLedWork(uint8 sn, bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << (4+sn) );
    }
    else {
        temp |= ( 1 << (4+sn) );
    }
    regAccess->writeReg(LED, temp);
}

void ChipDXCLogic::turnOnLedAlm(uint8 sn, bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << (8+sn) );
    }
    else {
        temp |= ( 1 << (8+sn) );
    }
    regAccess->writeReg(LED, temp);
}

void ChipDXCLogic::turnOnLedMaj(bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << 0 );
    }
    else {
        temp |= ( 1 << 0 );
    }
    regAccess->writeReg(LED, temp);
}
void ChipDXCLogic::turnOnLedMin(bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << 1 );
    }
    else {
        temp |= ( 1 << 1 );
    }
    regAccess->writeReg(LED, temp);
}

void ChipDXCLogic::turnOnledWorking(bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << 15 );
    }
    else {
        temp |= ( 1 << 15 );
    }
    regAccess->writeReg(LED, temp);
}

void ChipDXCLogic::sabitInterruptEnable(bool en) {
    uint16 regData = (en ? 1: 0);
    regAccess->writeReg(REG_INTRR_EN, regData);
}

void ChipDXCLogic::setPortLoopOut(uint8 ch, uint8 loop){
    regAccess->writeReg( getE1RegAddr(ch)+REG_E1_LOOPOUT_OFFSET, loop);
}
void ChipDXCLogic::setPortLoopIn(uint8 ch, uint8 loop){

    regAccess->writeReg( getE1RegAddr(ch)+REG_E1_LOOPIN_OFFSET, loop);
}

void ChipDXCLogic::resetRemote(uint8 port) {
    uint16 regvalue = regAccess->readReg( getE1RegAddr(port)+REG_E1_CLOSE );
    regvalue ^= (1<<15);
    regAccess->writeReg(getE1RegAddr(port)+REG_E1_CLOSE, regvalue);
}

void ChipDXCLogic::setPortEnable(uint8 port, uint8 en) {
    uint16 regvalue = regAccess->readReg( getE1RegAddr(port)+REG_E1_CLOSE );
    regvalue |= 1;
    regvalue ^= en;
    regAccess->writeReg(getE1RegAddr(port)+REG_E1_CLOSE, regvalue, 1, 0x8001);
}


void ChipDXCLogic::offHstbus(uint8 extslot) {
    uint16 regV = regAccess->readReg(REG_HSTBUS_SWITCH);
    regV &= ~(1 << extslot);
    regAccess->writeReg(REG_HSTBUS_SWITCH, regV);
}

void ChipDXCLogic::onHstbus(uint8 extslot) {
    uint16 regV = regAccess->readReg(REG_HSTBUS_SWITCH);
    regV |= (1 << extslot);
    regAccess->writeReg(REG_HSTBUS_SWITCH, regV);
}

void ChipDXCLogic::setDcnInterruptEnable(uint8 ch, uint8 en) {
    uint16 regV = regAccess->readReg(REG_DCN_INTRR_EN);
    regV &= ~(1<<ch);
    regV |= (en << ch);
    regAccess->writeReg(REG_DCN_INTRR_EN, regV);
}

bool ChipDXCLogic::selectDcnTs(uint8 ch, uint32 tsmap) {
    regAccess->writeReg(REG_DCN_TS_SEL_L(ch), tsmap & 0xffff);
    regAccess->writeReg(REG_DCN_TS_SEL_H(ch), tsmap >> 16);
    return true;
}

uint32 ChipDXCLogic::getDcnTsMap(uint8 ch) {
    return (regAccess->readReg(REG_DCN_TS_SEL_H(ch)) << 16) | regAccess->readReg(REG_DCN_TS_SEL_L(ch));
}
/*
 * DCN 收包buff里包括了长度字节，需要先把长度字节读出来，后续才是载荷；
 * 因为长度字节的值，包含自身的2字节长度。因此收包时，真实的包长度为长度字节值-2；
 */
bool ChipDXCLogic::ifDcnHavePacket(uint8 ch) {
    uint16 regv = regAccess->readReg(REG_DCN_R_STA);
    if( (regv & ( 1 << ch )) != 0 ) {
        return true;
    }
    return false;
}
int  ChipDXCLogic::getDcnPacketLen(uint8 ch) {
    uint16 regv = regAccess->readReg(REG_DCN_R_LEN(ch));
    return regv-2;

}
bool ChipDXCLogic::getDcnPacket(uint8 ch, uint8* buff, uint16 len) {
    for (int i = 0; i < 2; ++i) {
        //gap length bytes
        regAccess->readReg(REG_DCN_R_BUF(ch));
    }
    for (int i = 0; i < len; ++i) {
        buff[i] = regAccess->readReg(REG_DCN_R_BUF(ch));
    }
    return true;
}
void ChipDXCLogic::readDcnPacketOver(uint8 ch) {
    uint16 regv = regAccess->readReg(REG_DCN_R_OVER);
    regv ^= (1<<ch);
    regAccess->writeReg(REG_DCN_R_OVER, regv);
}
void ChipDXCLogic::sendDcnPacket(uint8 ch, uint8* data, uint16 len) {
    uint8 retryNum = 20;
    while( retryNum-- ) {
        uint16 sta = regAccess->readReg(REG_DCN_T_STA);
        if( ((sta >> ch) & 1) != 0 ) {
            regAccess->writeReg(REG_DCN_T_BUF(ch), (len+2) >> 8, 0);
            regAccess->writeReg(REG_DCN_T_BUF(ch), (len+2) & 0xff, 0);
            for (int i = 0; i < len; ++i) {
                regAccess->writeReg(REG_DCN_T_BUF(ch), data[i], 0);
            }
            uint16 regV = regAccess->readReg(REG_DCN_T_OVER);
            regV ^= (1 << ch);
            regAccess->writeReg(REG_DCN_T_OVER, regV);
            return;
        }
        os_dly_wait(1);
    }
#ifdef SW_DEBUG
    FILE* f = fopen("macport.txt", "a");
    fprintf(f, "\n!!!dcn ch-%d is busy!!!\n", ch);
#endif
}

