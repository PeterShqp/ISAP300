/*
 * SrcTribSTMPort.h
 *
 *  Created on: 2014��9��17��
 *      Author: Administrator
 */

#ifndef SRCTRIBSTMPORT_H_
#define SRCTRIBSTMPORT_H_

#include "SrcSTMPort.h"
#include "TribSTMLEDLOS.h"
#include "TribSTMLEDALM.h"

class Chip8STM1Logic2;
class Chip8STM1CPLD;

class SrcTribSTMPort: public SrcSTMPort {
public:
    SrcTribSTMPort(BAlarmModule*, PortSTM4*, SrcSTMAlarm_Data*, Chip8STM1Logic2&, Chip8STM1CPLD&);
    virtual ~SrcTribSTMPort();

    virtual void makeAlarmSignal(void);
private:
    TribSTMLEDLOS LEDLOS;
    TribSTMLEDALM LEDALM;
};

#endif /* SRCTRIBSTMPORT_H_ */
