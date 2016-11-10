/*
 * EmuxCompFac.cpp
 *
 *  Created on: 2013-11-19
 *      Author: Administrator
 */

#include "EmuxCompFac.h"
#include "CardTypeID_define.h"
#include "CBaseCard.h"
#include "Card30VF.h"
#include "Card16VF.h"
#include "Card8VF.h"
#include "Card16DATA.h"
#include "Card32FXS.h"
#include "Card32FXO.h"
#include "Card30MT.h"
#include "CardACPOWER.h"
#include "CardDCPOWER.h"
#include "CardFAN.h"
#include "CardDXC.h"
#include "Card16FE1.h"
#include "Card8DATA.h"
#include <iostream>
#include "SysError.h"

EmuxCompFac::EmuxCompFac() {
    // TODO Auto-generated constructor stub

}

EmuxCompFac::~EmuxCompFac() {
    // TODO Auto-generated destructor stub
}

CBaseCard* EmuxCompFac::makeCard(int iTypeID, CBaseSlot* slot) {
    CBaseCard* c = 0;
    if( slot ) {
#ifdef EZ_DEBUG
        std::cout << "Slot-" << (int)slot->GetSn() << " plug in a card." << std::endl;
#endif
        try {
            switch( iTypeID ) {
                case DXC_CARD_TYPEID: {
                    static std::string name("DXC");
                    c = new CardDXC(name, slot);
                }
                break;
//                 case PCMXC_CARD_TYPEID: {
//                     static std::string name("DXC");
//                     c = new CardPCMXC(name, slot);
//                 }
//                 break;
                case VF_30_CARD_TYPEID: {
                    static std::string name("30VF");
                    c = new Card30VF(name, slot);
                }
                break;
                case VF_16_CARD_TYPEID: {
                    static std::string name("16VF");
                    c = new Card16VF(name, slot);
                }
                break;
                case VF_8_CARD_TYPEID: {
                    static std::string name("10VF");
                    c = new Card8VF(name, slot);
                }
                break;
                case DATA_16_CARD_TYPEID:{
                    static std::string name("16DATA");
                    c = new Card16DATA(name, slot);
                }
                break;
                case FXS_32_CARD_TYPEID: {
                    static std::string name("32FXS");
                    c = new Card32FXS(name, slot);
                }
                break;
                case FXO_32_CARD_TYPEID: {
                    static std::string name("32FXO");
                    c = new Card32FXO(name, slot);
                }
                break;
                case MT_30_CARD_TYPEID: {
                    static std::string name("30MT");
                    c = new Card30MT(name, slot);
                }
                break;
                case FE1_16_CARD_TYPEID: {
                    static std::string name("16FE1");
                    c = new Card16FE1(name, slot);
                }
                break;
                case DATA_8_CARD_TYPEID: {
                    static std::string name("8DATA");
                    c = new Card8DATA(name, slot);
                }
                break;
                case PWR_AC_CARD_TYPEID:{
                    static std::string name("AC_POWER");
                    c = new CardACPOWER(name, slot);
                }
                    break;
                case PWR_DC_CARD_TYPEID:{
                    static std::string name("DC_POWER");
                    c = new CardDCPOWER(name, slot);
                }
                    break;
                case FAN_CARD_TYPEID:{
                    static std::string name("FAN");
                    c = new CardFAN(name, slot);
                }
                    break;
                default:
                    return 0;
            }
            return c;
        }
        catch(SysError& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}

