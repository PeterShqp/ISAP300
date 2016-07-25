/*
 * PortVF.h
 *
 *  Created on: 2014-2-21
 *      Author: Administrator
 */

#ifndef PORTVF_H_
#define PORTVF_H_

#include "RealPortBase.h"
#include <string>

#define DEF_VFType_MT   1
#define DEF_VFType_4W   2
#define DEF_VFType_FXS  3
#define DEF_VFType_FXO  4
#define DEF_VFType_2W   5


typedef struct {
    uint8 enable; //Enable(1) Disable(0)
    uint8 mode;   //Auto(0) Hotline(1)
    uint8 Polarturn; //Enable(1) Disable(0)
    char desc[32];
    uint8 dlen;
}VFPort_Config_T;

typedef struct {
    uint8 rcvgain;
    uint8 sndGain;
}VFGroup_Config_T;


class PairTSChannel;
class CardVF;
class PortVF : public RealPortBase {
public:
    PortVF(uint32 uid, PairTSChannel* t, VFPort_Config_T* config, VFGroup_Config_T* gconfig, CardVF* card);
    virtual ~PortVF();

    virtual int setLoop(const int type);
    virtual bool ifEnabled(void) {
        return getEnable() != 0;
    };
//    virtual std::string& getName(void);
    int getPortSn();
    int getPortType(void);
    int getEnable(void);
    bool setEnable(int en, bool save = true);
    int getWorkMode(void);
    bool setWorkMode(int md, bool save = true);
    int getPolarTurn(void);
    bool setPolarTurn(int polar, bool save = true);
    uint8 getRcvGain();
    uint8 getSndGain();
    bool setRcvGain(uint8 g, bool save = true);
    bool setSndGain(uint8 g, bool save = true);

    char* getDescription(uint32* len);
    bool setDescription(char* s, uint32 len, bool save = true);

private:
//    std::string name;
    PairTSChannel* ts;
    VFPort_Config_T* ConfigData;
    VFGroup_Config_T* ConfigDataG;
    CardVF* BelongCard;
    int PortType;
    int readPortType(void);
private:
    static std::map<uint32, PortVF*> group;
public:
    /* group option */
    static PortVF* getInstance(uint32 uid) {
        std::map<uint32, PortVF*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortVF* getFirstInstance(void) {
        std::map<uint32, PortVF*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortVF* getNextInstance(uint32 suid) {
        std::map<uint32, PortVF*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PORTVF_H_ */
