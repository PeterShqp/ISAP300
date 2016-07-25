/*
 * PortFE1.h
 *
 *  Created on: 2015年6月22日
 *      Author: Administrator
 */

#ifndef PORTFE1_H_
#define PORTFE1_H_

#include "RealPortBase.h"
#include "FE1ConfigDataDefine.h"

class DriverPCM;

class PortFE1: public RealPortBase {
public:
    PortFE1(uint32 uid, ConfigCell* card, FE1_Config_Data_T* config, DriverPCM& dri, bool paired = false);
    virtual ~PortFE1();

    virtual int setLoop(const int type);
    virtual bool ifEnabled(void) {
        return getPortEnable() != 0;
    };

    uint8 getPortEnable(void);
    bool setPortEnable(uint8 en, bool save = true);

    char* getDescription(uint32* len);
    bool setDescription(char* s, uint32 len, bool save = true);

private:
    DriverPCM& driver;
    FE1_Config_Data_T* ConfigData;

private:
    static std::map<uint32, PortFE1*> group;
public:
    /* group option */
    static PortFE1* getInstance(uint32 uid) {
        std::map<uint32, PortFE1*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortFE1* getFirstInstance(void) {
        std::map<uint32, PortFE1*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortFE1* getNextInstance(uint32 suid) {
        std::map<uint32, PortFE1*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PORTFE1_H_ */
