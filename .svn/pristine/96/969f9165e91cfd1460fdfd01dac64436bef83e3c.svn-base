/*
 * E1LEDAis.h
 *
 *  Created on: 2014Äê10ÔÂ23ÈÕ
 *      Author: Administrator
 */

#ifndef E1LEDAIS_H_
#define E1LEDAIS_H_

#include "DisplayMultiSignalOR.h"
#include "EZ_types.h"

class Chip16E1Logic;
class E1LEDAis: public DisplayMultiSignalOR {
public:
    E1LEDAis(uint8 sn, Chip16E1Logic& d);
    virtual ~E1LEDAis();

    virtual void display(bool alarm);
private:
    uint8 ItsSn;
    Chip16E1Logic& Driver;
};

#endif /* E1LEDAIS_H_ */
