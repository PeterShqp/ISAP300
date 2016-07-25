/*
 * ConfigCell.h
 *
 *  Created on: 2014��11��19��
 *      Author: Administrator
 */

#ifndef CONFIGCELL_H_
#define CONFIGCELL_H_

#include "os.h"
#include <string>
#include "EZ_types.h"

class ConfigCell {
public:
    ConfigCell(const std::string& name, int slotSn);
    ConfigCell();
    virtual ~ConfigCell();

    /* ���濨����Ϊ�ļ� */
    bool saveConfig();
    /* �ָ��������ļ� */
    bool fetchConfig();
    /* Ĭ���������  ���������д�˷���ʵ���Լ���Ĭ�����  �����н��������ȫ����0*/
    virtual void loadDefaultData(void);

    void saveToFile();

    virtual uint8* getConfigDataBuff(void) = 0;
    virtual uint32 getConfigDataLen(void) = 0;

    std::string& getItsConfigFileName(void) {
        return cfgFileName;
    };
private:
    friend TASK void Do_Save(void* cell);
    std::string cfgFileName;
    OS_TID task_save;
};

#endif /* CONFIGCELL_H_ */
