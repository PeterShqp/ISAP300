/*
 * Chip8STM1CPLD.h
 *
 *  Created on: 2014-5-16
 *      Author: Administrator
 */

#ifndef CHIP8STM1CPLD_H_
#define CHIP8STM1CPLD_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;


class Chip8STM1CPLD : public BaseChip {
    static const uint16 REG_DCC_INTR_EN = 0x0000;    //bit7~4
    static const uint16 REG_LOAD_OPTION = 0x0010;    //bit 0 program;
                                                     //bit 1/2 pcm/sdh INIT
                                                     //bit 3/4 pcm/sdh DONE
                                                     //bit 15 ezbus_mode 0=loadmode
    static const uint16 REG_LOAD_BUF_STMLGC1 = 0x0011;
    static const uint16 REG_LOAD_BUF_STMLGC2 = 0x0012;

    static const uint16 REG_VER_NUM = 0x20ff;


    static const uint16 REG_RST_RC7883 = 0x0003;
    static const uint16 REG_LED_2 = 0x0004; //bit7~0 alm7~0


    Chip8STM1CPLD();
public:
    Chip8STM1CPLD(CBaseSlot* slt);
    virtual ~Chip8STM1CPLD();

    virtual Chip_INIT_RESULT ChipInit(void);

    Chip_INIT_RESULT updataTwoFPGA(bool force = false, const char* pcmFname = 0, const char* sdhFname = 0);

    void enableDCC(void);
    void disableDCC(void);

    void resetRC7883();

    void portLEDAlarmOn(uint8 ch, bool sel);
    virtual std::string GetVerInfo(void);

private:
    RegisterAccess* regAccess;
	std::string ChipVerInfo;
	virtual std::string GetChipVerInfo(  const std::string ,const uint16);
	static const uint16 REG_VER_CPLD   = 0x0013;
	static const uint16 REG_VER_CPLD_STMLOGIC_1   = 0x1310;
	static const uint16 REG_VER_CPLD_STMLOGIC_2   = 0x2010;
	//    bool initState;

    bool prepareUpdata(void);   //first, pull down program and check if init is low,
                                //second, pull up program and check if init is high
    bool ifSucceed(void);  //DONE is high

};

#endif /* CHIP8STM1CPLD_H_ */
