/*
 * VCG.h
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#ifndef VCG_H_
#define VCG_H_

#include "BaseResource.h"
#include <map>
#include "EosCardConfigDefine.h"

class CHVC;
class ChipRC6400;
class VCG : public BaseResource {
    VCG();
public:
    VCG(uint32 uid, ConfigCell* card, VCG_ConfigData_T*, ChipRC6400& );
    virtual ~VCG();

//    virtual std::string& getName(void) {
//        return name;
//    };

    int getEnable();
    bool setEnable(int en, bool save = true);
    int getLcas();
    bool setLcas(int en, bool save = true);
    int memberNumber();
    bool addMember(uint32 mid, bool save = true);
    bool removeMember(uint32 mid, bool save = true);
    bool clrMember();
    char* GetDesc(uint32* len);
    bool SetDesc(char* desc, uint32 len);
    uint8 getFlowCtrl();
    bool setFlowCtrl(uint8 fl, bool save = true);

    CHVC* getMemberInstance(uint32 uid);
    CHVC* getFirstMember();
    CHVC* getNextMember(uint32 uid);

    bool ifGFPSynLos(void);
private:
//    std::string name;
    std::map<uint32, CHVC*> memberGroup;
    VCG_ConfigData_T* ConfigData;
    ChipRC6400& driver;
    int hid;
    void makeConfigData(void);

private:
    static std::map<uint32, VCG*> group;
public:
    /* group option */
    static VCG* getInstance(uint32 uid) {
        std::map<uint32, VCG*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static VCG* getFirstInstance(void) {
        std::map<uint32, VCG*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static VCG* getNextInstance(uint32 suid) {
        std::map<uint32, VCG*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* VCG_H_ */
