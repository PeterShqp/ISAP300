/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CBaseSlot.h
 ** File path:			/EMUX300/Src/Main_Code/3G/SlotCard/CBaseSlot.h
 ** Created by:          Shqp
 ** Created date:        2012-4-11
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

#ifndef CBASESLOT_H_
#define CBASESLOT_H_

#include "EZ_types.h"
#include <string>

enum CheckStatus {
    NoCard = 0,
    WaitInsert,
    Working,
    WaitDelete,
};

class CBaseCard;//ֻ�ܶ��x����,�����{�Ì���ķ���
class ComponentFactory;
class RegisterAccess;

typedef enum {
	Warm_start,
	Cold_start
}Start_Type_E;
/*
 *
 */
class CBaseSlot {
public:
	CBaseSlot(int sn, RegisterAccess* ra, ComponentFactory* factory);
	virtual ~CBaseSlot();

	std::string& GetName();
	virtual int GetCardTypeIDFromHardware() = 0;    //return 0 �ղ�
	virtual bool supportThisCard(int cardType) = 0;
	virtual void resetPLL(int sn) {
	    return;
	};

	int getCurrentCardTypeID(void);


	bool cardExist() {
		return card != 0;
	};
	int GetSn() {
		return iSn;
	};
	RegisterAccess* getRegisterAccess() {
	    return ra;
	};
	CBaseCard* GetCardObject(void) {
		return card;
	};

	int GetCardType(void);

	CBaseCard* InsertCard(int TypeID);
	void RemoveCard(void);

	int PlugInCard(CBaseCard* objCard);

	int getCheckStatus(void) { return state; };
	void setCheckStatus(CheckStatus s) { state = s; };

	virtual bool reset(Start_Type_E ){
		return true;
	};
	virtual void stopExt(bool stop) {return;};
//	int PullOutCard(void);
private:
	int iSn;
	RegisterAccess* ra;
	CBaseCard* card;
	ComponentFactory* iFactory;
    CheckStatus state;

};

#endif /* CBASESLOT_H_ */
