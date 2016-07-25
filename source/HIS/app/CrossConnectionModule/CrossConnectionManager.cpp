/*
 * CrossConnectionManager.cpp
 *
 *  Created on: 2013-11-28
 *      Author: Administrator
 */

#include "CrossConnectionManager.h"
#include "CCrossConnection.h"
#include <stdio.h>
#include <string.h>
#include "CBaseSlot.h"
#include "CPPTools.h"
#include "UID.h"
#include "ConnectableResource.h"
#include "SyncFileAPI.h"
#include "CCheckData.h"

std::map<uint32, CrossConnectionManager*> CrossConnectionManager::group;

TASK void saveFile(void* cc);

CrossConnectionManager::CrossConnectionManager(uint8 sn) {
    // TODO Auto-generated constructor stub
    itsSlot = sn;
    group.insert(std::pair<uint32, CrossConnectionManager*>(itsSlot, this));
    fname = "slot-"+CPPTools::number2string(itsSlot+1)+ "CrossConnection.cfg";
    task_save = os_tsk_create_ex(saveFile, P_SAVE+1, this);
    os_sem_init(sem_save, 0);
    MAXSN = 0;
    if( sn > 1 )
        restoreCorssConnect();
}

//CrossConnectionManager::CrossConnectionManager(uint8 sn, PairCrossConnectManager* pair) {
//    itsSlot = sn;
//    group.insert(std::pair<uint32, CrossConnectionManager*>(itsSlot, this));
//    fname = "CrossConnection.cfg";
//    task_save = pair->saveFile;
//    restoreCorssConnect();
//}

CrossConnectionManager::~CrossConnectionManager() {
    // TODO Auto-generated destructor stub
    os_tsk_delete(task_save);
    group.erase(itsSlot);
}

void CrossConnectionManager::restoreCorssConnect(void) {
    fetchConfig();
}



int CrossConnectionManager::CreatConnection(uint32 uiSour, uint32 uiDest, bool save) {

    ++MAXSN;
    if( MAXSN <= 0 ) {
        MAXSN = 1;
    }
    try {
#ifdef CC_DBG
        printf("\n--CreatConnection(src:%4x, dst:%4x) sn:%d start\n", uiSour, uiDest, MAXSN);
#endif
        CCrossConnection* pcc = new CCrossConnection(MAXSN, uiSour, uiDest);
#ifdef CC_DBG
        printf("\n--new CCrossConnection %d over!\n", MAXSN);
#endif
        if( pcc == 0 ) {
            return 0;
        }
        cc.insert( std::pair<int, CCrossConnection*>( MAXSN, pcc ) );
        if( save ) {
            saveConfig();
        }

    }
    catch(...) {
        return 0;
    }
    return MAXSN;
}

int CrossConnectionManager::CreatBiConnection(uint32 uiSour, uint32 uiDest) {
    int firstcc = CreatConnection(uiSour, uiDest);
    int secondcc = CreatConnection(uiDest, uiSour);
    if( (firstcc != 0) && (secondcc != 0) ) {
//        cc[firstcc]->setCouple(cc[secondcc]);
//        cc[secondcc]->setCouple(cc[firstcc]);
        return firstcc;
    }
    return 0;
}

uint32 CrossConnectionManager::CreatConnection(uint32 sn, uint32 uiSour, uint32 uiDest ) {
    try {
        it = cc.find(sn);
        if( it != cc.end() ) {
            //�Ѿ��ָ���ֻдӲ��
            ConnectableResource* r = ConnectableResource::getResrcInstance(uiDest);
            if( r ) {
                r->connectFrom(uiSour);
            }
            else {
                return 0;
            }

        }
        else {
            CCrossConnection* pcc = new CCrossConnection(sn, uiSour, uiDest);
            if( pcc == 0 ) {
                return 0;
            }
            cc.insert( std::pair<int, CCrossConnection*>( sn, pcc ) );
        }

    }
    catch(...) {
        return 0;
    }
    return sn;
}



bool CrossConnectionManager::deleteConnection(int csn) {
    std::map<int, CCrossConnection*>::iterator it = cc.find(csn);
    if( it != cc.end() ) {
        delete it->second;
        cc.erase(it);
        saveConfig();
        return true;
    }
    return false;
}

uint32 CrossConnectionManager::clearAll(void) {
    if( cc.empty() ) {
        return 0x5A;
    }
    it = cc.begin();
    while( it != cc.end() ) {
        delete it->second;
        it++;
    }
    cc.clear();
    saveConfig();
    return 0x5A;
}


int CrossConnectionManager::GetFirstSnOfConnection(void) {
    if( cc.empty() ) {
        return 0;
    }
    it = cc.begin();
    return it->first;
}
int CrossConnectionManager::GetNextSnConnection(int iStartSn) {
    it = cc.find(iStartSn);
    if( it != cc.end() ) {
        if( ++it != cc.end() ) {
            return it->first;
        }
    }
    return 0;
}

bool CrossConnectionManager::SetXcName(uint32 uiXcUID, std::string& name, bool save) {
    CCrossConnection* cc = getCC(uiXcUID);
    cc->SetName(name);
    if( save ) {
        return saveConfig();
    }
    return true;

}
bool CrossConnectionManager::SetXcDescription(uint32 uiXcUID, std::string& desc, bool save) {
    CCrossConnection* cc = getCC(uiXcUID);
    cc->SetDescription(desc);
    if( save ) {
        return saveConfig();
    }
    return true;
}
//uint32 CrossConnectionManager::setXcSncp(uint32 uiXcUID, uint32 en);


bool CrossConnectionManager::saveConfig(void) {
//    os_evt_set(0x0001, task_save);
    os_sem_send(sem_save);
    return true;
}

void CrossConnectionManager::saveToFile(void) {
    FILE* f = fopen(fname.c_str(), "wb");
#ifdef EZ_DBG
    printf("\n $$$CrossConnectionManager::saveToFile() start\n");
#endif
    if( f ) {
        CROSS_CONFIG_DATA_T temp;
        it = cc.begin();
        uint32 crc = 0;
        while( it != cc.end() ) {
            temp.sn = it->second->GetSn();
            temp.dest = it->second->GetdestUID();
            temp.source = it->second->GetSrcUID();
            std::string& name = it->second->GetName();
            strcpy( temp.name, name.c_str() );
            std::string& desc = it->second->GetDescription();
            strcpy( temp.desc, desc.c_str() );
            fwrite(&temp, sizeof(temp), 1, f);
            CCheckData::CRCCheck2((uint8*)&temp, sizeof(temp), crc, &crc);
            it++;
        }
        fwrite(&crc, sizeof(crc), 1, f);
        fclose(f);
#ifdef EZ_DBG
    printf("\n $$$CrossConnectionManager::saveToFile() end\n");
#endif
        SyncFileAPI::instance().sendAfileToRemote(fname.c_str());
    }

}

bool CrossConnectionManager::fetchConfig(void) {
    FILE* f = fopen(fname.c_str(), "rb");
    if( f ) {
        CROSS_CONFIG_DATA_T temp;
        while( !feof(f) ) {
            if( fread(&temp, sizeof(temp), 1, f) == 0 ) {
                break;
            }
            int sn = CreatConnection(temp.sn, temp.source, temp.dest);
            std::string name(temp.name);
            SetXcName(sn, name, false);
            std::string desc(temp.desc);
            SetXcDescription(sn, desc, false);
            MAXSN = temp.sn;
        }
        fclose(f);
    }
	return true;
}

//void CrossConnectionManager::clearAll(void) {
//    it = cc.begin();
//    while( it != cc.end() ) {
//        deleteConnection(it->second->GetSn());
//    }
//}

TASK void saveFile(void* cc) {
    CrossConnectionManager* card = (CrossConnectionManager*)cc;
    OS_RESULT result;
    bool needSave = false;
    while( 1 ) {
        result = os_sem_wait(card->sem_save, 300);
        if( (result == OS_R_TMO) && needSave ) {
            printf("\nstart--");
            card->saveToFile();
            printf("--end\n");
            needSave = false;
        }
        else if( result == OS_R_SEM || result == OS_R_OK) {
            needSave = true;
        }
    }
}
