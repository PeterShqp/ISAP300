/*
 * RscVC12.h
 *
 *  Created on: 2013-11-30
 *      Author: Administrator
 */

#ifndef RSCVC12_H_
#define RSCVC12_H_

#include "ConnectableResource.h"

class DriverSDH;
class RscVC12 : public ConnectableResource {
public:
    RscVC12(uint32 uid, ConfigCell* card, DriverSDH& chipDriver, bool paired = false);
    virtual ~RscVC12();

//    virtual std::string& getName(void);
    virtual int getSpeedLevel(void);
    virtual bool setFrom(int fromHID);
    virtual uint32 getHID();

    static uint8 itsHardwareID(uint32 uid);
private:
//    std::string name;
    DriverSDH& driver;
private:
    static std::map<uint32, RscVC12*> group;
public:
    /* group option */
    static RscVC12* getInstance(uint32 uid) {
        std::map<uint32, RscVC12*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscVC12* getFirstInstance(void) {
        std::map<uint32, RscVC12*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static RscVC12* getNextInstance(uint32 suid) {
        std::map<uint32, RscVC12*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };

};

#endif /* RSCVC12_H_ */
