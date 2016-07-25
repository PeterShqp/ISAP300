/*
 * PairRscConnectable.h
 *
 *  Created on: 2014Äê11ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRRSCCONNECTABLE_H_
#define PAIRRSCCONNECTABLE_H_

#include "PairResource.h"
#include "ConnectableResource.h"

class PairRscConnectable : public ConnectableResource {
public:
    PairRscConnectable(uint32 uid);
    virtual ~PairRscConnectable();

    virtual int getSpeedLevel(void);
    virtual bool setFrom(int fromHID); // if fromHID < 0, disconnect
    virtual uint32 getHID();
//    virtual uint32 getConnectFrom(void);

    PairResource& getPairTool(void) {
        return pairTool;
    };
private:
    PairResource pairTool;
};

#endif /* PAIRRSCCONNECTABLE_H_ */
