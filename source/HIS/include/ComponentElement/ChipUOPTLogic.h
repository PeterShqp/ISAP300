/*
 * ChipUOPTLogic.h
 *
 *  Created on: 2013-12-8
 *      Author: Administrator
 */

#ifndef CHIPUOPTLOGIC_H_
#define CHIPUOPTLOGIC_H_

#include "BaseChip.h"

class CBaseSlot;
class RegisterAccess;

class ChipUOPTLogic : public BaseChip {
//    static const uint16 REG_CHIP_ID     = 0x2020;
    static const uint16 REG_LOAD_OPTION = 0x2000;    //bit 0 program;
                                                     //bit 1/2 pcm/sdh INIT
                                                     //bit 3/4 pcm/sdh DONE
                                                     //bit 15 ezbus_mode 0=loadmode
    static const uint16 REG_LOAD_BUF_PCM = 0x2001;
    static const uint16 REG_LOAD_BUF_SDH = 0x2002;
    static const uint16 REG_LOAD_BUF_WE = 0x2003;   //bit6 pcm buf writealbe(1), bit7 sdh buf writeable(1)
    static const uint16 REG_SFP_STA_CTRL = 0x2006;  //bit0 1 SFP Loss(1)
                                                    //bit2 3 SFP LOS(1)
                                                    //bit4 5 SFP Tx dis(1)

    static const uint16 REG_INTRR_EN    = 0x2040;   //bit0 open(1)
    static const uint16 REG_VER_NUM = 0x20ff;
public:
    ChipUOPTLogic(CBaseSlot* slt);
    virtual ~ChipUOPTLogic();
//    virtual bool initCompleted(void) {
//        return initState;
//    };
    virtual Chip_INIT_RESULT ChipInit(void);

    bool ifSFPExist(uint8 sn);
    bool ifSFPLos(uint8 sn);
    bool ifSFPTxEnable(uint8 sn);
    void setSFPTxDisable(uint8 sn, bool en);

    Chip_INIT_RESULT updataTwoFPGA(bool force = false, const char* pcmFname = 0, const char* sdhFname = 0);
    void dccInterruptEnable(bool en);
    void resetRemoteDevice(uint8 port);

private:
    RegisterAccess* regAccess;

    bool initState;

    bool prepareUpdata(void);   //first, pull down program and check if init is low,
                                //second, pull up program and check if init is high
    bool ifSucceed(void);  //DONE is high

};

#endif /* CHIPUOPTLOGIC_H_ */
