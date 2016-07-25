/*
 * Card16FE1.cpp
 *
 *  Created on: 2015年6月17日
 *      Author: Administrator
 */

#include "Card16FE1.h"
#include "CardTypeID_define.h"
#include "SysError.h"
#include <iostream>
#include "PairSTBus.h"
#include "UID.h"
#include "PortFE1.h"
#include "FE1CardAlarmModule.h"
//#include "DCCXe1Rcv.h"
//#include "DCCXe1Snd.h"
#include "CardDXC.h"
#include "ObjectReference.h"
#include "F16E1PCMClockSource.h"

#include "XCPair.h"
#include "ClockSourceManager.h"
#include "ChannelSabit.h"
#include "ChannelTsDcn.h"
#include "NMPort.h"

Card16FE1::Card16FE1(std::string& name,CBaseSlot* slot) : CBaseCard(name, slot), fpga(slot) {
    // TODO Auto-generated constructor stub
    Chip_INIT_RESULT rst = fpga.ChipInit();
    if( rst == failed ) {
        throw SysError("!!!Card 16FE1 E1Logic init error!!!");
    }
    else if( rst == donothing ) {
        std::cout << fpga.itsName() << " have been running!" << std::endl;
    }
    if( !fetchConfig() ) {
        throw SysError("!!!Card 16E1 config data error!!!");
    }
    openHstbus(slot->GetSn(), true);
    ST_E1 info;
    info.slot = slot->GetSn();
    for (int i = 0; i < 16; ++i) {
        info.E1 = i;
        uint32 e1uid = UID::makeUID(&info);
        PairSTBus* pstbus = getConnectedStbus(e1uid);
        fe1_obj[i] = new PortFE1(e1uid, this, &ConfigData.fe1Data[i], fpga);
    }

    CardDXC* dxc = ObjectReference::getWorkingDXC();
    ST_Clock_source clkinfo;
    clkinfo.slot = slot->GetSn();
    clkinfo.type = UID::type_pcm_recover_clock;
    for (int i = 0; i < 16; ++i) {
        clkinfo.sn = i;
        uint32 index = UID::makeUID(&clkinfo);
        clockSource[i] = new F16E1PCMClockSource(index, i, dxc->getChipPCMLogic(), fpga);
        XCPair::instance().getPcmClockManager()->addClockSource(clockSource[i]);
    }

    cardversionInfo = fpga.GetVerInfo();

    AM = new FE1CardAlarmModule(this);
    AM->initModule();

    /*
     * 建立管理接口
     */
    ST_NM_Channel nminfo;
    nminfo.slot = slot->GetSn();
    nminfo.subtype = subtype_sabit;
    for (int i = 0; i < 16; ++i) {
        nminfo.sn = i;
        uint32 index = UID::makeUID(&nminfo);
        nmch_dcc[i] = new ChannelSabit(index, fpga);
        nmch_dcn[i] = new ChannelTsDcn(index, fpga);

        nmport[i] = new NMPort(fe1_obj[i], &ConfigData.fe1Data[i].nmportCfg);
        if( nmport[i] == 0 || nmch_dcc[i] == 0 || nmch_dcn[i] == 0 ) {
            throw SysError("!!!new object failed!!!");
        }

        nmport[i]->addNmChannel(nmch_dcc[i]);//must dcc firse
        nmport[i]->addNmChannel(nmch_dcn[i]);//must dcn second
        nmport[i]->start();
    }
    fpga.sabitInterruptEnable(true);
}



Card16FE1::~Card16FE1() {
    fpga.sabitInterruptEnable(false);
    openHstbus(getSn(), false);

    delete AM;
    for (int i = 0; i < 16; ++i) {
        XCPair::instance().getPcmClockManager()->removeClockSource(clockSource[i]);
        delete clockSource[i];
    }

    for (int i = 0; i < 16; ++i) {
        nmport[i]->stop();
        delete nmport[i];
        delete nmch_dcn[i];
        delete nmch_dcc[i];
    }
    for (int i = 0; i < 16; ++i) {
        delete fe1_obj[i];
    }
}

std::string& Card16FE1::GetCardVerInfo() {
    return cardversionInfo;
}

int Card16FE1::GetCartTypeID() {
    return FE1_16_CARD_TYPEID;
}

void Card16FE1::loadDefaultData(void) {
    ConfigCell::loadDefaultData();
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < UpE1_Signal_Count; ++j) {
            ConfigData.AlarmData.UpE1AlmData[i].Property[j].level = 2;
            ConfigData.AlarmData.UpE1AlmData[i].Property[j].mask = 0;
            ConfigData.AlarmData.UpE1AlmData[i].Property[j].trap = 0;
        }
        ConfigData.fe1Data[i].TXEN = 1;
        ConfigData.fe1Data[i].nmportCfg.type = 1;
        ConfigData.fe1Data[i].nmportCfg.porten = 1;
        ConfigData.fe1Data[i].nmportCfg.dcnCH.bitMap = (1<<30);
        ConfigData.fe1Data[i].nmportCfg.topodir = 7+i;
    }
}

PairSTBus* Card16FE1::getConnectedStbus(uint32 e1uid) {
    UN_Info info = UID::breakUID(e1uid);
    ST_Stbus stbus;
    stbus.slot = info.E1.slot;
    stbus.stbus = info.E1.E1 + 1;
    stbus.xcsn = 0;
    uint32 stbusuid = UID::makeUID(&stbus);
    PairResource* p = PairResource::getInstance(stbusuid);
    return dynamic_cast<PairSTBus*>(p);
}

void Card16FE1::resetRemoteDevice(uint8 port) {
    fpga.resetRemote(port);
}

void Card16FE1::openHstbus(uint8 sn, bool open) {
    CardDXC* dxc = ObjectReference::getWorkingDXC();
    if( dxc ) {
        dxc->openHstbus(sn, open);
    }
}

void Card16FE1::closeInterrupt(void) {
    fpga.sabitInterruptEnable(false);
}
