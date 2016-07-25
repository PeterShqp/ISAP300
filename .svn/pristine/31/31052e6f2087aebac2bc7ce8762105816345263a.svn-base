/*
 * TimeSlot2ITUT.cpp
 *
 *  Created on: 2013-12-16
 *      Author: Administrator
 */

#include "TimeSlot2ITUT.h"

TimeSlot2ITUT::TimeSlot2ITUT() {
    // TODO Auto-generated constructor stub

}

TimeSlot2ITUT::~TimeSlot2ITUT() {
    // TODO Auto-generated destructor stub
}

/*
 * Not thread safe
 */
ITUT_T& TimeSlot2ITUT::itutFrom(uint8 ts) {
    static ITUT_T t;
    t.tug3 = (ts-1)%3 + 1;
    t.tug2 = (ts-1)/3 + 1;
    t.tug1 = (ts-1)/21 +1;
    return t;
}
uint8 TimeSlot2ITUT::timeslotFrom(ITUT_T& it) {
    uint8 tsBase = (it.tug1-1) * 21;
    tsBase += (it.tug2-1) * 3;
    tsBase += it.tug3;
    return tsBase;
}
