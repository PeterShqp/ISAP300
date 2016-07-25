/*
 * ConfigCell.cpp
 *
 *  Created on: 2014��11��19��
 *      Author: Administrator
 */

#include "ConfigCell.h"
#include <stdio.h>
#include <string.h>
#include "CCheckData.h"
#include "CPPTools.h"
#include "SyncFileAPI.h"

TASK void Do_Save(void* cell);
#define DEF_Device_Attribute -1

ConfigCell::ConfigCell(const std::string& name, int slotSn) {
    if( slotSn == DEF_Device_Attribute ) {
        cfgFileName = name;
    }
    else {
        cfgFileName = "Card"+name + "Slot-" + CPPTools::number2string(slotSn+1) + ".cfg";
    }
    task_save = os_tsk_create_ex(Do_Save, P_SAVE, this);

}

ConfigCell::ConfigCell() : cfgFileName("PairXC.cfg") {
    task_save = os_tsk_create_ex(Do_Save, P_SAVE, this);
}

ConfigCell::~ConfigCell() {
    os_tsk_delete(task_save);
}

/* ���濨����Ϊ�ļ� */
bool ConfigCell::saveConfig() {
    os_evt_set(0x0001, task_save);
    return true;
}
/* �ָ��������ļ� */
bool ConfigCell::fetchConfig() {
    FILE* f = fopen(cfgFileName.c_str(), "rb");
    if( f ) {
        fread(getConfigDataBuff(), getConfigDataLen(), 1, f);
        uint32 crcCurrent = 0;
        uint32 crcRead = 0;
        CCheckData::CRCCheck1(getConfigDataBuff(), getConfigDataLen(), &crcCurrent);
        fread(&crcRead, sizeof(crcRead), 1, f);
        fclose(f);
        if( crcCurrent == crcRead ) {
            return true;
        }
    }
    loadDefaultData();
    return saveConfig();
}

void ConfigCell::loadDefaultData(void) {
    memset(getConfigDataBuff(), 0, getConfigDataLen());
}

void ConfigCell::saveToFile() {
    FILE* f = fopen(cfgFileName.c_str(), "wb");
    if( f ) {
        fwrite(getConfigDataBuff(), getConfigDataLen(), 1, f);
        uint32 crc = 0;
        CCheckData::CRCCheck1(getConfigDataBuff(), getConfigDataLen(), &crc);
        fwrite(&crc, sizeof(crc), 1, f);
        fclose(f);
        if( cfgFileName != "DeviceAttributeNew.txt") {
            SyncFileAPI::instance().sendAfileToRemote(cfgFileName.c_str());
        }
        else {
//            printf("\nno sync DeviceAttribute.txt\n");
        }
    }
}


TASK void Do_Save(void* cell) {
    ConfigCell* card = (ConfigCell*)cell;
    OS_RESULT result;
    bool needSave = false;
    while( 1 ) {
        result = os_evt_wait_or(0x0001, 300);
        if( (result == OS_R_TMO) && needSave ) {
            card->saveToFile();
            needSave = false;
        }
        else if( result == OS_R_EVT ) {
            needSave = true;
        }
    }
}
