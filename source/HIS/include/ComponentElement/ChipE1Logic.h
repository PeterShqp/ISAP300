/*
 * ChipE1Logic.h
 *
 *  Created on: 2013-12-17
 *      Author: Administrator
 */

#ifndef CHIPE1LOGIC_H_
#define CHIPE1LOGIC_H_

#include "FPGAChip.h"

class RegisterAccess;
class CBaseSlot;



class ChipE1Logic : public FPGAChip {
    static const uint16 VER = 0x000f;
    static const uint16 REG_LED_CTRL = 0x0100; //bit0 work, bit1 alm, bit2 connect, bit3 drop
public:
    ChipE1Logic(CBaseSlot* slt);
    ChipE1Logic(const std::string& chipName, CBaseSlot* slt);
    virtual ~ChipE1Logic();

    virtual Chip_INIT_RESULT ChipInit(void);

    void ledWorkOn(bool on);
    void ledAlmkOn(bool on);
    void ledConnectOn(bool on);
    void ledDropOn(bool on);
private:
    typedef enum {
        LED_WRK, LED_ALM, LED_CON, LED_DRP
    }E1_LED_E;
    void ledOn(E1_LED_E led, bool on);
    void initRegs(void);
};

#endif /* CHIPE1LOGIC_H_ */
