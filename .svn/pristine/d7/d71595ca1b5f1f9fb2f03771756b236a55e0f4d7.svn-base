/*
 * GeneralLogic.h
 *
 *  Created on: 2013-11-27
 *      Author: Administrator
 */

#ifndef GENERALLOGIC_H_
#define GENERALLOGIC_H_

#include "BaseChip.h"



class GeneralLogic /*: public BaseChip*/ {
    static const uint32 BASE = 0xe2000000;
    static const uint32 SLOT_CS = (BASE + 0);
    static const uint32 START_TYPE = (BASE + 0xff);
    static const uint32 RESET_MCU  = (BASE + 0x5);

    static const uint32 WORKING_INDICATE = (BASE + 0x7); //bit7 WR slot
                                                         //bit1 OMU Working(0)
                                                         //bit0 XC Working(0)
    static const uint32 WORKING_INDICATE2 = (BASE + 0x8); //bit0 //bit7 ezbus open(1)

    static const uint32 FSM_START = (BASE + 9);         //bit7 enable(1)
                                                        //bit1 & 0    00 IDLE/ 01 standby/ 10 working
    static const uint32 WTD = (BASE + 10);      //bit 7 1 start, write clear

    static const uint32 Remote_Sending_L = (BASE + 0x0D);
    static const uint32 Remote_Sending_H = (BASE + 0x0E);

    static const uint8 WARM_START = 0x55;
    static const uint8 COLD_START = 0xaa;


    GeneralLogic();
    GeneralLogic(const GeneralLogic&);
    GeneralLogic& operator= (GeneralLogic&);
    virtual ~GeneralLogic();

    static GeneralLogic dev;
public:
    static GeneralLogic& instance(void) {
        return dev;
    };
    virtual uint8 getDataWide(void);

    void switchSlotTo(uint32 slt);
    void switchToIdle(void);

//    uint32 getCurrentCS(void) {
//        return CurrentCS;
//    };

    void setWarmStartType(void) {
        *((uint8*)START_TYPE) = WARM_START;
    };
    void setColdStartType(void) {
        *((uint8*)START_TYPE) = COLD_START;
    }

    bool ifColdStart(void) {
    	return getStartType() == COLD_START;//true;
    };
    void resetMcu(void) {
        *((uint8*)RESET_MCU) ^= 1;
    };

    bool assignSlot(uint8 slot);
    bool ifOMUWorking(void);

    bool ifXCWorking(uint8 slot);
    void openEZBUS();
    void closeEZBUS();

    void FSMStart();
//    void FSMStop();

    void startWTD();
    void stopWTD();
    void feedWTD();

    bool ifRemoteExist(void);

private:
//    uint32 CurrentCS;
    uint8 getStartType(void) {
    	return *((uint8*)START_TYPE);
    };

};

#endif /* GENERALLOGIC_H_ */
