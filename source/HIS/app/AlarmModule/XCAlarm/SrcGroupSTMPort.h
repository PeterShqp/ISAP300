/*
 * SrcGroupSTMPort.h
 *
 *  Created on: 2014Äê9ÔÂ17ÈÕ
 *      Author: Administrator
 */

#ifndef SRCGROUPSTMPORT_H_
#define SRCGROUPSTMPORT_H_

#include "SrcSTMPort.h"
#include "XCLEDLOS.h"
#include "XCLEDALM.h"

class ChipXCCPLD;

class SrcGroupSTMPort: public SrcSTMPort {
public:
    SrcGroupSTMPort(BAlarmModule*, PortSTM4*, SrcSTMAlarm_Data*, ChipXCCPLD& d);
    virtual ~SrcGroupSTMPort();

    virtual void makeAlarmSignal(void);
private:
    XCLEDLOS ledLOS;
    XCLEDALM ledAlm;

};

#endif /* SRCGROUPSTMPORT_H_ */
