/*
 * OMUStandby.h
 *
 *  Created on: 2014��11��27��
 *      Author: Administrator
 */

#ifndef OMUSTANDBY_H_
#define OMUSTANDBY_H_

#include "OMUStatus.h"

class SyncFileBakAPI;
class OMUStandby: public OMUStatus {
public:
    OMUStandby();
    virtual ~OMUStandby();

    virtual Working_STATE_E getStatus(void) {
        return OMU_Standby;
    };
private:
    SyncFileBakAPI* sync;
};

#endif /* OMUSTANDBY_H_ */
