/*
 * SlotEXTNoSDH.h
 *
 *  Created on: 2015年5月28日
 *      Author: Administrator
 */

#ifndef SLOTEXTNOSDH_H_
#define SLOTEXTNOSDH_H_

#include "CBaseSlot.h"

class SlotEXTNoSDH: public CBaseSlot {
public:
    SlotEXTNoSDH(int sn, RegisterAccess* ra, ComponentFactory* factory);
    virtual ~SlotEXTNoSDH();

    virtual int GetCardTypeIDFromHardware();
    virtual bool supportThisCard(int cardType);

    virtual bool reset(Start_Type_E);
    virtual void stopExt(bool stop) {
        FlagStart = (stop ? 0 : 1);
    };
private:
    int HOLDToReset;
    int FlagStart;
};

#endif /* SLOTEXTNOSDH_H_ */
