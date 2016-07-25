/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CBaseCard.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/CBaseCard.cpp
 ** Created by:          Shqp
 ** Created date:        2012-3-27
 ** Version:             V0.1
 ** Descriptions:        
 **
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:         
 ** Modified date:       
 ** Version:				
 ** Descriptions:        
 **
 ** Rechecked by:        
 ***********************************************************************************************************************/

#include "CBaseCard.h"

#include "CBaseSlot.h"

CBaseCard::CBaseCard(std::string& name, CBaseSlot* slot) : ConfigCell(name, slot->GetSn()), itsName(name) {
    itsSlot = slot;
}

CBaseCard::~CBaseCard() {
}

int CBaseCard::getSn(void) {
    return itsSlot->GetSn();
}

