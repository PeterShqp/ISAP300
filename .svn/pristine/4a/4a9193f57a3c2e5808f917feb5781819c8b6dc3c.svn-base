/*
 * RscVC4.h
 *
 *  Created on: 2013-11-30
 *      Author: Administrator
 */

#ifndef RSCVC4_H_
#define RSCVC4_H_

#include "ConnectableResource.h"

#include "STMConfigDataDefine.h"
//typedef struct {
//    uint8 J1ModeTransmit; //0 is 16bytes, 1 is single byte
//    uint8 J1ModeReceive;
//    uint8 J1Transmit[64];
//    uint8 J1Expect[64];
//}VC4_Config_Data_T;

class DriverSDH;
class RscVC12;

class RscVC4 : public ConnectableResource {
public:
    RscVC4(uint32 uid, ConfigCell* card, DriverSDH& chipDriver, VC4_Config_Data_T* cfg, bool paired = false);
    virtual ~RscVC4();

//    virtual std::string& getName(void);
    virtual int getSpeedLevel(void);
    virtual bool setFrom(int fromHID);
    virtual uint32 getHID();

    static uint8 itsHardwareID(uint32 uid);

    uint32 getB3Counter(void);
    uint8* getJ1Transmit(uint32* len);  //read config
    uint8* getJ1Transmit(void);         //read register
    uint8* getJ1Expected(uint32* len);  //read config
    uint8* getJ1Expected(void);         //read register
    uint8* getJ1Received(uint32* len);

    bool setJ1Transmit(uint8* d, uint32 len, bool save = true);
    bool setJ1Expected(uint8* d, uint32 len, bool save = true);

    uint8 getJ1TLen(void);
    bool setJ1TLen(uint8 len, bool save = true);
    uint8 getJ1RLen(void);
    bool setJ1RLen(uint8 len, bool save = true);

    bool getAUAIS(void);
    bool getAULOP(void);
    bool getHPRDI(void);
    bool getHPREI(void);
    bool getHPTIM(void);
    bool getHPSLM(void);
    bool getHPUNEQ(void);

private:
//    std::string name;
    DriverSDH& driver;
    RscVC12* vc12_obj[63];
    VC4_Config_Data_T* ConfigData;
    int HID;
private:
    static std::map<uint32, RscVC4*> group;
public:
    /* group option */
    static RscVC4* getInstance(uint32 uid) {
        std::map<uint32, RscVC4*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscVC4* getFirstInstance(void) {
        std::map<uint32, RscVC4*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscVC4* getNextInstance(uint32 suid) {
        std::map<uint32, RscVC4*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* RSCVC4_H_ */
