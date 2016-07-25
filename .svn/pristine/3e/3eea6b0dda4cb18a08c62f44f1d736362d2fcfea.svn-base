/*
 * Slot155Channel.h
 *
 *  Created on: 2014-5-18
 *      Author: Administrator
 */

#ifndef SLOT155CHANNEL_H_
#define SLOT155CHANNEL_H_

#include "ConnectableResource.h"
#include <string>

class DriverSDH;
class PairRscSDHChannel;

class Slot155Channel : public ConnectableResource {
public:
    Slot155Channel(uint32 uid, PairRscSDHChannel* mapLink, ConfigCell* card, DriverSDH& d);
    virtual ~Slot155Channel();

//    virtual std::string& getName(void) {
//        return name;
//    };
    virtual int getSpeedLevel(void) {
        return 2;
    };
    virtual bool setFrom(int fromHID); // if fromHID < 0, disconnect
    virtual uint32 getHID();

    uint32 getDownStream(void);
    uint32 getUpStream(void);

private:
//    std::string name;
    DriverSDH& driver;
    PairRscSDHChannel* MappingCh;

private:
    static std::map<uint32, Slot155Channel*> group;
public:
    /* group option */
    static Slot155Channel* getInstance(uint32 uid) {
        std::map<uint32, Slot155Channel*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static Slot155Channel* getFirstInstance(void) {
        std::map<uint32, Slot155Channel*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static Slot155Channel* getNextInstance(uint32 suid) {
        std::map<uint32, Slot155Channel*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* SLOT155CHANNEL_H_ */
