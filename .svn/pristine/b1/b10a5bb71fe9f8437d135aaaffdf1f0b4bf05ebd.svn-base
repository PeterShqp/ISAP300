/*
 * SrcAlarmVC4.h
 *
 *  Created on: 2014年9月5日
 *      Author: Administrator
 */

#ifndef SRCALARMVC4_H_
#define SRCALARMVC4_H_

#include "BAlarmSource.h"
#include "XCAlarmDataDefine.h"

class BAlarmModule;
class RscVC4;

class SrcAlarmVC4: public BAlarmSource {
    SrcAlarmVC4();
public:
    SrcAlarmVC4(BAlarmModule*, RscVC4*, SrcVC4Alarm_Data*);
    virtual ~SrcAlarmVC4();

    virtual void makeAlarmSignal(void); //创建告警信号，同时为告警信号分配告警输出（如果有），
                                            //不要在告警源构造时调用，因为告警源构造时，告警输出可能还未正确构造。

    virtual bool ifSrcRestrain();
    virtual bool getAlarm(int type);
    virtual std::string getTypeName(int type);
    virtual uint32 itsID(void);
    virtual std::string& itsName(void);

private:
    SrcVC4Alarm_Data* pConfigData;
    RscVC4* port;

};

#endif /* SRCALARMVC4_H_ */
