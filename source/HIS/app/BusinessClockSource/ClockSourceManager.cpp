/*
 * ClockSourceManager.cpp
 *
 *  Created on: 2014-1-13
 *      Author: Administrator
 */

#include "ClockSourceManager.h"
#include "ClockSource.h"
#include <stdio.h>
#include "XcLocalClockSource.h"
#include "ClockSourceDefine.h"
#include "SysError.h"
#include "UID.h"

static TASK void ClockSourceProcess(void*);

ClockSourceManager::ClockSourceManager(std::string& name) : ConfigCell(name, 0) {
    start();
}

ClockSourceManager::~ClockSourceManager() {
    stop();
}

void ClockSourceManager::start() {
    if( !fetchConfig() ) {
        throw SysError("!!!ClockSourceManager config data error!!!");
    }
    WorkingClockSource = -1;
    task_clockprocess = os_tsk_create_ex(ClockSourceProcess, P_ClkSrc_process, this);

}

void ClockSourceManager::stop(void) {
    os_tsk_delete(task_clockprocess);
}


void ClockSourceManager::addClockSource(ClockSource* clk) {
    if( clk ) {
        useableClock.insert(std::pair<int, ClockSource*>(clk->getUID(), clk));
    }
}

void ClockSourceManager::removeClockSource(ClockSource* clk) {
    if( clk ) {
        std::map<int, ClockSource*>::iterator it;
        it = useableClock.find(clk->getUID());
        if( it != useableClock.end() ) {
            useableClock.erase(it);
        }
    }
}


/* backup clock source config */

/*
 * Ϊĳʱ�ӵȼ�����ʱ��Դ
 * NOTE��������ʱ��Դ��һ���ǵ�ǰ���ڵģ�����Ԥ���ã��ú���������ʱ��Դ���Ϸ��Լ��
 */
bool ClockSourceManager::setBackupClockSource(int p, int index, bool saveCfg) {
    if( p < ConfigData.BackupSourceNumber ) {
        if( index != ConfigData.BackupSource[p] ) {
            ConfigData.BackupSource[p] = index;
            if( saveCfg ) {
                return saveConfig();
            }
        }
        return true;
    }
    return false;
}
int ClockSourceManager::getBackupClockSource(int p) {
    if( p < ConfigData.BackupSourceNumber ) {
        return ConfigData.BackupSource[p];
    }
    return -1;
}

/* device clock source option */

/*
 * NOTE: num must > 0
 */
bool ClockSourceManager::setBackupClockSourceNumber(int num, bool saveCfg) {
    if( num <= 0 ) {
        return false;
    }
    if( num != ConfigData.BackupSourceNumber ) {
        ConfigData.BackupSourceNumber = num;
        if( saveCfg ) {
            return saveConfig();
        }
    }
    return true;
}
int ClockSourceManager::getBackupClockSourceNumber(void) {
    return ConfigData.BackupSourceNumber;
}

/*
 * ������ֵΪ0ʱ����ʾ��ϵͳ�Զ�ѡ���ñ�����õ�ʱ��Դ��
 * ������ֵ��0����ʾ�豸ʱ��ԴΪ�˹�ǿ��ָ����ϵͳ���Ը�ʱ��Դ���Ϸ���飬Ҳ���ᷢ��ʱ�ӵ�����
 */
bool ClockSourceManager::setExpectClockSource(int index, bool saveCfg) {
    if( ConfigData.ExpectClockSource != index ) {
        ConfigData.ExpectClockSource = index;
        if( saveCfg ) {
            return saveConfig();
        }
    }
    return true;
}
int ClockSourceManager::getExpectClockSource(void) {
    return ConfigData.ExpectClockSource;
}
int ClockSourceManager::getWorkingClockSource(void) {
    return WorkingClockSource;
}


void ClockSourceManager::FreeRunDefault(void) {
    ST_Clock_source clkinfo;
    clkinfo.slot = 0;
    clkinfo.type = UID::type_local_clock;
    clkinfo.sn = 0;
    uint32 index = UID::makeUID(&clkinfo);
    ClockSource* c = getClockSource(index);
    if( c ) {
        c->active();
        WorkingClockSource = index;
    }
    else {
        clkinfo.type = UID::type_pcm_main_clock;
        index = UID::makeUID(&clkinfo);
        c = getClockSource(index);
        if( c ) {
            c->active();
            WorkingClockSource = index;
        }
    }
}


TASK void ClockSourceProcess(void* obj) {
    ClockSourceManager* cm = (ClockSourceManager*)obj;
//    bool send = true;
    while(1) {
        os_dly_wait(50);
        int expectc = cm->getExpectClockSource();
        if( expectc != 0 ) {
            //人工指定
            if( expectc != cm->WorkingClockSource ) {
                ClockSource* c = cm->getClockSource(cm->WorkingClockSource);
                if( c != 0 ) {
                    c->deActive();
                }
                c = cm->getClockSource(expectc);
                if( c != 0 ) {
                    if( c->active() ) {
                        cm->WorkingClockSource = expectc;
                    }
                }
                else {
                    cm->FreeRunDefault();
                }
            }
        }
        else {
            //自动选择
            bool autoOK = false;
            for( int i = 0; i < cm->ConfigData.BackupSourceNumber; i++ ) {
                ClockSource* c = cm->getClockSource(cm->ConfigData.BackupSource[i]);
                if( c ) {
                    if( (c->getStatus() == clock_ok) && (c->getUID() != cm->WorkingClockSource) ) {
                        ClockSource* workingc = cm->getClockSource(cm->WorkingClockSource);
                        if( workingc != 0 ) {
                            workingc->deActive();
                        }
                        if( c->active() ) {
                            cm->WorkingClockSource = c->getUID();
                            autoOK = true;
                            break;
                        }
                    }
                }
            }
            if( !autoOK ) {
                cm->FreeRunDefault();
            }
        }
    }
}


