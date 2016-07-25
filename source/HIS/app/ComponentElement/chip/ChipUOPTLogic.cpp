/*
 * ChipUOPTLogic.cpp
 *
 *  Created on: 2013-12-8
 *      Author: Administrator
 */

#include "ChipUOPTLogic.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include <stdio.h>
#include "os.h"
#include "SysError.h"
#include <iostream>
#include "s1l_line_input.h"
#include "GeneralLogic.h"

static const std::string chipName = "UOPTLogic";

const char pcmlgcFname[] = "pcmlogic.bit";
const char sdhlgcFname[] = "sdhlogic.bit";
char fileBuf[340736];

ChipUOPTLogic::ChipUOPTLogic(CBaseSlot* slt) : BaseChip(chipName) {
    initState = false;
    regAccess = slt->getRegisterAccess();
}

ChipUOPTLogic::~ChipUOPTLogic() {

}


Chip_INIT_RESULT ChipUOPTLogic::updataTwoFPGA(bool force, const char* pcmFname, const char* sdhFname) {
    if( !GeneralLogic::instance().ifColdStart() ) {
        if( ifSucceed() ) {
            std::cout << "FPGAs have been running" << std::endl;
            display_prompt();
            return donothing;
        }
    }
    FILE* fpcm = 0;
    FILE* fsdh = 0;
    if( pcmFname ) {
        fpcm = fopen(pcmFname, "rb");
    }
    else {
        fpcm = fopen(pcmlgcFname, "rb");
    }
    if( sdhFname ) {
        fsdh = fopen(sdhFname, "rb");
    }
    else {
        fsdh = fopen(sdhlgcFname, "rb");
    }

    if( !fpcm && !fsdh) {
        std::cout << "!!!No update file exist!!!" << std::endl;
    }
    else if( !fpcm ) {
        fclose(fsdh);
        std::cout << "!!!No pcmlogic upload file exist!!!" << std::endl;
    }
    else if( !fsdh ) {
        fclose(fpcm);
        std::cout << "!!!No sdhlogic upload file exist!!!" << std::endl;
    }
    else { //all file is ok
        if( prepareUpdata() ) {
//            int pcmLoadBytes = 0;
//            int sdhLoadBytes = 0;
            std::cout << "Loading pcmlogic first." << std::endl;

            uint32 readCount = fread(fileBuf, 1, sizeof(fileBuf), fpcm);
            fclose(fpcm);

            if( readCount > 0 ) {
                for( int i = 0; i < sizeof(fileBuf); i+=2 ) {
                    while( (regAccess->readReg(REG_LOAD_BUF_WE) & 0x40) == 0 );
                    regAccess->writeReg( REG_LOAD_BUF_PCM, (fileBuf[i]<<8) | fileBuf[i+1], 0 );
                }
            }
            std::cout << std::endl;
            std::cout << "Loading sdhlogic second." << std::endl;

//            tsk_lock();
            readCount = fread(fileBuf, 1, sizeof(fileBuf), fsdh);
//            tsk_unlock();
            fclose(fsdh);

            if( readCount > 0 ) {
                for( int i = 0; i < sizeof(fileBuf); i+=2 ) {
                    while( (regAccess->readReg(REG_LOAD_BUF_WE) & 0x80) == 0 );
                    regAccess->writeReg( REG_LOAD_BUF_SDH, (fileBuf[i]<<8) | fileBuf[i+1], 0 );
                }
            }

            std::cout << std::endl;
            bool rtn =  ifSucceed();
            if( rtn ) {
                std::cout << "update FPGAs succeed!" << std::endl;
                display_prompt();
                return succeed;
           }
            else {
                std::cout << "!!!update FPGAs failed!!!" << std::endl;
            }
            display_prompt();
       }
        else {
            std::cout << "!!!Prog & init PINs error.!!!" << std::endl;

        }

    }
    return failed;
}

bool ChipUOPTLogic::prepareUpdata(void) {
    /* program pin pull down */
    uint16 regData = regAccess->readReg(REG_LOAD_OPTION);
    regData &= ~0x7f;
    regAccess->writeReg(REG_LOAD_OPTION, regData);

    /* delay 10ms */
    os_dly_wait(1);

    /* check if INIT is low */
    regData = regAccess->readReg(REG_LOAD_OPTION);
    if( (regData & 6) != 0 ) {
        return false;
    }

    /* program pin pull up */
    regData = regAccess->readReg(REG_LOAD_OPTION);
    regData |= 1;
    regAccess->writeReg(REG_LOAD_OPTION, regData);

    /* delay 10ms */
    os_dly_wait(1);

    /* check if INIT is high */
    regData = regAccess->readReg(REG_LOAD_OPTION);
    if( (regData & 6) != 6 ) {
        return false;
    }

    /* enter load mode */
    regData &= ~(1<<15);
    regAccess->writeReg(REG_LOAD_OPTION, regData);

    return true;

}


bool ChipUOPTLogic::ifSucceed(void) {
    /* exit load mode */
    uint16 regData = regAccess->readReg(REG_LOAD_OPTION);
    regData |= (1<<15);
    regAccess->writeReg(REG_LOAD_OPTION, regData);

    /* check if DONE is HIGH */
    regData = regAccess->readReg(REG_LOAD_OPTION);
    if( (regData & 0x18) != 0x18 ) {
        return false;
    }
    return true;
}


Chip_INIT_RESULT ChipUOPTLogic::ChipInit(void) {
    dccInterruptEnable(false);
    return updataTwoFPGA();
}


bool ChipUOPTLogic::ifSFPExist(uint8 sn) {
    uint16 regData = regAccess->readReg(REG_SFP_STA_CTRL);
    regData &= (1 << sn);
    return regData == 0;

}
bool ChipUOPTLogic::ifSFPLos(uint8 sn) {
    uint16 regData = regAccess->readReg(REG_SFP_STA_CTRL);
    regData &= (1 << (sn+2));
    return regData != 0;

}
bool ChipUOPTLogic::ifSFPTxEnable(uint8 sn) {
    uint16 regData = regAccess->readReg(REG_SFP_STA_CTRL);
    regData &= (1 << (sn+4));
    return regData != 0;

}
void ChipUOPTLogic::setSFPTxDisable(uint8 sn, bool en) {
    uint16 regData = regAccess->readReg(REG_SFP_STA_CTRL);
    regData &= ~(1 << (sn+4));
    regData |= (en << (sn+4));
    regAccess->writeReg(REG_SFP_STA_CTRL, regData);
}
void ChipUOPTLogic::dccInterruptEnable(bool en) {
    uint16 regData = (en ? 1: 0);
    regAccess->writeReg(REG_INTRR_EN, regData);
}

void ChipUOPTLogic::resetRemoteDevice(uint8 port) {
    uint16 mask = (1 << 4);
    if( port == 1 ) {
        mask = (1 << 5);
    }
    uint16 regData = regAccess->readReg(REG_SFP_STA_CTRL);
    regData |= mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //1
    regData &= ~mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //0
    os_dly_wait(2); //0
    regData |= mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //1
    os_dly_wait(2); //1
    regData &= ~mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //0
    regData |= mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //1
    regData &= ~mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //0
    regData |= mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //1
    regData &= ~mask;
    regAccess->writeReg(REG_SFP_STA_CTRL, regData, 0);
    os_dly_wait(2); //0

}

