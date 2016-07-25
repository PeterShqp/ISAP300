/*
 * PortE1.h
 *
 *  Created on: 2014-3-25
 *      Author: Administrator
 */

#ifndef PORTE1_H_
#define PORTE1_H_

#include "RealPortBase.h"
#include <string>

typedef struct {
//    Alarm_property_T alarm_property[E1_type_size];
    uint8 enable;
    uint8 sncp[8];
    char desc[32];
    uint8 dlen;
}UE1_Config_Data_T;

class ChipRC7883;
class CBaseCard;
class PairRscSDHChannel;

class PortE1: public RealPortBase {
    PortE1();
public:
    PortE1(uint32 uid, PairRscSDHChannel* mapLink, ConfigCell* BelongCard, ChipRC7883& dri, UE1_Config_Data_T* config);
    virtual ~PortE1();

    int getEnable(void);
    bool setEnable(int en, bool save = true);

    char* getDescription(uint32* len);
    bool setDescription(char* s, uint32 len, bool save = true);

    int getPortSn();
    int getPortSlot();

    uint8* getSNCP(uint32* len);
    bool setSNCP(uint8* ccid, uint32 len, bool save = true);
    uint32 getMappingLinkUID(void);
    uint32 getProtectPartner(void);

    virtual int setLoop(const int type);
    virtual bool ifEnabled(void) {
        return getEnable() != 0;
    };
//    virtual std::string& getName(void) {
//        return name;
//    };

    bool getLos(void);

private:
//    std::string name;
//    CBaseCard* BelongCard;
    ChipRC7883& driver;
    UE1_Config_Data_T* ConfigData;
    PairRscSDHChannel* MappingCh;
private:
    static std::map<uint32, PortE1*> group;
public:
    /* group option */
    static PortE1* getInstance(uint32 uid) {
        std::map<uint32, PortE1*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortE1* getFirstInstance(void) {
        std::map<uint32, PortE1*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortE1* getNextInstance(uint32 suid) {
        std::map<uint32, PortE1*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };

};

#endif /* PORTE1_H_ */
