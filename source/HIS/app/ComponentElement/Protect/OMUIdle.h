/*
 * OMUIdle.h
 *
 *  Created on: 2014��12��9��
 *      Author: Administrator
 */

#ifndef OMUIDLE_H_
#define OMUIDLE_H_

#include "OMUStatus.h"

class SyncFileBakAPI;
class OMUIdle: public OMUStatus {
public:
    OMUIdle();
    virtual ~OMUIdle();

    virtual Working_STATE_E getStatus(void);
private:
    SyncFileBakAPI* sync;
};

#endif /* OMUIDLE_H_ */
