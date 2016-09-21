/*
 * ChipE1Port16Logic.cpp
 *
 *  Created on: 2015年6月17日
 *      Author: Administrator
 */

#include "ChipE1Port16Logic.h"
#include "CPPTools.h"
#include "RegisterAccess.h"
#include <stdio.h>
#include "EZLog.h"

static const std::string chipName = "e1port16logic";

ChipE1Port16Logic::ChipE1Port16Logic(CBaseSlot* slt) : FPGAChip(chipName, slt) {
    // TODO Auto-generated constructor stub

}

ChipE1Port16Logic::~ChipE1Port16Logic() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT ChipE1Port16Logic::ChipInit(void) {
    Chip_INIT_RESULT rtn = updataFPGA();
    if( rtn == succeed ) {
        uint16 value = regAccess->readReg(LED);//temp test
        value |= 2;
        regAccess->writeReg(LED, value);
        os_mut_init(mut_dcn_rcv);
    }
    else if( rtn == donothing ) {
        os_mut_init(mut_dcn_rcv);
    }
    return rtn;
}

std::string ChipE1Port16Logic::GetChipVerInfo(const std::string ChipName,
        const uint16 Reg_Ver_Addr) {
    ChipVerInfo = ChipName + "V"
            + CPPTools::number2string(regAccess->readReg(Reg_Ver_Addr) >> 12 & 0xf)
            + "."
            + CPPTools::number2string(regAccess->readReg(Reg_Ver_Addr) >> 8 & 0x7)
            + "." + CPPTools::number2string(regAccess->readReg(Reg_Ver_Addr) & 0xff);
    return ChipVerInfo;
}
std::string  ChipE1Port16Logic::GetVerInfo(){
    return  (GetChipVerInfo("PCB:",REG_VER_CPLD)).erase(8,2)+","+\
             GetChipVerInfo("CPLD-1:",REG_VER_CPLD)+","+\
             GetChipVerInfo("FPGA:",REG_VER_FPGA_E1LOGIC);
}

bool ChipE1Port16Logic::itsLOS(int e1) {
    if( e1 < 0 || e1 > 15 ) {
        return false;
    }
    uint16 los = regAccess->readReg(REG_E1_LOS);
    los &= (1 << e1 );
    return los == 0;
}

bool ChipE1Port16Logic::itsAIS(int e1) {
    if( e1 < 0 || e1 > 15 ) {
        return false;
    }
    uint16 ais = regAccess->readReg(REG_E1_AIS);
    ais &= (1 << e1 );
    return ais != 0;
}

bool ChipE1Port16Logic::itsLOF(int e1) {
    uint16 alm = regAccess->readReg(REG_E1_ALM_BASE+e1);
    return (alm & (1 << 4)) == 0;
}

bool ChipE1Port16Logic::itsLOMF(int e1) {
    uint16 alm = regAccess->readReg(REG_E1_ALM_BASE+e1);
    return (alm & (1 << 2)) != 0;
}


void ChipE1Port16Logic::setPortLoopOut(uint8 ch, uint8 loop){
    uint16 temp = 0;
    temp = regAccess->readReg(REG_LOOP_OUTER);//out_loop
    temp &=~ (1 << ch);
    temp |=  (loop << ch);
    regAccess->writeReg(REG_LOOP_OUTER, temp);
}
void ChipE1Port16Logic::setPortLoopIn(uint8 ch, uint8 loop){
    uint16 temp = 0;
    temp = regAccess->readReg(REG_LOOP_INNER);//in_loop
    temp &=~ (1 << ch);
    temp |=  (loop << ch);
    regAccess->writeReg(REG_LOOP_INNER, temp);
}

bool ChipE1Port16Logic::ifSaHavePacket(void) {
    uint16 temp = regAccess->readReg(REG_SABIT_R_STA);
    if( temp & 1 ) {
        return true;
    }
    return false;
}
uint8 ChipE1Port16Logic::getSourceCh(void) {
    return regAccess->readReg(REG_SABIT_R_CH);
}
int ChipE1Port16Logic::getSaPacketLen(void) {
    return regAccess->readReg(REG_SABIT_R_LEN);
}
bool ChipE1Port16Logic::getSaPacket(uint8* buff, uint16 len, uint16 startPos) {
    for (int i = 0; i < len; ++i) {
        buff[i] = (uint8)regAccess->readReg(REG_SABIT_R_BUF+i+startPos);
    }
    return true;
}
void ChipE1Port16Logic::readSaPacketOver(void) {
    regAccess->writeReg(REG_SABIT_R_OVER, 0x46, 0);
}

void ChipE1Port16Logic::sendSaPacket(uint8 ch, uint8* data, uint16 len) {
    if( len > 255 ) {
#ifdef EZ_DEBUG
        printf("\n!!!Packet too long at ch-%d!!!\n", ch+1);
#endif
        return;
    }
    if( itsLOS(ch) ) {
        return;
    }
    uint8 chmask = 1 << (ch % 8);
    for (int i = 0; i < 200; ++i) {
//        if( (regAccess->readReg(REG_SABIT_T_STA)&1) == 1 ) {
            if( (regAccess->readReg(REG_SABIT_T_CH_STA_L + ch/8) & chmask) != 0 ) {
                break;
            }
//        }
        os_dly_wait(1);
        if( i == 199 ) {
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


void ChipE1Port16Logic::turnOnLedWork(uint8 sn, bool on) {
    uint16 temp = regAccess->readReg(LED_WRK);
    if( on ) {
        temp &= ~( 1 << sn );
    }
    else {
        temp |= ( 1 << sn );
    }
    regAccess->writeReg(LED_WRK, temp);
}

void ChipE1Port16Logic::turnOnLedAlm(uint8 sn, bool on) {
    uint16 temp = regAccess->readReg(LED_ALM);
    if( on ) {
        temp &= ~( 1 << sn );
    }
    else {
        temp |= ( 1 << sn );
    }
    regAccess->writeReg(LED_ALM, temp);
}

void ChipE1Port16Logic::sabitInterruptEnable(bool en) {
    uint16 regData = (en ? 1: 0);
    regAccess->writeReg(REG_INTRR_EN, regData);
}

void ChipE1Port16Logic::resetRemote(uint8 port) {
    if(port < 8) {
        uint16 temp = regAccess->readReg(REG_REMOTE_RESET_L);
        temp ^= (1 << port);
        regAccess->writeReg(REG_REMOTE_RESET_L, temp);
    }
    else {
        uint16 temp = regAccess->readReg(REG_REMOTE_RESET_H);
        temp ^= (1 << (port-8));
        regAccess->writeReg(REG_REMOTE_RESET_H, temp);
    }
}

void ChipE1Port16Logic::setPortEnable(uint8 port, uint8 en) {
    uint16 temp = 0;
    temp = regAccess->readReg(REG_PORT_EN);//out_loop
    temp |=  (1 << port);
    temp ^=  (en << port);
    regAccess->writeReg(REG_PORT_EN, temp);
}

void ChipE1Port16Logic::selectPCMClock(uint8 src) {
    regAccess->writeReg(REG_CLK_2M_SEL, src);
}

void ChipE1Port16Logic::setSabitInterruptEnable(uint8 ch, uint8 en) {
    uint16 regV = regAccess->readReg(REG_SABIT_INTRR_EN);
    regV &= ~(1<<ch);
    regV |= (en << ch);
    regAccess->writeReg(REG_SABIT_INTRR_EN, regV);
}

void ChipE1Port16Logic::setDcnInterruptEnable(uint8 ch, uint8 en) {
    uint16 regV = regAccess->readReg(REG_DCN_INTRR_EN);
    regV &= ~(1<<ch);
    regV |= (en << ch);
    regAccess->writeReg(REG_DCN_INTRR_EN, regV);
}

bool ChipE1Port16Logic::selectDcnTs(uint8 ch, uint32 tsmap) {
    regAccess->writeReg(REG_DCN_TS_SEL_L(ch), tsmap & 0xffff);
    regAccess->writeReg(REG_DCN_TS_SEL_H(ch), tsmap >> 16);
    return true;
}

uint32 ChipE1Port16Logic::getDcnTsMap(uint8 ch) {
    return (regAccess->readReg(REG_DCN_TS_SEL_H(ch)) << 16) | regAccess->readReg(REG_DCN_TS_SEL_L(ch));
}
/*
 * DCN 收包buff里包括了长度字节，需要先把长度字节读出来，后续才是载荷；
 * 因为长度字节的值，包含自身的2字节长度。因此收包时，真实的包长度为长度字节值-2；
 */
bool ChipE1Port16Logic::ifDcnHavePacket(uint8 ch) {
    uint16 regv = regAccess->readReg(REG_DCN_R_STA);
    if( (regv & ( 1 << ch )) != 0 ) {
        regv = regAccess->readReg(REG_DCN_R_STA);
        if( (regv & ( 1 << ch )) != 0 ) {
            regv = regAccess->readReg(REG_DCN_R_STA);
            if( (regv & ( 1 << ch )) != 0 ) {
                return true;
            }
        }
        else {
            EZLog::instance().record("#REG_DCN_R_STA read error.");
        }
    }
    return false;
}
int  ChipE1Port16Logic::getDcnPacketLen(uint8 ch) {
//    os_mut_wait(mut_dcn_rcv, 0xffff);
    regAccess->writeReg(REG_DCN_R_SEL, ch);
    uint16 regv = regAccess->readReg(REG_DCN_R_LEN);
//    os_mut_release(mut_dcn_rcv);
    return regv-2;

}
bool ChipE1Port16Logic::getDcnPacket(uint8 ch, uint8* buff, uint16 len) {
//    os_mut_wait(mut_dcn_rcv, 0xffff);
    regAccess->writeReg(REG_DCN_R_SEL, ch);

    for (int i = 0; i < 2; ++i) {
        //gap length bytes
        regAccess->readReg(REG_DCN_R_BUF);
    }
    for (int i = 0; i < len; ++i) {
        buff[i] = regAccess->readReg(REG_DCN_R_BUF);
    }
//    os_mut_release(mut_dcn_rcv);
    return true;
}
void ChipE1Port16Logic::readDcnPacketOver(uint8 ch) {
    regAccess->writeReg(REG_DCN_MONI_SEL, ch);
    uint16 bak = regAccess->readReg(REG_DCN_PAGE_STA) & (1<<14);
    while( bak == (regAccess->readReg(REG_DCN_PAGE_STA) & (1<<14)) ) {
        regAccess->writeReg(REG_DCN_R_OVER, 1<<ch);
        regAccess->writeReg(REG_DCN_R_OVER, 0);
    }

}
void ChipE1Port16Logic::sendDcnPacket(uint8 ch, uint8* data, uint16 len) {
    uint8 retryNum = 200;
    while( retryNum-- ) {
        uint16 sta = regAccess->readReg(REG_DCN_T_STA);
        if( ((sta >> ch) & 1) != 0 ) {
            regAccess->writeReg(REG_DCN_T_BUF(ch), (len+2) >> 8, 0);
            regAccess->writeReg(REG_DCN_T_BUF(ch), (len+2) & 0xff, 0);
            for (int i = 0; i < len; ++i) {
                regAccess->writeReg(REG_DCN_T_BUF(ch), data[i], 0);
            }

            /*write done*/
            regAccess->writeReg(REG_DCN_T_OVER, 1<<ch);
            regAccess->writeReg(REG_DCN_T_OVER, 0);
            return;
        }
        os_dly_wait(1);
    }
#ifdef EZ_DEBUG
    printf("\n!!!ch-%d is busy!!!\n", ch);
#endif
}

