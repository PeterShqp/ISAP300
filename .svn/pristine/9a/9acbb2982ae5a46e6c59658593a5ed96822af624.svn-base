/*
 * ComponentFactory.cpp
 *
 *  Created on: 2013-11-13
 *      Author: Administrator
 */

#include "ComponentFactory.h"
#include "SlotXC.h"
#include "SlotEXT.h"
#include "SlotPower.h"
#include "SlotFan.h"
#include "SlotEXTNoSDH.h"
#include "EZbus.h"
#include "os.h"
#include "CBaseCard.h"
#include <iostream>

extern OS_MUT mut_ezbus;

/* �ڴ˴������豸��֧�ֵİ忨����ID */
typedef enum {
    slot_xc, slot_Ext, slot_pwr, slot_fan, slot_Ext_NoSDH, slot_invalid
}suport_slot_table;

/* �ڴ˴��������EZBUS���?ʽ�İ忨Ƭѡֵ  */
typedef enum {
    cs_xc_m, cs_xc_s, cs_ext_1, cs_ext_2, cs_ext_3, cs_ext_4, cs_ext_5, cs_invalid = -1
} slot_cs_E;

typedef struct {
    suport_slot_table type;
    int cs;
}SLOT_INFO_T;

static const SLOT_INFO_T slotMap[] = {
        {slot_xc, cs_xc_m}, {slot_xc, cs_xc_s},
        {slot_Ext, cs_ext_1}, {slot_Ext, cs_ext_2}, {slot_Ext_NoSDH, cs_ext_3}, {slot_Ext, cs_ext_4}, {slot_Ext, cs_ext_5},
        {slot_pwr, cs_invalid}, {slot_pwr, cs_invalid}, {slot_fan, cs_invalid}};

ComponentFactory::ComponentFactory() {
    // TODO Auto-generated constructor stub

}

ComponentFactory::~ComponentFactory() {
    // TODO Auto-generated destructor stub
}

void ComponentFactory::makeSlot(std::vector<CBaseSlot*>& v) {
    os_mut_init(mut_ezbus);
    CBaseSlot* slt = 0;
    RegisterAccess* ra = 0;
    for( int i = 0; i < sizeof(slotMap)/sizeof(SLOT_INFO_T); i++ ) {
        int type = slotMap[i].type;
        switch( type ) {
        case slot_xc:
            ra = new EZbus(i);
            slt = new SlotXC(i, ra, this);
            break;
        case slot_Ext:
            ra = new EZbus(i);
            slt = new SlotEXT(i, ra, this);
            break;
        case slot_fan:
            slt = new SlotFan(i, 0, this);
            break;
        case slot_pwr:
            slt = new SlotPower(i, 0, this);
            break;
        case slot_Ext_NoSDH:
            ra = new EZbus(i);
            slt = new SlotEXTNoSDH(i, ra, this);
            break;
		default:
			slt = 0;
			break;
			
       }
       if( slt ) {
           v.push_back( slt );
       }
    }
}

void ComponentFactory::clearSlot(std::vector<CBaseSlot*>& v) {
    for( int i = 0; i < sizeof(slotMap)/sizeof(SLOT_INFO_T); i++ ) {
        delete v[i];
    }

}

int ComponentFactory::getCSBySlotNumber(int sltNum) {
    return slotMap[sltNum].cs;
}

int ComponentFactory::destroyCard(CBaseCard* pc) {
    if( pc ) {
        int slot = pc->getSn();
        delete pc;

#ifdef EZ_DEBUG
        std::cout << pc->GetName() << " card plug out at slot-" << slot << std::endl;
#endif
        return 1;
    }

    return -1;
}
