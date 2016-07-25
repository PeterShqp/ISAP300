/*
 * CardV5.cpp
 *
 *  Created on: 2015Äê3ÔÂ11ÈÕ
 *      Author: Administrator
 */

#include "CardV5.h"
#include "CardTypeID_define.h"
#include <stdio.h>
#include "SysError.h"
#include <iostream>

CardV5::CardV5(std::string& name, CBaseSlot* slot) : CBaseCard(name, slot), fpga(slot) {
    Chip_INIT_RESULT rst = fpga.ChipInit();
    if( rst == failed ) {
        throw SysError("!!!V5Logic init error!!!");
    }
    else if( rst == succeed ) {
    }
    else {
        std::cout << fpga.itsName() << " have been running!" << std::endl;
    }
}

CardV5::~CardV5() {
    // TODO Auto-generated destructor stub
}

int CardV5::GetCartTypeID() {
    return V5_CARD_TYPEID;
}
