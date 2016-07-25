/*
 * RscSDHBus.h
 *
 *  Created on: 2013-11-28
 *      Author: Administrator
 */

#ifndef RSCSDHBUS_H_
#define RSCSDHBUS_H_

#include <map>
#include "EZ_types.h"
#include "ConnectableResource.h"
#include <string>

class ChipCP1121A;
class RscSDHChannel;

class RscSDHBus : public ConnectableResource {
public:
    RscSDHBus(uint32 uid, ConfigCell* card, ChipCP1121A& chipDriver, bool paired = false);
    virtual ~RscSDHBus();

//    virtual std::string& getName(void);
    virtual int getSpeedLevel(void);
    virtual bool setFrom(int fromHID);
    virtual uint32 getHID();

    static uint8 itsHardwareID(uint32 uid);
private:
//    std::string name;
    ChipCP1121A& driver;
    RscSDHChannel* sdhch_obj[63];
private:
    static std::map<uint32, RscSDHBus*> group;
public:
    /* group option */
    static RscSDHBus* getInstance(uint32 uid) {
        std::map<uint32, RscSDHBus*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscSDHBus* getFirstInstance(void) {
        std::map<uint32, RscSDHBus*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscSDHBus* getNextInstance(uint32 suid) {
        std::map<uint32, RscSDHBus*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };

};

#endif /* RSCSDHBUS_H_ */
