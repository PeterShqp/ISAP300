/*
 * Chip8EOSLogicN2.h
 *
 *  Created on: 2014��12��23��
 *      Author: Administrator
 */

#ifndef CHIP8EOSLOGICN2_H_
#define CHIP8EOSLOGICN2_H_

#include "FPGAChip.h"

class Chip8EOSLogicN2: public FPGAChip {
public:
    Chip8EOSLogicN2(CBaseSlot* slt);
    virtual ~Chip8EOSLogicN2();

    virtual Chip_INIT_RESULT ChipInit(void);
    virtual std::string GetChipVerInfo( const std::string ,const uint16){
        return 0;
    }
    virtual uint16 getModeRegAddr(void) {
        return 0;
    };
};

#endif /* CHIP8EOSLOGICN2_H_ */
