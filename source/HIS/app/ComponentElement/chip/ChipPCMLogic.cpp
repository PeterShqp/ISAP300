/*
 * ChipPCMLogic.cpp
 *
 *  Created on: 2013-12-8
 *      Author: Administrator
 *
 *      ��Ҫ��3�鹦�ܼ����ڴ�оƬ
 *      1. 64K��������
 *      2. SDHҵ��ʱ��Դѡ��ʹ���
 *      3. DCC��DCN����ͨ��
 */

#include "ChipPCMLogic.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "os.h"
#include "SoftSwitch_define.h"
#include <stdio.h>
#include "UID.h"

static const std::string chipName = "PCMLogic";
static const int slotStbusHIDMapping[] = {0,0,8,9,10,11,12};

ChipPCMLogic::ChipPCMLogic(CBaseSlot* slt) : BaseChip(chipName) {
    regAccess = slt->getRegisterAccess();

}

ChipPCMLogic::~ChipPCMLogic() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT ChipPCMLogic::ChipInit(void) {

    /* ��λCP1121A */
    regAccess->writeReg(REG_RESET_CP1121A, 1);
    os_dly_wait(1);
    regAccess->writeReg(REG_RESET_CP1121A, 0);
    os_dly_wait(100);


    protectFSMStart();

    /* DCC D-Byte all*/
    regAccess->writeReg(REG_DCC_A_SEL, 0x0fff, 0);
    regAccess->writeReg(REG_DCC_B_SEL, 0x0fff, 0);


    for( int i = 0; i < 16; i++ ) {
        for( int j = 0; j < 32; j++ ) {
            regAccess->writeReg( REG_64K_CROSS_BASE | (i<<6) | (j<<1) | 1, 0x80 );
        }
    }

    selectPCMClock(0);
    return succeed;

}

void ChipPCMLogic::resetClockChip(void) {
    /* ��λZarLink30122 */
    uint16 temp = regAccess->readReg(REG_RESET_ZL30122);
    temp &= (1 << 15);
    regAccess->writeReg(REG_RESET_ZL30122, temp, 0);
    os_dly_wait(1);
    temp |= 1;
    regAccess->writeReg(REG_RESET_ZL30122, temp, 0);
    os_dly_wait(1);
}

void ChipPCMLogic::setFreeRun(bool f) {
    if( f ) {
        regAccess->writeReg(REG_RESET_ZL30122, 0x8001, 0);
    }
    else {
        regAccess->writeReg(REG_RESET_ZL30122, 0x0001, 0);
    }
}



void ChipPCMLogic::selectClockSource(USEABLE_RCLOCK cs) {
    uint16 regValue = regAccess->readReg(REG_CLOCK_SEL);
    switch( cs ) {
    case RCLKLocal:
        setFreeRun(true);
        return;
    case RCLKA:
    case RCLKB:
    case RCLKExt:
        regValue &= ~3;
        regValue |= cs;
        break;
    case RCLK2MA:
    case RCLK2MB:
    case RCLK2MExt:
        regValue &= ~(3<<8);
        regValue |= ((cs-10) << 8);
        break;
    default:
        return;
    }
    setFreeRun(false);
    regAccess->writeReg(REG_CLOCK_SEL, regValue);
}

void ChipPCMLogic::setExtClockMode(USEABLE_RCLOCK c, ExtClock_type_E mode) {
    uint16 regValue = regAccess->readReg(REG_CLOCK_SEL);
    switch( c ) {
    case RCLK2MA:
        regValue &= ~(3<<14);
        regValue |= (mode<<14);
        break;
    case RCLK2MB:
        regValue &= ~(3<<12);
        regValue |= (mode<<12);
        break;
    default:
        return;
    }
    regAccess->writeReg(REG_CLOCK_SEL, regValue);
}

bool ChipPCMLogic::setDCCOH(int ch, uint16 data) {
    uint16 regAddr = 0;
    switch( ch ) {
    case 0:
        regAddr = REG_DCC_A_SEL;
        break;
    case 1:
        regAddr = REG_DCC_B_SEL;
        break;
    default:
        return false;
    }
    regAccess->writeReg(regAddr, data);
	return true;
}



bool ChipPCMLogic::ifHavePacket(NM_CH_E ch) {
    uint16 regAddr = 0;
    switch( ch ) {
    case DCC_A:
        regAddr = REG_DCC_A_RS;
        break;
    case DCC_B:
        regAddr = REG_DCC_B_RS;
        break;
    case DCN_A:
        regAddr = REG_DCN_A_RS;
        break;
    case DCN_B:
        regAddr = REG_DCN_B_RS;
        break;
    }
    uint16 value = regAccess->readReg(regAddr);
    if( ((value >> 1 ) & 1) == 0 ) {
        return false;
    }
    return true;
}

bool ChipPCMLogic::ifSendBusy(NM_CH_E ch) {
    uint16 regAddr = 0;
    switch( ch ) {
    case DCC_A:
        regAddr = REG_DCC_A_TS;
        break;
    case DCC_B:
        regAddr = REG_DCC_B_TS;
        break;
    case DCN_A:
        regAddr = REG_DCN_A_TS;
        break;
    case DCN_B:
        regAddr = REG_DCN_B_TS;
        break;
    }
    uint16 value = regAccess->readReg(regAddr);
    if( ((value >> 1 ) & 1) == 1 ) {
        return false;
    }
    return true;
}
void ChipPCMLogic::sendStart(NM_CH_E ch) {
    uint16 regAddr = 0;
    switch( ch ) {
    case DCC_A:
        regAddr = REG_DCC_A_TS;
        break;
    case DCC_B:
        regAddr = REG_DCC_B_TS;
        break;
    case DCN_A:
        regAddr = REG_DCN_A_TS;
        break;
    case DCN_B:
        regAddr = REG_DCN_B_TS;
        break;
    }
    uint16 value = regAccess->readReg(regAddr);
    value ^= 1;
    regAccess->writeReg(regAddr, value, 0);
}

int ChipPCMLogic::getPacketLen(NM_CH_E ch) {
    uint16 regAddr = 0;
    switch( ch ) {
    case DCC_A:
        regAddr = REG_DCC_A_R_LEN;
        break;
    case DCC_B:
        regAddr = REG_DCC_B_R_LEN;
        break;
    case DCN_A:
        regAddr = REG_DCN_A_R_LEN;
        break;
    case DCN_B:
        regAddr = REG_DCN_B_R_LEN;
        break;
    }
    uint16 valueH = regAccess->readReg(regAddr);
    uint16 valueL = regAccess->readReg(regAddr+1);
    uint32 rtn = ((valueH << 8) | valueL);
    if( rtn >= 2 ) {
        return rtn-2;
    }
    return -1;
}

/*
 * ��оƬ�������ݰ��Ƶ�buff,�ҷ��ذ��Ƶĳ���
 */
uint32 ChipPCMLogic::GetDCCPacket(NM_CH_E ch, uint8* buff, uint16 len, uint16 startPos) {
    if( buff ) {
        uint16 regAddr = 0;
        switch( ch ) {
        case DCC_A:
            regAddr = REG_DCC_A_R_BUF;
            break;
        case DCC_B:
            regAddr = REG_DCC_B_R_BUF;
            break;
        case DCN_A:
            regAddr = REG_DCN_A_R_BUF;
            break;
        case DCN_B:
            regAddr = REG_DCN_B_R_BUF;
            break;
        }
        for (int i = 0; i < len; ++i) {
            buff[i] = (uint8)regAccess->readReg(regAddr+i+startPos);
        }
    }
    return 0;
}

void ChipPCMLogic::clearDccRdBufForce(NM_CH_E ch) {
    uint16 regAddr = 0;
    switch( ch ) {
    case DCC_A:
        regAddr = REG_DCC_A_RS;
        break;
    case DCC_B:
        regAddr = REG_DCC_B_RS;
        break;
    case DCN_A:
        regAddr = REG_DCN_A_RS;
        break;
    case DCN_B:
        regAddr = REG_DCN_B_RS;
        break;
    }
    uint16 value = regAccess->readReg(regAddr);
    value ^= 1;
    regAccess->writeReg(regAddr, value, 0);
}

void ChipPCMLogic::DccSendPacket(NM_CH_E ch, uint8* data, uint16 len) {
    if( data != 0 && len <= DEF_MTU ) {
        for (int i = 0; i < 10; ++i) {
            if( !ifSendBusy(ch) ) {
                break;
            }
            os_dly_wait(1);
            if( i == 9 ) {
                return;
            }
        }
        uint16 regbufAddr = 0;
        uint16 reglenAddr = 0;
        switch( ch ) {
        case DCC_A:
            regbufAddr = REG_DCC_A_T_BUF;
            reglenAddr = REG_DCC_A_T_LEN;
            break;
        case DCC_B:
            regbufAddr = REG_DCC_B_T_BUF;
            reglenAddr = REG_DCC_B_T_LEN;
            break;
        case DCN_A:
            regbufAddr = REG_DCN_A_T_BUF;
            reglenAddr = REG_DCN_A_T_LEN;
            break;
        case DCN_B:
            regbufAddr = REG_DCN_B_T_BUF;
            reglenAddr = REG_DCN_B_T_LEN;
            break;
        }

        regAccess->writeReg(reglenAddr, (len+2)>>8, 0);
        regAccess->writeReg(reglenAddr+1, (len+2)&0xff, 0);
        for (int i = 0; i < len; ++i) {
            regAccess->writeReg(regbufAddr+i, data[i], 0);
        }
        sendStart(ch);
    }
}

bool ChipPCMLogic::CreatCrossConnection(uint32 toCh, uint32 toTs, uint32 fromCh, uint32 fromTs) {
    uint16 uiRegAddr = (toCh << 5) | toTs;
    if( toCh > 15 || fromCh > 15 || toTs > 31 || fromTs > 31 ) {
        return false;
    }
    regAccess->writeReg( (uiRegAddr << 1) | REG_64K_CROSS_BASE, fromTs);
    regAccess->writeReg( (uiRegAddr << 1) | 1 | REG_64K_CROSS_BASE, fromCh );
    return true;
}


bool ChipPCMLogic::RemoveCrossConnection(uint32 Ch, uint32 Ts) {
    uint16 uiRegAddr = (Ch << 5) | Ts;
    if( Ch > 15 || Ts > 31 ) {
        return false;
    }
    regAccess->writeReg( (uiRegAddr << 1) | 1 | REG_64K_CROSS_BASE, 0x80 );
    return true;
}

uint16 ChipPCMLogic::getHID(uint32 uid) {
    UN_Info info = UID::breakUID(uid);
    if( info.ts.slot == 0 || info.ts.slot == 1 ) {
        return (info.ts.E1 << 8) | (info.ts.TS);
    }
    return (slotStbusHIDMapping[info.ts.slot] << 8) | info.ts.TS;
}

bool ChipPCMLogic::itsLOS(int e1) {
    if( e1 < 0 || e1 > 7 ) {
        return false;
    }
    uint16 los = regAccess->readReg(REG_E1_LOS);
    los &= (1 << e1 );
    return los == 0;
}

bool ChipPCMLogic::itsAIS(int e1) {
    if( e1 < 0 || e1 > 4 ) {
        return false;
    }
    uint16 ais = regAccess->readReg(REG_E1_AIS);
    ais &= (1 << e1 );
    return ais != 0;
}

bool ChipPCMLogic::itsLOF(int e1) {
    uint16 alm = regAccess->readReg(REG_E1_ALM_BASE+e1);
    return (alm & (1 << 4)) == 0;
}

bool ChipPCMLogic::itsLOMF(int e1) {
    uint16 alm = regAccess->readReg(REG_E1_ALM_BASE+e1);
    return (alm & (1 << 2)) != 0;
}


void ChipPCMLogic::clockIOSet(uint16 setPins, uint16 clrPins) {
    uint16 temp = regAccess->readReg(REG_ClOCK_CTRL);
    if( setPins != 0 ) {
        temp |= setPins;
    }
    if( clrPins != 0 ) {
        temp &= ~clrPins;
    }
    regAccess->writeReg(REG_ClOCK_CTRL, temp, false);
}

bool ChipPCMLogic::MSPIReady(void) {
    uint16 temp = regAccess->readReg(REG_MSPI_ADDR);
    return (temp >> 15) == 1;
}

uint8 ChipPCMLogic::readMSPI(uint8 addr) {
    regAccess->writeReg( REG_MSPI_ADDR, addr | 0x80, 0 );
    while( !MSPIReady() );
    uint16 temp = regAccess->readReg( REG_MSPI_DATA);
    return temp >> 8;
}

void ChipPCMLogic::writeMSPI(uint8 addr, uint8 data) {
    regAccess->writeReg(REG_MSPI_DATA, data, 0);
    regAccess->writeReg( REG_MSPI_ADDR, addr, 0 );
    while( !MSPIReady() );
}

void ChipPCMLogic::setAlarm(uint8 remote, uint8 local) {
    uint16 state = (remote << 8) | (local<<0);
    regAccess->writeReg(REG_Alarm_STA, state, 0);
}

void ChipPCMLogic::protectFSMStart(void) {
    regAccess->writeReg(REG_FSM_Start, 1);
}
void ChipPCMLogic::selectPCMClock(uint8 src) {
    if( src == 0 ) {
        regAccess->writeReg(REG_PCM_CLOCK_SEL, 0x80);
    }
    else if( src < 9 ) {
        regAccess->writeReg(REG_PCM_CLOCK_SEL, src-1);
    }
    regAccess->writeReg(REG_PCM_CLOCK_START, 0x00, 0); //start pcm clock generator
}
void ChipPCMLogic::setPortLoopOut(uint8 ch, uint8 loop){
	uint16 temp = 0;
	temp = regAccess->readReg(REG_LOOP_OUTER);//out_loop
	temp &=~ (1 << ch);
	temp |=  (loop << ch);
	regAccess->writeReg(REG_LOOP_OUTER, temp);
}
void ChipPCMLogic::setPortLoopIn(uint8 ch, uint8 loop){
	uint16 temp = 0;
	temp = regAccess->readReg(REG_LOOP_INNER);//in_loop
	temp &=~ (1 << ch);
	temp |=  (loop << ch);
	regAccess->writeReg(REG_LOOP_INNER, temp);
}

bool ChipPCMLogic::ifSaHavePacket(void) {
    uint16 temp = regAccess->readReg(REG_SABIT_R_STA);
    if( temp & 1 ) {
        return true;
    }
    return false;
}
uint8 ChipPCMLogic::getSourceCh(void) {
    return regAccess->readReg(REG_SABIT_R_CH);
}
int ChipPCMLogic::getSaPacketLen(void) {
    return regAccess->readReg(REG_SABIT_R_LEN);
}
bool ChipPCMLogic::getSaPacket(uint8* buff, uint16 len, uint16 startPos) {
    for (int i = 0; i < len; ++i) {
        buff[i] = (uint8)regAccess->readReg(REG_SABIT_R_BUF+i+startPos);
    }
    return true;
}
void ChipPCMLogic::readSaPacketOver(void) {
    regAccess->writeReg(REG_SABIT_R_OVER, 0x46, 0);
}

void ChipPCMLogic::sendSaPacket(uint8 ch, uint8* data, uint16 len) {
    if( len > 255 ) {
#ifdef EZ_DEBUG
        printf("\n!!!Packet too long at ch-%d!!!\n", ch+1);
#endif
        return;
    }
    for (int i = 0; i < 10; ++i) {
        if( (regAccess->readReg(REG_SABIT_T_STA)&1) == 1 ) {
            break;
        }
        os_dly_wait(1);
        if( i == 9 ) {
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
