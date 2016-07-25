/*
 * ChipV5Logic.cpp
 *
 *  Created on: 2015��3��12��
 *      Author: Administrator
 */

#include "ChipV5Logic.h"
#include "RegisterAccess.h"

static const std::string chipName = "V5Logic";

ChipV5Logic::ChipV5Logic(CBaseSlot* slt) : FPGAChip(chipName, slt) {
    // TODO Auto-generated constructor stub

}

ChipV5Logic::~ChipV5Logic() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT ChipV5Logic::ChipInit(void) {
    Chip_INIT_RESULT rtn = updataFPGA();
//    if( rtn == succeed ) {
//        initRegs();//temp test
//    }
    return rtn;
}
