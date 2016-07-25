/*
 * Chip30VFLogic.cpp
 *
 *  Created on: 2014-2-21
 *      Author: Administrator
 */

#include "Chip30VFLogic.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include "s1l_line_input.h"

static const std::string chipName = "VFLOGIC";

Chip30VFLogic::Chip30VFLogic(CBaseSlot* slt) : BaseChip(chipName){
    regAccess = slt->getRegisterAccess();
    while(ifHavePacket()) {
        regAccess->readReg(REG_INC_RCV_OVER);
    }
}

Chip30VFLogic::~Chip30VFLogic() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT Chip30VFLogic::ChipInit(void) {
	display_prompt();
    return donothing;
}

bool Chip30VFLogic::ifSendBusy(void) {
    uint16 temp = regAccess->readReg(REG_INC_SND_RCV_ST);
    if( (temp & 1) == 0 ) {
        return true;
    }
    return false;
}
void Chip30VFLogic::sendPacket(uint8* data, uint8 len) {
    if( data != 0 ) {
        for (int i = 0; i < len; ++i) {
            regAccess->writeReg(REG_INC_SND_BUF+i, data[i], false);
        }
        regAccess->writeReg(REG_INC_SND_START, 0, false);
    }
}

bool Chip30VFLogic::ifHavePacket(void) {
    uint16 temp = regAccess->readReg(REG_INC_SND_RCV_ST);
    if( (temp & 2) != 0 ) {
        return true;
    }
    return false;
}
void Chip30VFLogic::readPacket(uint8* data) {
    if( data ) {
        for (int i = 0; i < 31; ++i) {
            data[i] = regAccess->readReg(REG_INC_RCV_BUF+i);
        }
        regAccess->readReg(REG_INC_RCV_OVER);
    }
}
