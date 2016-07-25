/*
 * Chip48E1CPLD.h
 *
 *  Created on: 2014��6��25��
 *      Author: Administrator
 */

#ifndef CHIP48E1CPLD_H_
#define CHIP48E1CPLD_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;



class Chip48E1CPLD : public BaseChip {
	Chip48E1CPLD();
public:
	Chip48E1CPLD(CBaseSlot* slt);
	virtual ~Chip48E1CPLD();
    virtual Chip_INIT_RESULT ChipInit(void){
    	return donothing;
    }

	virtual std::string GetVerInfo(void);

private:
	RegisterAccess* ra;
	std::string ChipVerInfo;
	virtual std::string GetChipVerInfo(  const std::string ,const uint16);
    static const uint16 REG_VER_CPLD   = 0x0010;
    static const uint16 REG_VER_CPLD_E1PORTLOGIC_1   = 0x2010;
    static const uint16 REG_VER_CPLD_E1PORTLOGIC_2   = 0x3010;
    static const uint16 REG_VER_CPLD_E1PORTLOGIC_3   = 0x4010;
    static const uint16 REG_VER_FPGA_E1LOGIC   = 0x1010;


};

#endif /* CHIP24E1CPLD_H_ */
