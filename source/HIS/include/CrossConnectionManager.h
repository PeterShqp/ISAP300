/*
 * CrossConnectionManager.h
 *
 *  Created on: 2013-11-28
 *      Author: Administrator
 */

#ifndef CROSSCONNECTIONMANAGER_H_
#define CROSSCONNECTIONMANAGER_H_

#include <map>
#include <string>
#include "EZ_types.h"
#include "os.h"

typedef struct {
    uint32 sn;
    uint32 source;
    uint32 dest;
    char name[32];
    char desc[32];
}CROSS_CONFIG_DATA_T;

class CCrossConnection;
//class CBaseSlot;

class PairCrossConnectManager;
class CrossConnectionManager {
public:
    CrossConnectionManager(uint8 sn);
//    CrossConnectionManager(uint8 sn, PairCrossConnectManager*);
    virtual ~CrossConnectionManager();

    void restoreCorssConnect(void);
    int CreatConnection(uint32 uiSour, uint32 uiDest, bool save = true);
    int CreatBiConnection(uint32 uiSour, uint32 uiDest);
    uint32 CreatConnection(uint32 sn, uint32 uiSour, uint32 uiDest);
    bool deleteConnection(int csn);
    bool SetXcName(uint32 uiXcUID, std::string& name, bool save = true);
    bool SetXcDescription(uint32 uiXcUID, std::string& desc, bool save = true);
//    bool setXcSncp(uint32 uiXcUID, uint32 en);
    CCrossConnection* getCC(int sn) {
        std::map<int, CCrossConnection*>::iterator it = cc.find(sn);
        if( it != cc.end() ) {
            return it->second;
        }
        return 0;
    };
    int GetFirstSnOfConnection(void);
    int GetNextSnConnection(int iStartSn);
    int count(void) {
        return cc.size();
    };

    int getSlotSn(void) {
        return itsSlot;
    };

    uint32 clearAll(void);
private:
    friend TASK void saveFile(void* cc);
    friend TASK void saveDoubleFile(void* cc);
    std::map<int, CCrossConnection*> cc;
    std::map<int, CCrossConnection*>::iterator it;
    std::string fname;
    bool saveConfig(void);
    bool fetchConfig(void);
    void saveToFile(void);
//    void clearAll(void);
    uint8 itsSlot;
    OS_TID task_save;
    OS_SEM sem_save;
    int MAXSN;

private:
    static std::map<uint32, CrossConnectionManager*> group;
public:
    /* group option */
    static CrossConnectionManager* getInstance(uint32 uid) {
        std::map<uint32, CrossConnectionManager*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CrossConnectionManager* getFirstInstance(void) {
        std::map<uint32, CrossConnectionManager*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static CrossConnectionManager* getNextInstance(uint32 suid) {
        std::map<uint32, CrossConnectionManager*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };};

#endif /* CROSSCONNECTIONMANAGER_H_ */
