/*
 * SlotXC.h
 *
 *  Created on: 2013-11-20
 *      Author: Administrator
 */

#ifndef SLOTXC_H_
#define SLOTXC_H_

#include "CBaseSlot.h"
#include "os_def.h"

class ComponentFactory;
class RegisterAccess;
class SlotXC : public CBaseSlot {
public:
    SlotXC(int sn, RegisterAccess*, ComponentFactory* f);
    virtual ~SlotXC();

    virtual int GetCardTypeIDFromHardware();
    virtual bool supportThisCard(int cardType);
    virtual bool reset(Start_Type_E);
private:
    friend TASK void Do_Xc_Reset(void);
 //   OS_TID CXC_RESET;

};

#endif /* SLOTXC_H_ */
