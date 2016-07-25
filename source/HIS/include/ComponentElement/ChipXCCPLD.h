/*
 * ChipXCCPLD.h
 *
 *  Created on: 2014��6��26��
 *      Author: Administrator
 */

#ifndef CHIPXCCPLD_H_
#define CHIPXCCPLD_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;

class ChipXCCPLD: public BaseChip {
    typedef enum {
        LED_WRK, LED_MAJ, LED_MIN, LED_LOSA, LED_ALMA, LED_LOSB, LED_ALMB
    }XC_LED_NAME;
	ChipXCCPLD();
public:
	ChipXCCPLD(CBaseSlot* slt);
	virtual ~ChipXCCPLD();
	virtual Chip_INIT_RESULT ChipInit(void) {
		return succeed;
	}
	virtual std::string GetVerInfo(void);

	void turnLedWorkOn(bool on);
	void turnLedMajOn(bool on);
	void turnLedMinOn(bool on);
	void turnLedLosAOn(bool on);
    void turnLedAlmAOn(bool on);
    void turnLedLosBOn(bool on);
    void turnLedAlmBOn(bool on);

private:
	RegisterAccess* ra;
	std::string ChipVerInfo;
	virtual std::string GetChipVerInfo(const std::string, const uint16);
	static const uint16 REG_OPT_DISABLE = 0x2006;
    static const uint16 REG_VER_CPLD_GENERALLOGIC_XY   = 0x0010;
    static const uint16 REG_VER_CPLD_GENERALLOGIC_Z   = 0x0011;
    static const uint16 REG_VER_CPLD_UOPTLOGIC   = 0x2010;
    static const uint16 REG_VER_FPGA_PCMLOGIC    = 0x8C0F;
    static const uint16 REG_VER_FPGA_SDHLOGIC    = 0xC010;
    static const uint16 REG_XC_LEDS              = 0x2fff;
    void turnLedOn(XC_LED_NAME name, bool on);

};

#endif /* CHIPXCCPLD_H_ */
