/*
 * SoftWDT.h
 *
 *  Created on: 2016年4月12日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_MIDWARE_SOFTWDT_H_
#define SOURCE_HIS_APP_MIDWARE_SOFTWDT_H_

#include "os.h"
#include <map>

typedef struct {
    uint32 current_count;
}WDT_Para_T;

class SoftWDT {
    SoftWDT() {};
    SoftWDT(SoftWDT&) {};
    virtual ~SoftWDT() {};
    static SoftWDT wdt;
public:
    static SoftWDT& instance(void) {
        return wdt;
    };
    void init(void);
    void startSoftWDT(void);
    void stopSoftWDT(void);

    void pause(void);
    void resume(void);

    void add(OS_TID, WDT_Para_T*);
    void feed(OS_TID);
private:
    friend TASK void T_SoftWDT(void);
    const static uint32 OUT_TIME_COUNT = 300;
    OS_TID task_soft_wdt;
    std::map<OS_TID, WDT_Para_T*> workingWdt;
};

#endif /* SOURCE_HIS_APP_MIDWARE_SOFTWDT_H_ */
