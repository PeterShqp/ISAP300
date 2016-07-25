/*
 * SrcGroupSTMPort.cpp
 *
 *  Created on: 2014��9��17��
 *      Author: Administrator
 *      群路光 告警源
 */

#include "SrcGroupSTMPort.h"
#include "AlarmInstance.h"
#include "PortSTM4.h"

SrcGroupSTMPort::SrcGroupSTMPort(BAlarmModule* m, PortSTM4* p, SrcSTMAlarm_Data* d, ChipXCCPLD& cpld) : SrcSTMPort(m,p,d),
        ledLOS(p->itsHid(), cpld), ledAlm(p->itsHid(), cpld) {
    // TODO Auto-generated constructor stub

}

SrcGroupSTMPort::~SrcGroupSTMPort() {
    // TODO Auto-generated destructor stub
}

/*
 * �澯�źŵĴ���
 * ͬʱ����Ϊ�澯�źŷ����ʺϵĸ澯���
 *
 */
void SrcGroupSTMPort::makeAlarmSignal(void) {

    /* ���Ҹ澯��ʾ */
    addAlmIns( new AlarmInstance(STM_Sig_BASE+R_LOS, this, &(pConfigData->Property[R_LOS]), &ledLOS) );
    /* �������������STM�澯�ź� */
    addAlmIns( new AlarmInstance(STM_Sig_BASE+R_OOF, this, &pConfigData->Property[R_OOF], &ledAlm) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+R_LOF, this, &pConfigData->Property[R_LOF], &ledAlm) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+MS_AIS, this, &pConfigData->Property[MS_AIS], &ledAlm) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+MS_RDI, this, &pConfigData->Property[MS_RDI], &ledAlm) );
    addAlmIns( new AlarmInstance(STM_Sig_BASE+MS_REI, this, &pConfigData->Property[MS_REI], &ledAlm) );
}
