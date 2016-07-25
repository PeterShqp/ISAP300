/*
 * ProtectAssistCell.h
 *
 *  Created on: 2014��11��27��
 *      Author: Administrator
 */

#ifndef PROTECTASSISTCELL_H_
#define PROTECTASSISTCELL_H_

#include "os.h"
#include "OMUStatus.h"
#include "OMUWorking.h"

class ProtectAssistCell {
    ProtectAssistCell();
    ProtectAssistCell(ProtectAssistCell&);
    ProtectAssistCell& operator= (ProtectAssistCell&);
    virtual ~ProtectAssistCell();
    static ProtectAssistCell pcell;
public:
    static ProtectAssistCell& instance(void) {
        return pcell;
    };

    void start();

    Working_STATE_E getOMUWorkingStateByHardware();
    Working_STATE_E getOMUCurrentWorkingState();

    void switchTo(Working_STATE_E);

    void autoPause(void) {
        protectPause = true;
    };

    void autoStart(void) {
        protectPause = false;
    };

    OS_TID getTaskProcessWorking(void) {
        OMUWorking* o = dynamic_cast<OMUWorking*>(omu);
        if( o ) {
            return o->task_work;
        }
        return 0;
    };
private:
    friend void check_working(void* pc);
    OS_TID working_state_check;
    OMUStatus* omu;
    bool protectPause;
};

#endif /* PROTECTASSISTCELL_H_ */
