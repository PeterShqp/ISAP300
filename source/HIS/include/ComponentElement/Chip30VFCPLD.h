/*
 * Chip30VFCPLD.h
 *
 *  Created on: 2014��6��26��
 *      Author: Administrator
 */

#ifndef CHIP30VFCPLD_H_
#define CHIP30VFCPLD_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;

class Chip30VFCPLD : public BaseChip{
	Chip30VFCPLD();
public:
	Chip30VFCPLD(CBaseSlot* slt);
	virtual ~Chip30VFCPLD();

	 virtual Chip_INIT_RESULT ChipInit(void){
		 return donothing;
	 }

	bool Resetchip(void);
	virtual std::string GetVerInfo(void);

private:
	RegisterAccess* ra;

	std::string ChipVerInfo;
	virtual std::string GetChipVerInfo( const std::string ,const uint16);
	static const uint16 REG_VER_CPLD   = 0x0010;//bit15~bit12,X;bit11~bit8,Y,bit7~bit0,Z.

	static const uint16 REG_RST_CPLD   = 0x0000;//bit0 is used to reset 88f54
};


#endif /* CHIP30VFCPLD_H_ */
