/*
 * ChipEmuxLogic.cpp
 *
 *  Created on: 2015年6月3日
 *      Author: Administrator
 */

#include "ChipEmuxLogic.h"
#include "RegisterAccess.h"
#include "os.h"
#include <stdio.h>
#include "CPPTools.h"
#include "UID.h"

static const std::string chipName = "EmuxLogic";
static const int slotStbusHIDMapping[] = {0,0,8,9,10,11,12};

ChipEmuxLogic::ChipEmuxLogic(CBaseSlot* slot) : FPGAChip(chipName, slot, 0x2000) {
    // TODO Auto-generated constructor stub

}

ChipEmuxLogic::~ChipEmuxLogic() {
    // TODO Auto-generated destructor stub
}

std::string ChipEmuxLogic::GetChipVerInfo(const std::string ChipName,
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
std::string  ChipEmuxLogic::GetVerInfo() {
    return  (GetChipVerInfo("PCB-1:",REG_VER_CPLD_GENERALLOGIC_Z)).erase(10,2)+","\
            +GetChipVerInfo("CPLD-1:",REG_VER_CPLD_GENERALLOGIC_Z)+","\
            +(GetChipVerInfo("PCB-2:",REG_VER_CPLD_UOPTLOGIC)).erase(10,2)+","\
            +GetChipVerInfo("CPLD-2:",REG_VER_CPLD_UOPTLOGIC)+","\
            +GetChipVerInfo("FPGA-1:",REG_VER_FPGA_PCMLOGIC)+","\
            ;
}

Chip_INIT_RESULT ChipEmuxLogic::ChipInit(void) {
    Chip_INIT_RESULT rtn = updataFPGA();
    if( rtn == succeed ) {
        for( int i = 0; i < 16; i++ ) {
            for( int j = 0; j < 32; j++ ) {
                regAccess->writeReg( REG_64K_CROSS_BASE | (i<<6) | (j<<1) | 1, 0x80 );
            }
        }

        selectPCMClock(0);
        protectFSMStart();
    }
    return rtn;
}

void ChipEmuxLogic::protectFSMStart(void) {
    regAccess->writeReg(REG_FSM_Start, 1);
}

bool ChipEmuxLogic::CreatCrossConnection(uint32 toCh, uint32 toTs, uint32 fromCh, uint32 fromTs) {
    uint16 uiRegAddr = (toCh << 5) | toTs;
    if( toCh > 15 || fromCh > 15 || toTs > 31 || fromTs > 31 ) {
        return false;
    }
    regAccess->writeReg( (uiRegAddr << 1) | REG_64K_CROSS_BASE, fromTs);
    regAccess->writeReg( (uiRegAddr << 1) | 1 | REG_64K_CROSS_BASE, fromCh );
    return true;
}


bool ChipEmuxLogic::RemoveCrossConnection(uint32 Ch, uint32 Ts) {
    uint16 uiRegAddr = (Ch << 5) | Ts;
    if( Ch > 15 || Ts > 31 ) {
        return false;
    }
    regAccess->writeReg( (uiRegAddr << 1) | 1 | REG_64K_CROSS_BASE, 0x80 );
    return true;
}

bool ChipEmuxLogic::itsLOS(int e1) {
    if( e1 < 0 || e1 > 4 ) {
        return false;
    }
    uint16 los = regAccess->readReg(REG_E1_LOS);
    los &= (1 << e1 );
    return los == 0;
}

bool ChipEmuxLogic::itsAIS(int e1) {
    if( e1 < 0 || e1 > 4 ) {
        return false;
    }
    uint16 ais = regAccess->readReg(REG_E1_AIS);
    ais &= (1 << e1 );
    return ais != 0;
}

bool ChipEmuxLogic::itsLOF(int e1) {
    uint16 alm = regAccess->readReg(REG_E1_ALM_BASE+e1);
    return (alm & (1 << 4)) == 0;
}

bool ChipEmuxLogic::itsLOMF(int e1) {
    uint16 alm = regAccess->readReg(REG_E1_ALM_BASE+e1);
    return (alm & (1 << 2)) != 0;
}

uint16 ChipEmuxLogic::getHID(uint32 uid) {
    UN_Info info = UID::breakUID(uid);
    if( info.ts.slot == 0 || info.ts.slot == 1 ) {
        return (info.ts.E1 << 8) | (info.ts.TS);
    }
    return (slotStbusHIDMapping[info.ts.slot] << 8) | info.ts.TS;
}


void ChipEmuxLogic::selectPCMClock(uint8 src) {
    if( src == 0 ) {
        regAccess->writeReg(REG_PCM_CLOCK_SEL, 0x80);
    }
    else if( src < 9 ) {
        regAccess->writeReg(REG_PCM_CLOCK_SEL, src-1);
    }
}
void ChipEmuxLogic::setPortLoopOut(uint8 ch, uint8 loop){
    uint16 temp = 0;
    temp = regAccess->readReg(REG_LOOP_OUTER);//out_loop
    temp &=~ (1 << ch);
    temp |=  (loop << ch);
    regAccess->writeReg(REG_LOOP_OUTER, temp);
}
void ChipEmuxLogic::setPortLoopIn(uint8 ch, uint8 loop){
    uint16 temp = 0;
    temp = regAccess->readReg(REG_LOOP_INNER);//in_loop
    temp &=~ (1 << ch);
    temp |=  (loop << ch);
    regAccess->writeReg(REG_LOOP_INNER, temp);
}

bool ChipEmuxLogic::ifSaHavePacket(void) {
    uint16 temp = regAccess->readReg(REG_SABIT_R_STA);
    if( temp & 1 ) {
        return true;
    }
    return false;
}
uint8 ChipEmuxLogic::getSourceCh(void) {
    return regAccess->readReg(REG_SABIT_R_CH);
}
int ChipEmuxLogic::getSaPacketLen(void) {
    return regAccess->readReg(REG_SABIT_R_LEN);
}
bool ChipEmuxLogic::getSaPacket(uint8* buff, uint16 len, uint16 startPos) {
    for (int i = 0; i < len; ++i) {
        buff[i] = (uint8)regAccess->readReg(REG_SABIT_R_BUF+i+startPos);
    }
    return true;
}
void ChipEmuxLogic::readSaPacketOver(void) {
    regAccess->writeReg(REG_SABIT_R_OVER, 0x46, 0);
}

void ChipEmuxLogic::sendSaPacket(uint8 ch, uint8* data, uint16 len) {
    if( len > 255 ) {
#ifdef EZ_DEBUG
        printf("\n!!!Packet too long at ch-%d!!!\n", ch+1);
#endif
        return;
    }
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


void ChipEmuxLogic::turnOnLedWork(uint8 sn, bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << (4+sn) );
    }
    else {
        temp |= ( 1 << (4+sn) );
    }
    regAccess->writeReg(LED, temp);
}

void ChipEmuxLogic::turnOnLedAlm(uint8 sn, bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << (8+sn) );
    }
    else {
        temp |= ( 1 << (8+sn) );
    }
    regAccess->writeReg(LED, temp);
}

void ChipEmuxLogic::turnOnLedMaj(bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << 0 );
    }
    else {
        temp |= ( 1 << 0 );
    }
    regAccess->writeReg(LED, temp);
}
void ChipEmuxLogic::turnOnLedMin(bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << 1 );
    }
    else {
        temp |= ( 1 << 1 );
    }
    regAccess->writeReg(LED, temp);
}

void ChipEmuxLogic::turnOnledWorking(bool on) {
    uint16 temp = regAccess->readReg(LED);
    if( on ) {
        temp &= ~( 1 << 15 );
    }
    else {
        temp |= ( 1 << 15 );
    }
    regAccess->writeReg(LED, temp);
}

void ChipEmuxLogic::sabitInterruptEnable(bool en) {
    uint16 regData = (en ? 1: 0);
    regAccess->writeReg(REG_INTRR_EN, regData);
}

void ChipEmuxLogic::resetRemote(uint8 port) {
    uint16 temp = regAccess->readReg(REG_REMOTE_RESET);
    temp ^= (1 << port);
    regAccess->writeReg(REG_REMOTE_RESET, temp);
}
