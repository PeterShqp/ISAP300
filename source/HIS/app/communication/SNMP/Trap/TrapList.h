#ifndef TrapList_H
#define TrapList_H

#include "EZ_types.h"
#include "os.h"

#define TrapMaxBufferSize 255
#define TrapMaxNumber 100

class SNMPPdu;
class AlarmRecord;
class CPerformanceEventCurItem;

struct TrapBuffer
{
	uint32 valid;
	uint32 buffersize;
	uint8 buffer[TrapMaxBufferSize];	
};
class TrapList {
	TrapList(void);
	TrapList(TrapList&);
	TrapList& operator= (TrapList&);
	virtual ~TrapList(void);
	static TrapList t;
public:
	static TrapList& instance(void) {
	    return t;
	}
//	Main 		*main;			   	//
//
	TrapBuffer trapBuffer[TrapMaxNumber]; //保存待发送的trap包
	uint32 currentIndex;
	uint32 endIndex;
public:
	void Initial(void);				   		//��ʼ��
	void deInitial(void);
//	void insertList(SNMPPdu *pdu);


	void insertNewAlarmTrap(AlarmRecord *type);
	void insertRecoveryAlarmTrap(AlarmRecord *type,uint32 timetick);

//	void insertNewPerformanceEventTrap(CPerformanceEventCurItem *pfitem);
//	void insertRecoveryPerformanceEventTrap(CPerformanceEventCurItem *pfitem);


	bool isHasTrapItem();
	void sendaTrapItem();	
	
	bool ifTrapDestExist();
private:
	uint8 soc_massage;
	OS_TID tsk_send_trap;
	bool inited;
};
#endif
