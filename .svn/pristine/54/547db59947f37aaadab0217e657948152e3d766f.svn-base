/*
 * RscSDHChannel.h
 *
 *  Created on: 2013-11-28
 *      Author: Administrator
 */

#ifndef RSCSDHCHANNEL_H_
#define RSCSDHCHANNEL_H_

#include "ConnectableResource.h"
#include <string>

class ChipCP1121A;
class RscSDHChannel : public ConnectableResource {
public:
    RscSDHChannel(uint32 uid, ConfigCell* card, ChipCP1121A& chipDriver, bool paired);
    virtual ~RscSDHChannel();

//    virtual std::string& getName(void);
    virtual int getSpeedLevel(void);
    virtual bool setFrom(int fromHID);
    virtual uint32 getHID();

    static uint8 itsHardwareID(uint32 uid);

//    uint32 getDownStream(void) {
//        return downStream;
//    };
//
//    void setDownStream(uint32 d) {
//        downStream = d;
//    };

private:
//    uint32 downStream;
//    std::string name;
    ChipCP1121A& driver;
private:
    static std::map<uint32, RscSDHChannel*> group;
public:
    /* group option */
    static RscSDHChannel* getInstance(uint32 uid) {
        std::map<uint32, RscSDHChannel*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscSDHChannel* getFirstInstance(void) {
        std::map<uint32, RscSDHChannel*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscSDHChannel* getNextInstance(uint32 suid) {
        std::map<uint32, RscSDHChannel*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* RSCSDHCHANNEL_H_ */
