/*
 * IsapCompFac.cpp
 *
 *  Created on: 2013-11-19
 *      Author: Administrator
 */

#include "IsapCompFac.h"
#include "CardXC.h"
#include <string>
#include "CardTypeID_define.h"
#include "CBaseSlot.h"
#include "SysError.h"
#include <iostream>
#include "Card24E1.h"
#include "Card30VF.h"
#include "Card8EOS.h"
#include "Card4STM1.h"
#include "Card48E1.h"
#include "Card16VF.h"
#include "Card8VF.h"
#include "Card8STM1.h"
#include "Card16E1.h"
#include "Card4EOS.h"
#include "Card8EOSFX.h"
#include "Card4EOSFX.h"
#include "Card8EOSN.h"
#include "Card8EOSFXN.h"
#include "Card16DATA.h"
#include "CardV5.h"
#include "CardFAN.h"
#include "CardACPOWER.h"
#include "CardDCPOWER.h"
#include "Card4EOSN.h"
#include "Card4EOSFXN.h"
#include "Card8DATA.h"

IsapCompFac::IsapCompFac() {
    // TODO Auto-generated constructor stub

}

IsapCompFac::~IsapCompFac() {
    // TODO Auto-generated destructor stub
}

CBaseCard* IsapCompFac::makeCard(int iTypeID, CBaseSlot* slot) {
    CBaseCard* c = 0;
    if( slot ) {
#ifdef EZ_DEBUG
        std::cout << "Slot-" << (int)slot->GetSn() << " plug in a card." << std::endl;
#endif
        try {
            switch( iTypeID ) {
                case XC_CARD_TYPEID: {
                    static std::string name("XC");
                    c = new CardXC(name, slot);
                }
                    break;
                case E1_24_CARD_TYPEID: {
                    static std::string name("24E1");
                    c = new Card24E1(name, slot);
                }
                break;
                case E1_48_CARD_TYPEID: {
                	static std::string name("48E1");
                	c = new Card48E1(name, slot);
                }
                    break;
                case EOS_8_CARD_TYPEID: {
                    static std::string name("8EOSFE");
                    c = new Card8EOS(name, slot);
                }
                    break;
                case VF_30_CARD_TYPEID: {
                    static std::string name("30VF");
                    c = new Card30VF(name, slot);
                }
                break;
                case STM_4_CARD_TYPEID: {
                    static std::string name("4STM1");
                    c = new Card4STM1(name, slot);
                }
                break;
                case STM_8_CARD_TYPEID: {
                    static std::string name("8STM1");
                    c = new Card8STM1(name, slot);
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
                case E1_16_CARD_TYPEID: {
                    static std::string name("16E1");
                    c = new Card16E1(name, slot);
                }
                break;
                case EOS_4_CARD_TYPEID: {
                    static std::string name("4EOSFE");
                    c = new Card4EOS(name, slot);
                }
                break;
                case EOS_8X_CARD_TYPEID: {
                    static std::string name("8EOSFX");
                    c = new Card8EOSFX(name, slot);
                }
                break;
                case EOS_4X_CARD_TYPEID: {
                    static std::string name("4EOSFX");
                    c = new Card4EOSFX(name, slot);
                }
                break;
                case EOS_8N_CARD_TYPEID: {
                    static std::string name("8EOSFEN");
                    c = new Card8EOSN(name, slot);
                }
                break;
                case EOS_8XN_CARD_TYPEID: {
                    static std::string name("8EOSFXN");
                    c = new Card8EOSFXN(name, slot);
                }
                break;
                case EOS_4N_CARD_TYPEID: {
                    static std::string name("8EOSFXN");
                    c = new Card4EOSN(name, slot);
                }
                break;
                case EOS_4XN_CARD_TYPEID: {
                    static std::string name("8EOSFXN");
                    c = new Card4EOSFXN(name, slot);
                }
                break;
                case DATA_16_CARD_TYPEID: {
					  static std::string name("16DATA");
					  c = new Card16DATA(name, slot);
                 }
                break;
                case V5_CARD_TYPEID: {
                    static std::string name("V5");
                    c = new CardV5(name, slot);
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
