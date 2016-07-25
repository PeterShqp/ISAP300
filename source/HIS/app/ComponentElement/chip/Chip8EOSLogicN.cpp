/*
 * Chip8EOSLogicNN.cpp
 *
 *  Created on: 2014��12��22��
 *      Author: Administrator
 */

#include "Chip8EOSLogicN.h"
#include "RegisterAccess.h"
#include "CBaseSlot.h"
#include "os.h"

static const std::string chipName = "ETHLogic1";

Chip8EOSLogicN::Chip8EOSLogicN(CBaseSlot* slt) : FPGAChip(chipName, slt) {
    ra = slt->getRegisterAccess();

}

Chip8EOSLogicN::~Chip8EOSLogicN() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT Chip8EOSLogicN::ChipInit(void) {
    Chip_INIT_RESULT rtn = updataFPGA();
    if( rtn == succeed ) {
        initRegs();//temp test
    }
    return rtn;
}

void Chip8EOSLogicN::initRegs(void) {
    regAccess->writeReg(0x1101, 0xA0A0, false);
    os_dly_wait(10);
    regAccess->writeReg(0x1101, 0xA1A1, false);
    os_dly_wait(10);

}
