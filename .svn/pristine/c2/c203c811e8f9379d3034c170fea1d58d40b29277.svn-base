/*
 * Chip8EOSLogic.h
 *
 *  Created on: 2014-3-26
 *      Author: Administrator
 */

#ifndef CHIP8EOSLOGIC_H_
#define CHIP8EOSLOGIC_H_

#include "FPGAChip.h"

class CBaseSlot;
class RegisterAccess;

class Chip8EOSLogic: public FPGAChip {
public:
    Chip8EOSLogic(CBaseSlot* slt);
    virtual ~Chip8EOSLogic();

    virtual Chip_INIT_RESULT ChipInit(void);
	virtual std::string GetChipVerInfo( const std::string ,const uint16){
		return 0;
	}

private:
    RegisterAccess* ra;

    void initRegs(void);

};

#endif /* CHIP8EOSLOGIC_H_ */
