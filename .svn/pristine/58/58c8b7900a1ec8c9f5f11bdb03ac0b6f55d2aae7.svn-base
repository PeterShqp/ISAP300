/*
 * Chip8EOSLogic.cpp
 *
 *  Created on: 2014-3-26
 *      Author: Administrator
 */

#include "Chip8EOSLogic.h"
#include "RegisterAccess.h"
#include "CBaseSlot.h"
#include "os.h"

static const std::string chipName = "ETHLogic";

Chip8EOSLogic::Chip8EOSLogic(CBaseSlot* slt) : FPGAChip(chipName, slt) {
    ra = slt->getRegisterAccess();

}

Chip8EOSLogic::~Chip8EOSLogic() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT Chip8EOSLogic::ChipInit(void) {
    Chip_INIT_RESULT rtn = updataFPGA();
    if( rtn == succeed ) {
        initRegs();//temp test
    }
    return rtn;
}

void Chip8EOSLogic::initRegs(void) {
    regAccess->writeReg(0x1101, 0xA0A0, false);
    os_dly_wait(10);
    regAccess->writeReg(0x1101, 0xA1A1, false);
    os_dly_wait(10);

}

