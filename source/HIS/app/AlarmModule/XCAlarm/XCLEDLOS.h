/*
 * XCLEDLOS.h
 *
 *  Created on: 2014Äê8ÔÂ15ÈÕ
 *      Author: Administrator
 */

#ifndef XCLEDLOS_H_
#define XCLEDLOS_H_

#include "DisplayMultiSignalOR.h"

class ChipXCCPLD;
class XCLEDLOS: public DisplayMultiSignalOR {
public:
    XCLEDLOS(int sn, ChipXCCPLD& d);
    virtual ~XCLEDLOS();

    virtual void display(bool alarm);


private:
    int itsSn;
    ChipXCCPLD& Driver;
};

#endif /* XCLEDLOS_H_ */
