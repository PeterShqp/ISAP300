/*
 * PairSTBus.h
 *
 *  Created on: 2014��11��26��
 *      Author: Administrator
 */

#ifndef PAIRSTBUS_H_
#define PAIRSTBUS_H_

#include "PairResource.h"

class PairTSChannel;
class PairSTBus: public PairResource {
public:
    PairSTBus(uint32 uid);
    virtual ~PairSTBus();

    PairTSChannel* getPairTSChannel(int sn) {
        if( sn < 32 ) {
            return  ts_obj[sn];
        }
        return 0;
    };
private:
    PairTSChannel* ts_obj[32];
};

#endif /* PAIRSTBUS_H_ */
