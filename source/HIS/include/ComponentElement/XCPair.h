/*
 * XCPair.h
 *
 *  Created on: 2014��11��19��
 *      Author: Administrator
 */

#ifndef XCPAIR_H_
#define XCPAIR_H_

#include "ConfigCell.h"
#include "XCConfigDataDefine.h"

class CrossConnectionManager;
class ChipLM75A;
class PairPortSTM;
class PairRscSDHBus;
class PairSTBus;
class PairClockSource;
class BaseResource;
class ClockSourceManager;
class PairPortFE1;
//class PairPcmLocalClockSource;
//class PairPcmRecoverClockSource;

class XcPairSaver: public ConfigCell {
public:
    XcPairSaver();
    virtual ~XcPairSaver() {};

    virtual void loadDefaultData(void);
    virtual uint8* getConfigDataBuff(void) {
        return (uint8*) &ConfigData;
    };
    virtual uint32 getConfigDataLen(void) {
        return sizeof(ConfigData);
    };
private:
    Card_ConfigData_XC ConfigData;

};

class XCPair {
    XCPair() {
        ccm_obj = 0;
        sdh_clock = 0;
        pcm_clock = 0;

    };
    XCPair(XCPair&);
    XCPair& operator= (XCPair&);
    virtual ~XCPair() {};
    static XCPair pairCard;
public:
    static XCPair& instance(void) {
        return pairCard;
    };
    bool init(int subtype);
    void deInit(void);


    bool addResource(BaseResource*);
    bool removeResource(BaseResource*);
    CrossConnectionManager* getPccManager(void) {
        return ccm_obj;
    };
    ClockSourceManager* getSdhClockManager(void) {
        return sdh_clock;
    };
    ClockSourceManager* getPcmClockManager(void) {
        return pcm_clock;
    };
    XcPairSaver* getConfigSaver(void) {
        return saver;
    };
private:
    XcPairSaver* saver;
    CrossConnectionManager* ccm_obj;
    ClockSourceManager* sdh_clock;
    ClockSourceManager* pcm_clock;
    ChipLM75A* temperatureSensor;

    PairPortSTM* stm4_obj[2];
    PairPortFE1* fe1_obj[4];
    PairRscSDHBus* sdhbus_obj[10];
    PairSTBus* framee1_obj[8];
    PairSTBus* stbus_obj[5];
    PairSTBus* expstbus_obj[5][16];
    PairClockSource* xclocalclock_obj;
    PairClockSource* xcoptclock_obj[2];
    PairClockSource* xcextclock_obj[2];

    PairClockSource* pcmLocalClock_obj;
    PairClockSource* pcmRecoverClock_obj[8];
    int SubType;

};

#endif /* XCPAIR_H_ */
