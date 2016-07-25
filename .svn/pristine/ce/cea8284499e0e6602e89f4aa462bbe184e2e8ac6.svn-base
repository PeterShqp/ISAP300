/*
 * SlotEXT.h
 *
 *  Created on: 2013-11-21
 *      Author: Administrator
 */

#ifndef SLOTEXT_H_
#define SLOTEXT_H_

#include "CBaseSlot.h"

class ComponentFactory;
class RegisterAccess;
class SlotEXT : public CBaseSlot {
public:
    SlotEXT(int sn, RegisterAccess*, ComponentFactory* f);
    virtual ~SlotEXT();


    virtual int GetCardTypeIDFromHardware();
    virtual bool supportThisCard(int cardType);

    virtual bool reset(Start_Type_E);

    virtual void resetPLL(int sn);
    virtual void stopExt(bool stop) {
        FlagStart = (stop ? 0 : 1);
    };
private:
    int HOLDToReset;
    int FlagStart;
};

#endif /* SLOTEXT_H_ */
