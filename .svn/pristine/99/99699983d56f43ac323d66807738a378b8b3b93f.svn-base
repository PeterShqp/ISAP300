/*
 * BAlarmSource.h
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#ifndef BALARMSOURCE_H_
#define BALARMSOURCE_H_

#include <map>
#include <string>
#include "AlarmDataDefine.h"

class AlarmInstance;
class BAlarmModule;

typedef std::map<int, AlarmInstance*> INSMap;


class BAlarmSource {
    BAlarmSource();
public:
    BAlarmSource(BAlarmModule*);
    virtual ~BAlarmSource();

    virtual void makeAlarmSignal(void) = 0; //�����澯�źţ�ͬʱΪ�澯�źŷ���澯���������У���
                                            //��Ҫ�ڸ澯Դ����ʱ���ã���Ϊ�澯Դ����ʱ���澯������ܻ�δ��ȷ���졣

    void processAlarm(void);

    virtual bool ifSrcRestrain() = 0;
    virtual bool getAlarm(int type) = 0;
    virtual bool ifAlarm(void) {
        return false;
    };
    virtual std::string getTypeName(int type) = 0;
    virtual uint32 itsID(void) = 0;
    virtual std::string& itsName(void) = 0;

    void addAlmIns(AlarmInstance* ai);
    void delalmIns(AlarmInstance* ai);

    BAlarmModule* itsModule(void) {
        return ItsModule;
    };

    bool saveConfigData(void);

    bool ifHaveMAJ(void);
    bool ifHaveMIN(void);
//    bool ifAlarm(void);

    AlarmInstance* getAlarmInstanceByTypeID(int type);
    AlarmInstance* getFirstAlarmInstance(void);
    AlarmInstance* getNextAlarmInstance(int type);
    AlarmInstance* getNextAlarmInstance(AlarmInstance* ai);
protected:
    BAlarmModule* ItsModule;
private:
    INSMap InsGroup;
};

#endif /* BALARMSOURCE_H_ */
