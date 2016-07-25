/*
 * UpE1LEDWork.h
 *
 *  Created on: 2015年6月9日
 *      Author: Administrator
 */

#ifndef UPE1LEDWORK_H_
#define UPE1LEDWORK_H_

#include "DisplayMultiSignalOR.h"
#include "EZ_types.h"

class DriverPCM;

class UpE1LEDWork: public DisplayMultiSignalOR {
public:
    UpE1LEDWork(uint8 sn, DriverPCM& chip);
    virtual ~UpE1LEDWork();

    virtual void display(bool alarm);

private:
    DriverPCM& driver;
    uint8 hid;
};

#endif /* UPE1LEDWORK_H_ */
