#include "EZ_types.h"
/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CBaseCard.h
 ** File path:			/EMUX300/Src/Main_Code/3G/CBaseCard.h
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

#ifndef CBASECARD_H_
#define CBASECARD_H_

#include "CPPTools.h"
#include "CBaseSlot.h"
#include "ConfigCell.h"

class CBaseSlot;
class RegisterAccess;

class CBaseCard : public ConfigCell {
	CBaseCard();
public:
	CBaseCard(std::string& name, CBaseSlot* slot);
	virtual ~CBaseCard();

	std::string& GetName() {
		return itsName;
	};

	std::string& GetCardDescr() {
		return itsCardDescr;
	};
	virtual std::string& GetCardVerInfo()=0;
	void SetCardDescr(std::string& s) {
		itsCardDescr = s;
	};

	int getSn(void);
	CBaseSlot* getItsSlot(void) {
	    return itsSlot;
	};


	virtual void closeInterrupt(void) {
	    return;
	};

	virtual int GetCartTypeID() = 0;

	virtual bool Resetcard(void) {
		return true;
	};
	virtual void resetRemoteDevice(uint8 port) {return ;};
private:
	CBaseSlot* itsSlot;
	std::string itsCardDescr;
	std::string itsName;
//	std::string cfgFileName;
//    OS_TID task_save;


};

#endif /* CBASECARD_H_ */
