/*
 * FPGAChip.cpp
 *
 *  Created on: 2014-4-1
 *      Author: Administrator
 */

#include "FPGAChip.h"
#include "CBaseSlot.h"
#include <iostream>
#include <stdio.h>
#include "s1l_line_input.h"
#include "RegisterAccess.h"
#include "os.h"
#include "GeneralLogic.h"
#include "CPPTools.h"

//extern char fileBuf[340736];

FPGAChip::FPGAChip(const std::string& name, CBaseSlot* slt, uint16 offset) : BaseChip(name) {

    regAccess = slt->getRegisterAccess();
    REG_ADD_OFFSET = offset;
}

FPGAChip::~FPGAChip() {
    // TODO Auto-generated destructor stub
}

Chip_INIT_RESULT FPGAChip::updataFPGA(void) {
    if( !GeneralLogic::instance().ifColdStart() ) {
        if( ifSucceed() ) {
            std::cout << "FPGAs have been running" << std::endl;
//            display_prompt();
            return donothing;
        }
    }
    std::cout << "Start update FPGA: " << itsName() << std::endl;
    std::string fname = itsName() + ".bit";
    FILE* fpcm = fopen(fname.c_str(), "rb");
    if( fpcm ) {
//        /*check file's CRC*/
//        uint32 crcInFile = 0;
//        CPPTools::getFileCRC(fname.c_str(), &crcInFile);
//		uint32 CRCReal = 0;
//		CPPTools::calculateFileCRC(fname.c_str(), &CRCReal, 16);
//		if( crcInFile != CRCReal ) {
//#ifdef EZ_DEBUG
//		    std::cout << "FPGA: " << itsName() << " file is damaged!!"<< std::endl;
//#endif
//		    return failed;
//		}

        if( prepareUpdata() ) {
            fseek(fpcm, 0, SEEK_END);
            uint32 fileSize = ftell(fpcm);
            char* fileBuf = new char[fileSize];
            fseek(fpcm, 0, SEEK_SET);
            uint32 readCount = fread(fileBuf, 1, fileSize, fpcm);
            fclose(fpcm);

            if( readCount > 0 ) {
                for( int i = 0; i < fileSize; i+=2 ) {
//                    while( regAccess->readReg(REG_LOAD_WBusy) == 1 );
                    regAccess->writeReg( REG_LOAD_BUF+REG_ADD_OFFSET, (fileBuf[i]<<8) | fileBuf[i+1]);
                }
            }
            delete []fileBuf;

            std::cout << std::endl;
            if( ifSucceed() ) {
                std::cout << "update FPGAs succeed!" << std::endl;
//                display_prompt();
                return succeed;
            }
            else {
                std::cout << "!!!update FPGAs failed!!!" << std::endl;
//                display_prompt();
            }
       }
        else {
            std::cout << "!!!Prog & init PINs error.!!!" << std::endl;

        }

    }
    else {
        std::cout << "!!!No update file exist!!!" << std::endl;

    }
    return failed;
}


bool FPGAChip::prepareUpdata(void) {
    /* program pin pull down */
    uint16 regData = regAccess->readReg(REG_LOAD_OPTION+REG_ADD_OFFSET);
    regData &= ~0x7f;
    regAccess->writeReg(REG_LOAD_OPTION+REG_ADD_OFFSET, regData);

    /* delay 10ms */
    os_dly_wait(1);

    /* check if INIT is low */
    regData = regAccess->readReg(REG_LOAD_OPTION+REG_ADD_OFFSET);
    if( (regData & 2) != 0 ) {
        return false;
    }

    /* program pin pull up */
    regData = regAccess->readReg(REG_LOAD_OPTION+REG_ADD_OFFSET);
    regData |= 1;
    regAccess->writeReg(REG_LOAD_OPTION+REG_ADD_OFFSET, regData);

    /* delay 10ms */
    os_dly_wait(1);

    /* check if INIT is high */
    regData = regAccess->readReg(REG_LOAD_OPTION+REG_ADD_OFFSET);
    if( (regData & 2) != 2 ) {
        return false;
    }

    /* enter load mode */
    regData = regAccess->readReg(getModeRegAddr());
    regData &= ~(1<<15);
    regAccess->writeReg(getModeRegAddr(), regData);

    return true;

}


bool FPGAChip::ifSucceed(void) {
    /* exit load mode */
    uint16 regData = regAccess->readReg(getModeRegAddr());
    regData |= (1<<15);
    regAccess->writeReg(getModeRegAddr(), regData);

    /* check if DONE is HIGH */
    regData = regAccess->readReg(REG_LOAD_OPTION+REG_ADD_OFFSET);
    if( (regData & 0x08) != 0x08 ) {
        return false;
    }
    return true;
}
