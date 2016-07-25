/*
 * XCLEDALM.h
 *
 *  Created on: 2014Äê8ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef XCLEDALM_H_
#define XCLEDALM_H_

#include "DisplayMultiSignalOR.h"

class ChipXCCPLD;
class XCLEDALM: public DisplayMultiSignalOR {
public:
    XCLEDALM(int sn, ChipXCCPLD& d);
    virtual ~XCLEDALM();

    virtual void display(bool alarm);

private:
    int itsSn;
    ChipXCCPLD& Driver;
};

#endif /* XCLEDALM_H_ */
