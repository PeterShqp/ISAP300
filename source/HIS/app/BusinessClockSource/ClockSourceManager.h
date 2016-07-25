/*
 * ClockSourceManager.h
 *
 *  Created on: 2014-1-13
 *      Author: Administrator
 */

#ifndef CLOCKSOURCEMANAGER_H_
#define CLOCKSOURCEMANAGER_H_

#include <map>
#include <vector>
//#include "CMidFileCfg.h"
#include "os.h"
#include "ConfigCell.h"

enum {
    clock_auto,
    clock_manual
};

static const uint8 MAX_Backup_ClockSource = 8;

typedef struct {
    uint32 ExpectClockSource;
    uint8 BackupSourceNumber;
    uint32 BackupSource[MAX_Backup_ClockSource];
}ClockSourceManager_Config_T;

class ClockSource;

class ClockSourceManager : public ConfigCell {
    friend class ClockSource;
    friend TASK void ClockSourceProcess(void*);
public:
    ClockSourceManager(std::string& name);
    virtual ~ClockSourceManager();

    virtual uint8* getConfigDataBuff(void) {
        return (uint8*)&ConfigData;
    };
    virtual uint32 getConfigDataLen(void) {
        return sizeof(ConfigData);
    }

    /* backup clock source config */
    bool setBackupClockSource(int p, int index, bool ifsave = true);
    int getBackupClockSource(int p);

    /* device clock source option */
    bool setBackupClockSourceNumber(int num, bool ifsave = true);
    int getBackupClockSourceNumber(void);
    bool setExpectClockSource(int index, bool ifsave = true);
    int getExpectClockSource(void);
    int getWorkingClockSource(void);
    void FreeRunDefault(void);

    /* useable clock source access */
    ClockSource* getClockSource(int sn) {
        std::map<int, ClockSource*>::iterator it = useableClock.find(sn);
        if( it != useableClock.end() ) {
            return it->second;
        }
        return 0;
    };

    ClockSource* getFirstClockSource() {
        std::map<int, ClockSource*>::iterator it = useableClock.begin();
        if( it != useableClock.end() ) {
            return it->second;
        }
        return 0;
    };

    ClockSource* getNextClockSource(int sn) {
        std::map<int, ClockSource*>::iterator it = useableClock.find(sn);
        if( it != useableClock.end() ) {
            if( ++it != useableClock.end() ) {
                return it->second;
            }
        }
        return 0;
    };

    void addClockSource(ClockSource* clk);
    void removeClockSource(ClockSource* clk);

private:
    void start();
    void stop(void);
    std::map<int, ClockSource*> useableClock;
    ClockSourceManager_Config_T ConfigData;
    int WorkingClockSource; //0 free run ; not 0 current clock source
    OS_TID task_clockprocess;
};

#endif /* CLOCKSOURCEMANAGER_H_ */
