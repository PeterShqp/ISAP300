/*
 * CTSChannel.h
 *
 *  Created on: 2014-2-18
 *      Author: Administrator
 */

#ifndef CTSCHANNEL_H_
#define CTSCHANNEL_H_

#include "ConnectableResource.h"
#include <string>


class DriverPCM;

class CTSChannel : public ConnectableResource {
public:
    CTSChannel(uint32 uid, ConfigCell* card, DriverPCM* dri, bool paired = false);
    virtual ~CTSChannel();

//    virtual std::string& getName(void);
    virtual int getSpeedLevel(void);
    virtual bool setFrom(int fromHID);
    virtual uint32 getHID();

//    uint32 getDownStream(void) {
//        return DownStream;
//    };
//
//    void setDownStream(uint32 id) {
//        DownStream = id;
//    };
private:
//    uint32 DownStream;
//    std::string name;
    DriverPCM* driver;
private:
    static std::map<uint32, CTSChannel*> group;
public:
    /* group option */
    static CTSChannel* getInstance(uint32 uid) {
        std::map<uint32, CTSChannel*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CTSChannel* getFirstInstance(void) {
        std::map<uint32, CTSChannel*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CTSChannel* getNextInstance(uint32 suid) {
        std::map<uint32, CTSChannel*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };


};

#endif /* CTSCHANNEL_H_ */
