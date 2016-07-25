/*
 * Chip8EOSCPLD.h
 *
 *  Created on: 2014-5-23
 *      Author: Administrator
 */

#ifndef CHIP8EOSCPLD_H_
#define CHIP8EOSCPLD_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;


class Chip8EOSCPLD : public BaseChip {
	Chip8EOSCPLD();
public:
    Chip8EOSCPLD(CBaseSlot* slt);
    virtual ~Chip8EOSCPLD();

    virtual Chip_INIT_RESULT ChipInit(void);

    uint16 smiRead(uint16 phy, uint16 reg);
    bool smiWrite(uint16 phy, uint16 reg, uint16 data);
    virtual std::string GetVerInfo(void);
private:
    RegisterAccess* ra;
	std::string ChipVerInfo;
	virtual std::string GetChipVerInfo( const std::string ,const uint16);
	static const uint16 REG_VER_CPLD   = 0x0010;
	static const uint16 REG_VER_FPGA_ETHLOGIC   = 0x1010;

    static const uint16 REG_SMI_WDATA     = 0x0011;
    static const uint16 REG_SMI_Reg_ADDR  = 0x0012;
    static const uint16 REG_SMI_Phy_ADDR  = 0x0013; //bit15 write(1) read(0) ready(1) busy(0)
    static const uint16 REG_SMI_RDATA     = 0x0014;

    static const uint16 REG_PLL_ENABLE    = 0x0021; //bit0 enable(1), disable(0)
                                                    //bit2 PLL locked(1)
                                                    //bit15 ip108 reset
    static const uint16 REG_CLOCK_SWITCH  = 0x0022; //bit0
};

#endif /* CHIP8EOSCPLD_H_ */
