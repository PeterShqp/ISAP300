/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CMibImpl.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-1
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CMibImpl.h"
#include "CErrorValueDefine.h"
#include "CStdSystem.h"
//#include "CMibDebug.h"
#include "CMibNEStruct.h"
#include "CMibAttribute.h"
#include "CMibInterface.h"
#include "CMibModule.h"
#include "CMibAlarm.h"
/**********************************************************************************************************************
** Function name:			CMibImpl
** Descriptions:			类构造函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-01
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibImpl::CMibImpl()
{
	objpSnmpMib = 0;					//上级SNMP和MIB对象指针

}
/**********************************************************************************************************************
** Function name:			~CMibImpl
** Descriptions:			类析构函数
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-01
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CMibImpl::~CMibImpl()
{
}
/**********************************************************************************************************************
** Function name:			InitialClassObject
** Descriptions:			初始化类对象，类使用前必须调用
** input parameters:		objpIn：			SNMP和MIB对象指针
** output parameters:		None
** Returned value:			执行成功返回CErrorValueDefine::uiConstReturnSuccess;
**							参数输入空指针错误CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							执行失败返回CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-8-1
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CMibImpl::InitialClassObject(CSnmpMib* objpIn)
{
	if(objpIn == 0){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}

	objpSnmpMib = objpIn;
	uint32 uiInOID[] = {1,3};
	CSnmpVariable objMib(uiInOID,2);
	InitialNode(&objMib);

	//插入标准的系统组,1.3.6.1.2.1.1
	CStdSystem* objpSystem = new CStdSystem();	
	objpSystem->InitialGroup();
	InsertDownLinkNode(objpSystem);

	//插入私有的网元结构组，1.3.6.1.4.1.25449.1.1.3
	CMibNEStruct* objpElement = new CMibNEStruct();
  	objpElement->InitialGroup();
  	InsertDownLinkNode(objpElement);

 	//插入私有的网元告警组，1.3.6.1.4.1.25449.1.1.4
   	CMibAlarm* objpAlarm = new CMibAlarm();
   	objpAlarm->InitialGroup();
   	InsertDownLinkNode(objpAlarm);

  	//插入私有的网元模块组，1.3.6.1.4.1.25449.1.1.7
 	CMibModule* objpModule = new CMibModule();
  	objpModule->InitialGroup();
 	InsertDownLinkNode(objpModule);
//
//
  	//插入私有的网元接口组，1.3.6.1.4.1.25449.1.1.8
 	CMibInterface* objpInterface = new CMibInterface();
 	objpInterface->InitialGroup();
 	InsertDownLinkNode(objpInterface);
//
	//插入私有的网元属性组，1.3.6.1.4.1.25449.1.1.9
	CMibAttribute* objpAttri = new CMibAttribute();
	objpAttri->InitialGroup();
	InsertDownLinkNode(objpAttri);
//
//	//插入私有的调试组,1.3.6.1.4.1.25449.1.1.11
// 	CMibDebug* objpDebug = new CMibDebug();
// 	objpDebug->InitialGroup();
// 	InsertDownLinkNode(objpDebug);


	return CErrorValueDefine::uiConstReturnSuccess;
}
