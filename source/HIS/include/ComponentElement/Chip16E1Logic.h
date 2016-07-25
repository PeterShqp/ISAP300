/*
 * Chip16E1Logic.h
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef CHIP16E1LOGIC_H_
#define CHIP16E1LOGIC_H_

#include "ChipE1Logic.h"

class Chip16E1Logic: public ChipE1Logic {
    static const uint16 REG_LED_ALM = 0x1003; //bit0 work, bit1 alm, bit2 connect, bit3 drop

public:
    Chip16E1Logic(CBaseSlot* slt);
    virtual ~Chip16E1Logic();

    void ledAlarmOn(uint8 sn, bool on);
};

#endif /* CHIP16E1LOGIC_H_ */
