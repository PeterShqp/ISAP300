/*
 * CardCPU.h
 *
 *  Created on: 2013-12-25
 *      Author: Administrator
 */

#ifndef CARDCPU_H_
#define CARDCPU_H_

//#include "Clock82V3155.h"
#include <string>

class CardCPU {
public:
    CardCPU();
    virtual ~CardCPU();

    static int itsSlot(void);
    static std::string GetVerInfo(void);
};

#endif /* CARDCPU_H_ */
