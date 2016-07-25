/*
 * UpE1LEDALM.h
 *
 *  Created on: 2015年6月9日
 *      Author: Administrator
 */

#ifndef UPE1LEDALM_H_
#define UPE1LEDALM_H_

#include "DisplayMultiSignalOR.h"
#include "EZ_types.h"

class DriverPCM;

class UpE1LEDALM: public DisplayMultiSignalOR {
public:
    UpE1LEDALM(uint8 sn, DriverPCM& chip);
    virtual ~UpE1LEDALM();

    virtual void display(bool alarm);

private:
    DriverPCM& driver;
    uint8 hid;
};

#endif /* UPE1LEDALM_H_ */
