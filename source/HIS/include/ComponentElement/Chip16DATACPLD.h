/*
 * Chip16DATACPLD.h
 *
 *  Created on: 2015��1��21��
 *      Author: Administrator
 */

#ifndef CHIP16DATACPLD_H_
#define CHIP16DATACPLD_H_
#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;
class Chip16DATACPLD: public BaseChip {
	Chip16DATACPLD();
public:
	Chip16DATACPLD(CBaseSlot* slt);
	virtual ~Chip16DATACPLD();
	virtual std::string GetVerInfo(void);
    virtual Chip_INIT_RESULT ChipInit(void){
    	return donothing;
    }
private:
	RegisterAccess* ra;
	virtual std::string GetChipVerInfo(  const std::string ,const uint16);
	static const uint16 REG_VER_CPLD   = 0x0010;
	std::string ChipVerInfo;
};

#endif /* CHIP16DATACPLD_H_ */
