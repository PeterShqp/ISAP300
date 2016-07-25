/*
 * FPGAChip.h
 *
 *  Created on: 2014-4-1
 *      Author: Administrator
 */

#ifndef FPGACHIP_H_
#define FPGACHIP_H_

#include "BaseChip.h"

class RegisterAccess;
class CBaseSlot;


class FPGAChip : public BaseChip {
    FPGAChip();
public:
    FPGAChip(const std::string& name, CBaseSlot*, uint16 offset = 0);
    virtual ~FPGAChip();

    virtual Chip_INIT_RESULT ChipInit(void) = 0;
    virtual uint16 getModeRegAddr(void) {
        return REG_LOAD_OPTION + REG_ADD_OFFSET;
    };


	Chip_INIT_RESULT updataFPGA(void);
protected:
    RegisterAccess* regAccess;
private:
    bool prepareUpdata(void);   //first, pull down program and check if init is low,
                                //second, pull up program and check if init is high
    bool ifSucceed(void);  //DONE is high

    static const uint16 REG_LOAD_OPTION = 0x0000;    //bit 0 program;
                                                     //bit 1 INIT
                                                     //bit 3 DONE
                                                     //bit 15 ezbus_mode 0=loadmode
    static const uint16 REG_LOAD_BUF    = 0x0001;
    static const uint16 REG_LOAD_WBusy  = 0x0003;    //bit0 1 busy, 0 ready

    uint16 REG_ADD_OFFSET;

};

#endif /* FPGACHIP_H_ */
