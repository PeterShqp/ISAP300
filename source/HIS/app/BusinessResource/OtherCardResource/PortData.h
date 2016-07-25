/*
 * PortData.h
 *
 *  Created on: 2014-2-25
 *      Author: Administrator
 */

#ifndef PORTDATA_H_
#define PORTDATA_H_

#include "RealPortBase.h"

typedef struct {
    uint8 enable;
    char desc[32];
    uint8 dlen;
}DATA_Config_T;

class PairTSChannel;
class Chip16DATALogic;
class PortData : public RealPortBase {
public:
    PortData(uint32 uid, ConfigCell* card, PairTSChannel* t,Chip16DATALogic& dri,DATA_Config_T* config);
    virtual ~PortData();

//    virtual std::string& getName(void);
    uint8 getPortSn(void);

    int getPortType(void);
    int getEnable(void);
    bool setEnable(int en, bool save = true);
    virtual int setLoop(const int type);
    virtual bool ifEnabled(void) {
        return getEnable() != 0;
    };
	char* getDesc(uint32*);
	int setDesc(const char*, uint32);

private:
//    std::string name;
    PairTSChannel* ts;
    Chip16DATALogic& drive;
    DATA_Config_T* ConfigData;
private:
    static std::map<uint32, PortData*> group;
public:
    /* group option */
    static PortData* getInstance(uint32 uid) {
        std::map<uint32, PortData*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortData* getFirstInstance(void) {
        std::map<uint32, PortData*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortData* getNextInstance(uint32 suid) {
        std::map<uint32, PortData*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PORTDATA_H_ */
