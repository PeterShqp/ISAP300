/*
 * SrcTribSTMPort.cpp
 *
 *  Created on: 2014��9��17��
 *      Author: Administrator
 */

#include "SrcTribSTMPort.h"
#include "AlarmInstance.h"
#include "PortSTM4.h"

SrcTribSTMPort::SrcTribSTMPort(BAlarmModule* m, PortSTM4* p, SrcSTMAlarm_Data* d, Chip8STM1Logic2& c, Chip8STM1CPLD& cpld)
                : SrcSTMPort(m,p,d), LEDLOS(p->itsHid(), c), LEDALM(p->itsHid(), cpld) {
    // TODO Auto-generated constructor stub

}

SrcTribSTMPort::~SrcTribSTMPort() {
    // TODO Auto-generated destructor stub
}

void SrcTribSTMPort::makeAlarmSignal(void) {

    /* ���Ҹ澯��ʾ */
    addAlmIns( new AlarmInstance(STM_Sig_BASE+R_LOS, this, &(pConfigData->Property[R_LOS]), &LEDLOS) );
    /* �������������STM�澯�ź� */
    addAlmIns( new AlarmInstance(STM_Sig_BASE+R_LOF, this, &pConfigData->Property[R_LOF], &LEDALM) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+R_OOF, this, &pConfigData->Property[R_OOF], &LEDALM) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+MS_AIS, this, &pConfigData->Property[MS_AIS], &LEDALM) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+MS_RDI, this, &pConfigData->Property[MS_RDI], &LEDALM) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+MS_REI, this, &pConfigData->Property[MS_REI], &LEDALM) );

}
