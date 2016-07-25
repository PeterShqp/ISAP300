/*
 * TribSTMLEDALM.h
 *
 *  Created on: 2014Äê9ÔÂ18ÈÕ
 *      Author: Administrator
 */

#ifndef TRIBSTMLEDALM_H_
#define TRIBSTMLEDALM_H_

#include "DisplayMultiSignalOR.h"

class Chip8STM1CPLD;
class TribSTMLEDALM: public DisplayMultiSignalOR {
public:
    TribSTMLEDALM(int sn, Chip8STM1CPLD& d);
    virtual ~TribSTMLEDALM();

    virtual void display(bool alarm);

private:
    int itsSn;
    Chip8STM1CPLD& Driver;
};

#endif /* TRIBSTMLEDALM_H_ */
