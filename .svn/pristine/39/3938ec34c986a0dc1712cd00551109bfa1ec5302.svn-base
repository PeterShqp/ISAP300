/*
 * CHVC.h
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#ifndef CHVC_H_
#define CHVC_H_

#include "BaseResource.h"
#include <map>
#include "EosCardConfigDefine.h"

class PairRscSDHChannel;
class VCG;
class ChipRC6400;

class CHVC : public BaseResource {
    CHVC();
public:
    CHVC(uint32 uid, ConfigCell* card, PairRscSDHChannel* maplink, ChipRC6400& chip1, ChipRC6400& chip2, CHVC_ConfigData_T*);
    virtual ~CHVC();

//    virtual std::string& getName(void);

    uint32 getDownStream(void);
    uint32 getUpStream(void);

    bool bandToVCG(VCG*);

    uint32 getProtectPartner(void);
    uint32 getSNCP(void);
    bool setSNCP(uint32 cc, bool save = true );

    int itsSn(void) {
        return sn;
    };
private:
    PairRscSDHChannel* LinkChannel;
    ChipRC6400& Driver1;
    ChipRC6400& Driver2;
    VCG* BandVCG;
    int sn;
    CHVC_ConfigData_T* ConfigData;
private:
    static std::map<uint32, CHVC*> group;
public:
    /* group option */
    static CHVC* getInstance(uint32 uid) {
        std::map<uint32, CHVC*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CHVC* getFirstInstance(void) {
        std::map<uint32, CHVC*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CHVC* getNextInstance(uint32 suid) {
        std::map<uint32, CHVC*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* CHVC_H_ */
