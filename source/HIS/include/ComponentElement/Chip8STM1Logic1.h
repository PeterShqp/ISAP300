/*
 * Chip8STM1Logic1.h
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#ifndef CHIP8STM1LOGIC1_H_
#define CHIP8STM1LOGIC1_H_

#include "BaseChip.h"

class RegisterAccess;
class CBaseSlot;

class Chip8STM1Logic1: public BaseChip {
    static const uint16 REG_BUS_SEL_A = 0x1000; //bit2 enable(1), bit0 1 stm sel
    static const uint16 REG_BUS_SEL_B = 0x1040;
public:
    Chip8STM1Logic1(CBaseSlot* slt);
    virtual ~Chip8STM1Logic1();

    virtual Chip_INIT_RESULT ChipInit(void);


    int sdhBusSel(uint8 bus, uint8 ch, uint8 frombus);

private:
    RegisterAccess* ra;
};

#endif /* CHIP8STM1LOGIC1_H_ */
