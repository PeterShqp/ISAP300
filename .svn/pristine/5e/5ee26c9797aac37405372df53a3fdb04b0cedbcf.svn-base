/*
 * Chip8STM1Logic2.h
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#ifndef CHIP8STM1LOGIC2_H_
#define CHIP8STM1LOGIC2_H_

#include "BaseChip.h"
#include "os.h"

class RegisterAccess;
class CBaseSlot;

class Chip8STM1Logic2: public BaseChip {
public:
    Chip8STM1Logic2(CBaseSlot* slt);
    virtual ~Chip8STM1Logic2();
    virtual Chip_INIT_RESULT ChipInit(void);
    /*
     * for DCC
     */
    bool setDCCOH(uint8 ch, uint16 data);

    bool ifHavePacket(uint8 ch);
    int getPacketLen(uint8 ch);
    uint32 GetDCCPacket(uint8 ch, uint8* buff, uint16 len, uint16 starPos = 0);
    void DccSendPacket(uint8 ch, uint8* data, uint16 len);
    void clearDccRdBufForce(uint8 ch);

    /*
     * for LED
     */
    void portLEDLosOn(uint8 ch, bool sel);
    void cardLEDAlarmOn(bool sel);
    void cardLEDWorkOn(bool sel);

private:
    bool ifSendBusy(uint8 ch);
    void sendStart(uint8 ch);

    RegisterAccess* ra;

    static const uint16 REG_DCC_A_SEL = 0x2001;
    static uint16 REG_DCC_N_SEL(uint8 N) {
        return REG_DCC_A_SEL + N;
    };

    static const uint16 REG_DCC_A_TS = 0x2401; //bit1 send done, bit0 send start
    static const uint16 REG_DCC_B_TS = 0x2403; //bit1 send done, bit0 send start
    static const uint16 REG_DCC_A_RS = 0x2407; //bit1 rcv ready, bit0 rcv done
    static const uint16 REG_DCC_B_RS = 0x240b; //bit1 rcv ready, bit0 rcv done

    static uint16 REG_DCC_N_TS(uint8 N) {
        if (N % 2) {
            return REG_DCC_B_TS + N / 2 * 0x100;
        }
        return REG_DCC_A_TS + N / 2 * 0x100;
    };
    static uint16 REG_DCC_N_RS(uint8 N) {
        if (N % 2) {
            return REG_DCC_B_RS + N / 2 * 0x100;
        }
        return REG_DCC_A_RS + N / 2 * 0x100;
    };

    static const uint16 REG_DCC_A_T_LEN = 0x3000;
    static const uint16 REG_DCC_A_T_BUF = 0x3002;
    static const uint16 REG_DCC_B_T_LEN = 0x3400;
    static const uint16 REG_DCC_B_T_BUF = 0x3402;

    static const uint16 REG_DCC_A_R_LEN = 0x3800;
    static const uint16 REG_DCC_A_R_BUF = 0x3802;
    static const uint16 REG_DCC_B_R_LEN = 0x3C00;
    static const uint16 REG_DCC_B_R_BUF = 0x3C02;

    static uint16 REG_DCC_N_T_LEN(uint8 N) {
        if (N % 2) {
            return REG_DCC_B_T_LEN + (N / 2) * 0x1000;
        }
        return REG_DCC_A_T_LEN + (N / 2) * 0x1000;
    };

    static uint16 REG_DCC_N_T_BUF(uint8 N) {
        if (N % 2) {
            return REG_DCC_B_T_BUF + (N / 2) * 0x1000;
        }
        return REG_DCC_A_T_BUF + (N / 2) * 0x1000;
    };

    static uint16 REG_DCC_N_R_LEN(uint8 N) {
        if (N % 2) {
            return REG_DCC_B_R_LEN + (N / 2) * 0x1000;
        }
        return REG_DCC_A_R_LEN + (N / 2) * 0x1000;
    };

    static uint16 REG_DCC_N_R_BUF(uint8 N) {
        if (N % 2) {
            return REG_DCC_B_R_BUF + (N / 2) * 0x1000;
        }
        return REG_DCC_A_R_BUF + (N / 2) * 0x1000;
    };

    static const uint16 REG_LED_1 = 0x2009; //bit9 almcard
                                            //bit8 workcard
                                            //bit7~0 los7~0
};

#endif /* CHIP8STM1LOGIC2_H_ */
