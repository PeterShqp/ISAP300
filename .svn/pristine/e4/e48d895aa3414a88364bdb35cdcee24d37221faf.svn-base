/*
 * SrcAlarmE1.h
 *
 *  Created on: 2014Äê9ÔÂ9ÈÕ
 *      Author: Administrator
 */

#ifndef SRCALARME1_H_
#define SRCALARME1_H_

#include "BAlarmSource.h"
#include "E1CardAlarmDataDefine.h"

class PortE1;
class BAlarmDisplay;

class SrcAlarmE1: public BAlarmSource {
public:
    SrcAlarmE1(BAlarmModule*, PortE1*, SrcE1Alarm_Data*, BAlarmDisplay&);
    virtual ~SrcAlarmE1();

    virtual void makeAlarmSignal(void);
    virtual bool ifSrcRestrain();
    virtual bool getAlarm(int type);
    virtual std::string getTypeName(int type);
    virtual uint32 itsID(void);
    virtual std::string& itsName(void);
private:
    SrcE1Alarm_Data* pConfigData;
    PortE1* port;
    BAlarmDisplay& ledWork;
};

#endif /* SRCALARME1_H_ */
