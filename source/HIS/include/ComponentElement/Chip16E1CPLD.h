/*
 * Chip16E1CPLD.h
 *
 *  Created on: 2014Äê10ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef CHIP16E1CPLD_H_
#define CHIP16E1CPLD_H_

#include "Chip24E1CPLD.h"

class Chip16E1CPLD: public Chip24E1CPLD {
public:
    Chip16E1CPLD(CBaseSlot* slt);
    virtual ~Chip16E1CPLD();

    void ledWorkOn(uint8 sn, bool on);
    virtual std::string GetVerInfo(void);

private:
    static const uint16 REG_LED_WRK   = 0x0102;

};

#endif /* CHIP16E1CPLD_H_ */
