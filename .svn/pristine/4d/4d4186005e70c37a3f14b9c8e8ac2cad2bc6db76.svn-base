/*
 * Chip8STM1Logic1.cpp
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#include "Chip8STM1Logic1.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"

static const std::string chipName = "STM1Logic1";

Chip8STM1Logic1::Chip8STM1Logic1(CBaseSlot* slt) : BaseChip(chipName) {
    ra = slt->getRegisterAccess();

}

Chip8STM1Logic1::~Chip8STM1Logic1() {
    // TODO Auto-generated destructor stub
}


Chip_INIT_RESULT Chip8STM1Logic1::ChipInit(void) {
    return donothing;
}

/*
 * ΪSDHBUS��slotVCͨ����ch��ѡ��֧·�� fromֵΪ
 */
int Chip8STM1Logic1::sdhBusSel(uint8 bus, uint8 ch, uint8 from) {
    if( bus == 0 ) {
        ra->writeReg(REG_BUS_SEL_A+ch, from);
    }
    else if( bus == 1 ) {
        ra->writeReg(REG_BUS_SEL_B+ch, from);
    }
    else {
        return -1;
    }
    return 1;
}
