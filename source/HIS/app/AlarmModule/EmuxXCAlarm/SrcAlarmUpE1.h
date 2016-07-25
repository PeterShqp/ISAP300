/*
 * SrcAlarmUpE1.h
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */

#ifndef SRCALARMUPE1_H_
#define SRCALARMUPE1_H_

#include "BAlarmSource.h"
#include "DXCAlarmDataDefine.h"
#include "UpE1LEDWork.h"
#include "UpE1LEDALM.h"

class RealPortBase;

class SrcAlarmUpE1: public BAlarmSource {
public:
    SrcAlarmUpE1(uint8 sn, BAlarmModule*m, RealPortBase* port, SrcUpE1Alarm_Data* data, DriverPCM& chip);
    virtual ~SrcAlarmUpE1();

    virtual void makeAlarmSignal(void);
    virtual bool ifSrcRestrain();
    virtual bool getAlarm(int type);
    virtual std::string getTypeName(int type);
    virtual uint32 itsID(void);
    virtual std::string& itsName(void);
private:
    SrcUpE1Alarm_Data* pConfigData;
    UpE1LEDWork ledwork;
    UpE1LEDALM ledalm;
    DriverPCM& driver;
    RealPortBase* e1;
    uint8 SN;

};

#endif /* SRCALARMUPE1_H_ */
