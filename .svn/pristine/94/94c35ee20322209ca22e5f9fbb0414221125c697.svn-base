/*
 * SrcSTMPort.h
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#ifndef SRCSTMPORT_H_
#define SRCSTMPORT_H_

#include "BAlarmSource.h"
#include "XCAlarmDataDefine.h"
#include <string>

class PortSTM4;
class SrcAlarmVC4;

class SrcSTMPort : public BAlarmSource {
public:
    SrcSTMPort(BAlarmModule*, PortSTM4*, SrcSTMAlarm_Data*);
    virtual ~SrcSTMPort();

    virtual void makeAlarmSignal(void) = 0;

    virtual bool ifSrcRestrain();
    virtual bool getAlarm(int type);
    virtual bool ifAlarm(void);

    virtual std::string getTypeName(int type);
    virtual uint32 itsID(void);
    virtual std::string& itsName(void);
protected:
    SrcSTMAlarm_Data* pConfigData;

private:
    PortSTM4* port;
    SrcAlarmVC4* AlarmSrcObj[4];
};

#endif /* SRCSTMPORT_H_ */
