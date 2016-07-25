/*
 * GeneralLogic.cpp
 *
 *  Created on: 2013-11-27
 *      Author: Administrator
 */

#include "GeneralLogic.h"
#include "ComponentFactory.h"
#include "CardCPU.h"

GeneralLogic GeneralLogic::dev;

//static const std::string s = "GeneralLogic";

GeneralLogic::GeneralLogic() /*: BaseChip(s)*/ {
//    CurrentCS = 0;

}

GeneralLogic::~GeneralLogic() {
    // TODO Auto-generated destructor stub
}


uint8 GeneralLogic::getDataWide(void) {
    return 8;
}


void GeneralLogic::switchSlotTo(uint32 slt) {
    uint8 cs = ComponentFactory::getCSBySlotNumber(slt);
//    CurrentCS = slt;
    *((uint8*)SLOT_CS) = cs;
}

void GeneralLogic::switchToIdle(void) {
    *((uint8*)SLOT_CS) = 0xff;
}

bool GeneralLogic::assignSlot(uint8 slot) {
    uint8* reg = reinterpret_cast<uint8*>(WORKING_INDICATE);
    if( reg ) {
        *reg &= ~0x80;
        *reg |= (slot << 7);
        return true;
    }
    return false;
}
bool GeneralLogic::ifOMUWorking(void) {
    uint8* reg = reinterpret_cast<uint8*>(WORKING_INDICATE);
    if( reg ) {
        if( ((*reg) & (1<<1)) == 0 ) {
            return true;
        }
    }
    return false;
}

bool GeneralLogic::ifXCWorking(uint8 slot) {
    if( CardCPU::itsSlot() == slot ) {
        uint8* reg = reinterpret_cast<uint8*>(WORKING_INDICATE);
        if( reg ) {
            return ((*reg) & 1) == 0;
        }
    }
    else {
        uint8* reg = reinterpret_cast<uint8*>(WORKING_INDICATE2);
        if( reg ) {
            return ((*reg) & 1) == 0;
        }
    }
    return false;
}

void GeneralLogic::openEZBUS() {
    uint8* reg = reinterpret_cast<uint8*>(WORKING_INDICATE2);
    if( reg ) {
        *reg |= 0x80;
    }
}
void GeneralLogic::closeEZBUS() {
    uint8* reg = reinterpret_cast<uint8*>(WORKING_INDICATE2);
    if( reg ) {
        *reg &= ~0x80;
    }

}

void GeneralLogic::FSMStart() {
    uint8* reg = reinterpret_cast<uint8*>(FSM_START);
    if( reg ) {
        *reg ^= 0x80;
    }
}
//void GeneralLogic::FSMStop() {
//    uint8* reg = reinterpret_cast<uint8*>(FSM_START);
//    if( reg ) {
//        *reg &= ~0x80;
//    }
//
//}
void GeneralLogic::startWTD() {
    uint8* reg = reinterpret_cast<uint8*>(WTD);
    if( reg ) {
        *reg = 0x80;
    }
}

void GeneralLogic::stopWTD() {
    uint8* reg = reinterpret_cast<uint8*>(WTD);
    if( reg ) {
        *reg = 0;
    }
}

void GeneralLogic::feedWTD() {
    uint8* reg = reinterpret_cast<uint8*>(WTD);
    if( reg ) {
        *reg = 0xAA;
    }
}

bool GeneralLogic::ifRemoteExist(void) {
    uint8* regL = reinterpret_cast<uint8*>(Remote_Sending_L);
    uint8* regH = reinterpret_cast<uint8*>(Remote_Sending_H);
    if( regL && regH ) {
        if( (((*regH) << 8) | (*regL)) == 0 ) {
            return true;
        }
    }
    return false;
}

