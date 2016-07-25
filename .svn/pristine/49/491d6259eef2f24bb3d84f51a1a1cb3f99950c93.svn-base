/*
 * OMUStatus.h
 *
 *  Created on: 2014Äê11ÔÂ27ÈÕ
 *      Author: Administrator
 */

#ifndef OMUSTATUS_H_
#define OMUSTATUS_H_

#include "os.h"

typedef enum {
    OMU_Working,
    OMU_Standby,
    OMU_Idle

}Working_STATE_E;

class OMUStatus {
public:
    OMUStatus(uint8 delay);
    virtual ~OMUStatus();

    virtual Working_STATE_E getStatus(void) = 0;
    bool ifLock(void) {
        return Locked;
    };
    void lockIt(bool l) {
        Locked = l;
    };
private:
    uint8 dly_times;
    OS_TID led_run;
    bool Locked;
};

#endif /* OMUSTATUS_H_ */
