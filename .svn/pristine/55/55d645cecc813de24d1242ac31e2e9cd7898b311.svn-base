/*
 * TribSTMLEDLOS.h
 *
 *  Created on: 2014Äê9ÔÂ17ÈÕ
 *      Author: Administrator
 */

#ifndef TRIBSTMLEDLOS_H_
#define TRIBSTMLEDLOS_H_

#include "DisplayMultiSignalOR.h"

class Chip8STM1Logic2;
class TribSTMLEDLOS: public DisplayMultiSignalOR {
public:
    TribSTMLEDLOS(int sn, Chip8STM1Logic2& d);
    virtual ~TribSTMLEDLOS();

    virtual void display(bool alarm);

private:
    int Sn;
    Chip8STM1Logic2& Driver;
};

#endif /* TRIBSTMLEDLOS_H_ */
