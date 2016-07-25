/*
 * ObjectReference.cpp
 *
 *  Created on: 2013-12-10
 *      Author: Administrator
 */

#include "ObjectReference.h"
#include "DeviceComponent.h"
#include "CBaseSlot.h"
#include "CardXC.h"
#include "SlotModule.h"
#include "DeviceAttribute.h"
#include "Card24E1.h"
#include "CardTypeID_define.h"
#include "CardVF.h"
#include "Card16FE1.h"
#include "CardDXC.h"
#include "GeneralLogic.h"

ObjectReference::ObjectReference() {
    // TODO Auto-generated constructor stub

}

ObjectReference::~ObjectReference() {
    // TODO Auto-generated destructor stub
}

CardXC* ObjectReference::getPXCCard(int sn) {
    CBaseSlot* pslt = SlotModule::getSlot(sn);
    if( pslt ) {
        CBaseCard* pcard = pslt->GetCardObject();
        if( pcard ) {
            CardXC* pxc = dynamic_cast<CardXC*>(pcard);
            if( pxc ) {
                return pxc;
            }
        }
    }
    return 0;
}

CardDXC* ObjectReference::getDXCCard(int sn) {
    CBaseSlot* pslt = SlotModule::getSlot(sn);
    if( pslt ) {
        CBaseCard* pcard = pslt->GetCardObject();
        if( pcard ) {
            CardDXC* pxc = dynamic_cast<CardDXC*>(pcard);
            if( pxc ) {
                return pxc;
            }
        }
    }
    return 0;
}

CardDXC* ObjectReference::getWorkingDXC(void) {
    for (int i = 0; i < 2; ++i) {
        CardDXC* xc = getDXCCard(i);
        if(xc) {
            if( GeneralLogic::instance().ifXCWorking(i) ) {
                return xc;
            }
        }
    }
    return 0;
}


Card24E1* ObjectReference::get24E1Card(int sn) {
    CBaseSlot* pslt = SlotModule::getSlot(sn);
    if( pslt ) {
        CBaseCard* pcard = pslt->GetCardObject();
        if( pcard && pcard->GetCartTypeID() == E1_24_CARD_TYPEID ) {
            Card24E1* pxc = dynamic_cast<Card24E1*>(pcard);
            if( pxc ) {
                return pxc;
            }
        }
    }
    return 0;
}

CardVF* ObjectReference::getVFCard(int sn) {
    CBaseSlot* pslt = SlotModule::getSlot(sn);
    if( pslt ) {
        CBaseCard* pcard = pslt->GetCardObject();
        int type = pcard->GetCartTypeID();
        if( pcard && (
                type == VF_30_CARD_TYPEID ||
                type == VF_16_CARD_TYPEID ||
                type == VF_8_CARD_TYPEID ||
                type == FXS_32_CARD_TYPEID ||
                type == FXO_32_CARD_TYPEID ||
                type == MT_30_CARD_TYPEID)
                ) {
            CardVF* pxc = dynamic_cast<CardVF*>(pcard);
            if( pxc ) {
                return pxc;
            }
        }
    }
    return 0;
}

int ObjectReference::getOPTMode(void) {
    int mode = DeviceComponent::getDeviceAttribute().optMode();
    if( mode == 622 ) {
        return 0;
    }
    return 1;
}

Card16FE1* ObjectReference::get16FE1Card(int sn) {
    CBaseSlot* pslt = SlotModule::getSlot(sn);
    if( pslt ) {
        CBaseCard* pcard = pslt->GetCardObject();
        int type = pcard->GetCartTypeID();
        if( pcard && (type == FE1_16_CARD_TYPEID) ) {
            Card16FE1* pc = dynamic_cast<Card16FE1*>(pcard);
            if( pc ) {
                return pc;
            }
        }
    }
    return 0;
}
