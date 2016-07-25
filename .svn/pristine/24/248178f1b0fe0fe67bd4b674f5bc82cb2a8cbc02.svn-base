/*
 * CSTBus.h
 *
 *  Created on: 2013-12-16
 *      Author: Administrator
 */

#ifndef CSTBUS_H_
#define CSTBUS_H_

#include "EZ_Types.h"

#include "BaseResource.h"
#include <map>

class DriverPCM;
class CTSChannel;
class CBaseCard;

class CSTBus : public BaseResource {
public:
    CSTBus(uint32 uid, ConfigCell* card, DriverPCM* driver, bool paired = false);
    virtual ~CSTBus();

//    virtual std::string& getName(void);

//    bool getLOS();
//    bool getAIS();
//    bool getLOF();
//    bool getLOMF();

private:
    static std::map<uint32, CSTBus*> group;
    CTSChannel* ts_obj[32];
//    DriverPCM* chip;
//    std::string name;
    /* group option */
    static CSTBus* getInstance(uint32 uid) {
        std::map<uint32, CSTBus*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CSTBus* getFirstInstance(void) {
        std::map<uint32, CSTBus*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CSTBus* getNextInstance(uint32 suid) {
        std::map<uint32, CSTBus*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* CSTBUS_H_ */
