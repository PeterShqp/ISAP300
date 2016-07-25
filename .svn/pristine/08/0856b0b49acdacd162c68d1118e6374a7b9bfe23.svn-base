/*
 * TimeSlot2ITUT.h
 *
 *  Created on: 2013-12-16
 *      Author: Administrator
 */

#ifndef TIMESLOT2ITUT_H_
#define TIMESLOT2ITUT_H_

#include "EZ_types.h"
/*
 * NOTE: ITUT ±‡¬Î÷– tug3£®1~3£©£¨ tug2£®1~7£©£¨tug1£®1~3£©
 *       TimeSlot £®1~63£©
 */
typedef struct ITUT {
    uint8 tug3;
    uint8 tug2;
    uint8 tug1;
}ITUT_T;
class TimeSlot2ITUT {
public:
    TimeSlot2ITUT();
    virtual ~TimeSlot2ITUT();
    static ITUT_T& itutFrom(uint8 ts);
    static uint8 timeslotFrom(ITUT_T& it);
};

#endif /* TIMESLOT2ITUT_H_ */
