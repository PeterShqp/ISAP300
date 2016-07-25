/*
 * Chip24E1CPLD.h
 *
 *  Created on: 2014��6��25��
 *      Author: Administrator
 */

#ifndef CHIP24E1CPLD_H_
#define CHIP24E1CPLD_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;



class Chip24E1CPLD : public BaseChip {
	Chip24E1CPLD();
public:
	Chip24E1CPLD(CBaseSlot* slt);
    Chip24E1CPLD(CBaseSlot* slt, const std::string& name);
	virtual ~Chip24E1CPLD();
    virtual Chip_INIT_RESULT ChipInit(void){
    	return donothing;
    }

	virtual std::string GetVerInfo(void);

protected:
	RegisterAccess* ra;
	virtual std::string GetChipVerInfo(  const std::string ,const uint16);
    static const uint16 REG_VER_CPLD   = 0x0010;
    static const uint16 REG_VER_CPLD_E1PORTLOGIC_1   = 0x2010;
    static const uint16 REG_VER_CPLD_E1PORTLOGIC_2   = 0x3010;
    static const uint16 REG_VER_CPLD_E1PORTLOGIC_3   = 0x4010;
    static const uint16 REG_VER_FPGA_E1LOGIC   = 0x1010;
	std::string ChipVerInfo;
private:

};

#endif /* CHIP24E1CPLD_H_ */
