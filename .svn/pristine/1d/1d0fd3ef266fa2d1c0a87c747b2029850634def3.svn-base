/*
 * ChipSDHLogic.h
 *
 *  Created on: 2013-12-9
 *      Author: Administrator
 */

#ifndef CHIPSDHLOGIC_H_
#define CHIPSDHLOGIC_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;

class ChipSDHLogic : public BaseChip {
    static const uint16 REG_PLL_RESET   = 0xC008;
    static const uint16 REG_VER_NUM     = 0x2020;
public:
    ChipSDHLogic(CBaseSlot* slt);
    virtual ~ChipSDHLogic();

    virtual Chip_INIT_RESULT ChipInit(void);

    void resetPLL(void);

private:
    void resetPLL(int sn);
    RegisterAccess* regAccess;
};

#endif /* CHIPSDHLOGIC_H_ */
