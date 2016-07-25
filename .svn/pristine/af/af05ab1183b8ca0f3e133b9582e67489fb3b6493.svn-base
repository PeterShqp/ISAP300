/*
 * ChipSDHLogic.cpp
 *
 *  Created on: 2013-12-9
 *      Author: Administrator
 */

#include "ChipSDHLogic.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "os.h"

static const std::string chipName = "SDHLogic";

ChipSDHLogic::ChipSDHLogic(CBaseSlot* slt) : BaseChip(chipName) {
    // TODO Auto-generated constructor stub
    regAccess = slt->getRegisterAccess();
}

ChipSDHLogic::~ChipSDHLogic() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT ChipSDHLogic::ChipInit(void) {
    return donothing;
}


void ChipSDHLogic::resetPLL(void) {
    resetPLL(1);
    resetPLL(0x7c);
    resetPLL(0x80);
}

void ChipSDHLogic::resetPLL(int sn) {
    regAccess->writeReg(REG_PLL_RESET, sn);
    os_dly_wait(1);
    regAccess->writeReg(REG_PLL_RESET, 0);
}
