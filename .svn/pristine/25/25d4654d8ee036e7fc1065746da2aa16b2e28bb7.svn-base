/*
 * Chip8STM1Logic2.cpp
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#include "Chip8STM1Logic2.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "os.h"
#include "SoftSwitch_define.h"

static const std::string chipName = "STM1Logic2";

Chip8STM1Logic2::Chip8STM1Logic2(CBaseSlot* slt) :
        BaseChip(chipName) {
    ra = slt->getRegisterAccess();

}

Chip8STM1Logic2::~Chip8STM1Logic2() {
    // TODO Auto-generated destructor stub

}


Chip_INIT_RESULT Chip8STM1Logic2::ChipInit(void) {
    for (int i = 0; i < 8; ++i) {
        uint16 regAddr = REG_DCC_N_SEL(i);
        ra->writeReg(regAddr, 0x0fff);
    }

    return succeed;
}

bool Chip8STM1Logic2::setDCCOH(uint8 ch, uint16 data) {
    uint16 regAddr = REG_DCC_N_SEL(ch);
    ra->writeReg(regAddr, data);
    return true;
}

bool Chip8STM1Logic2::ifHavePacket(uint8 ch) {
    uint16 regAddr = REG_DCC_N_RS(ch);
    uint16 value = ra->readReg(regAddr);
    if (((value >> 1) & 1) == 0) {
        return false;
    }
    return true;
}

bool Chip8STM1Logic2::ifSendBusy(uint8 ch) {
    uint16 regAddr = REG_DCC_N_TS(ch);
    uint16 value = ra->readReg(regAddr);
    if (((value >> 1) & 1) == 1) {
        return false;
    }
    return true;
}
void Chip8STM1Logic2::sendStart(uint8 ch) {
    uint16 regAddr = REG_DCC_N_TS(ch);
    uint16 value = ra->readReg(regAddr);
    value ^= 1;
    ra->writeReg(regAddr, value, 0);
}

int Chip8STM1Logic2::getPacketLen(uint8 ch) {
    uint16 regAddr = REG_DCC_N_R_LEN(ch);
    uint16 valueH = ra->readReg(regAddr);
    uint16 valueL = ra->readReg(regAddr + 1);
    uint32 rtn = ((valueH << 8) | valueL);
    if (rtn >= 2) {
        return rtn - 2;
    }
    return -1;
}

/*
 * ��оƬ�������ݰ��Ƶ�buff,�ҷ��ذ��Ƶĳ���
 */
uint32 Chip8STM1Logic2::GetDCCPacket(uint8 ch, uint8* buff, uint16 len, uint16 starPos) {
    if (buff) {
        uint16 regAddr = REG_DCC_N_R_BUF(ch) + starPos;
        for (int i = 0; i < len; ++i) {
            buff[i] = (uint8) ra->readReg(regAddr + i);
        }
    }
    return 0;
}

void Chip8STM1Logic2::clearDccRdBufForce(uint8 ch) {
    uint16 regAddr = REG_DCC_N_RS(ch);
    uint16 value = ra->readReg(regAddr);
    value ^= 1;
    ra->writeReg(regAddr, value, 0);
}
void Chip8STM1Logic2::DccSendPacket(uint8 ch, uint8* data, uint16 len) {
    if (data != 0 && len < DEF_MTU) {
        for (int i = 0; i < 10; ++i) {
            if( !ifSendBusy(ch) ) {
                break;
            }
            os_dly_wait(1);
            if( i == 9 ) {
                return;
            }
        }
        uint16 regbufAddr = REG_DCC_N_T_BUF(ch);
        uint16 reglenAddr = REG_DCC_N_T_LEN(ch);

        ra->writeReg(reglenAddr, (len + 2) >> 8, 0);
        ra->writeReg(reglenAddr + 1, (len + 2) & 0xff, 0);
        for (int i = 0; i < len; ++i) {
            ra->writeReg(regbufAddr + i, data[i], 0);
        }
        sendStart(ch);
    }
}
/*
 * for Led
 */
void Chip8STM1Logic2::portLEDLosOn(uint8 ch, bool sel) {
    uint16 PortLedPosition;
    PortLedPosition = ra->readReg(REG_LED_1);
    if (!sel) {
        PortLedPosition |= (1 << ch);
        ra->writeReg(REG_LED_1, PortLedPosition, 0);
    } else {
        PortLedPosition &= ~(1 << ch);
        ra->writeReg(REG_LED_1, PortLedPosition, 0);
    }
}
void Chip8STM1Logic2::cardLEDAlarmOn(bool sel) {
    uint16 PortLedPosition;
    PortLedPosition = ra->readReg(REG_LED_1);
    if (!sel) {
        PortLedPosition |= (1 << 9);
        ra->writeReg(REG_LED_1, PortLedPosition, 0);
    } else {
        PortLedPosition &= ~(1 << 9);
        ra->writeReg(REG_LED_1, PortLedPosition, 0);
    }
}
void Chip8STM1Logic2::cardLEDWorkOn(bool sel) {
    uint16 PortLedPosition;
    PortLedPosition = ra->readReg(REG_LED_1);
    if (sel) {
        PortLedPosition |= (1 << 8);
        ra->writeReg(REG_LED_1, PortLedPosition, 0);
    } else {
        PortLedPosition &= ~(1 << 8);
        ra->writeReg(REG_LED_1, PortLedPosition, 0);
    }
}
