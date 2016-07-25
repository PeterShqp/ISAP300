/*
 * ClockZarlink30122.h
 *
 *  Created on: 2014Äê11ÔÂ19ÈÕ
 *      Author: Administrator
 */

#ifndef CLOCKZARLINK30122_H_
#define CLOCKZARLINK30122_H_

typedef enum {
    FrefChannel1, //19M
    FrefChannel2, //2M
}Fref_Channel_E;

class ChipPCMLogic;
class ClockZarlink30122 {
public:
    ClockZarlink30122(ChipPCMLogic* c);
    virtual ~ClockZarlink30122();

    void initChip(void);
    void selectFref(Fref_Channel_E ch);
private:
    ChipPCMLogic* chip;
};

#endif /* CLOCKZARLINK30122_H_ */
