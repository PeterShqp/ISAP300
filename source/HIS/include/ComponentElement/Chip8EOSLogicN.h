/*
 * Chip8EOSLogicN.h
 *
 *  Created on: 2014��12��22��
 *      Author: Administrator
 */

#ifndef CHIP8EOSLOGICN_H_
#define CHIP8EOSLOGICN_H_

#include "FPGAChip.h"

class CBaseSlot;

class Chip8EOSLogicN : public FPGAChip {
public:
    Chip8EOSLogicN(CBaseSlot* slt);
    virtual ~Chip8EOSLogicN();

    virtual Chip_INIT_RESULT ChipInit(void);
    virtual std::string GetChipVerInfo( const std::string ,const uint16){
        return 0;
    }

private:
    RegisterAccess* ra;

    void initRegs(void);
};

#endif /* CHIP8EOSLOGICN_H_ */
