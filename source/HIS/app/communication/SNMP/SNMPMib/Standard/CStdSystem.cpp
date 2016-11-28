/****************************************Copyright (c)*****************************************************************
 **                            Easy Broadband Technology Co., Ltd.
 **                                      
 **                                 http://www.ebbnetwork.com
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** FileName:				CStdSystem.cpp
 ** Created by:				WangChangRong
 ** Created date:			2011-8-8
 ** Version:				1.0
 ** Descriptions:			
 **---------------------------------------------------------------------------------------------------------------------
 ** Modified by:				
 ** Modified date:			
 ** Version:					
 ** Descriptions:			
 **********************************************************************************************************************/

#include "CStdSystem.h"
#include "CErrorValueDefine.h"
#include "CSnmpCell.h"
#include "CSnmpConstDefine.h"
//#include "CSlotCardConstDefine.h"
#include "CCommonDefine.h"
//#include "CClassPointer.h"
//#include "CDateTime.h"
//#include "CMain.h"
//extern CClassPointer objGlbClassPointer;
//#include "DeviceLocal.h"
#include "DeviceComponent.h"
#include "Deviceattribute.h"


/**********************************************************************************************************************
** Function name:			CStdSystem
** Descriptions:			�๹�캯��
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
CStdSystem::CStdSystem()
{
}
/**********************************************************************************************************************
** Function name:			~CStdSystem
** Descriptions:			����������
** input parameters:		None
** output parameters:		None
** Returned value:			None
** Created by:				WangChangRong
** Created date:			2011-08-08
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/

CStdSystem::~CStdSystem()
{
}

/**********************************************************************************************************************
** Function name:			InitialGroup
** Descriptions:			��ʼ����׼���ж���
** input parameters:		None
** output parameters:		None
** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
** Created by:				WangChangRong
** Created date:			2011-8-1
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CStdSystem::InitialGroup()
{
	uint32 uiInOID[] = {1,3,6,1,2,1,1};
	CSnmpVariable objMib(uiInOID,7);
	InitialNode(&objMib);
	return 0;
}

/**********************************************************************************************************************
** Function name:			GetResponse
** Descriptions:			Get����Ӧ����
** input parameters:		objpCell��		SNMP�������
** output parameters:		None
** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-09
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CStdSystem::GetResponse(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != 9 || uipInOID[8] != 0 ){//���Ⱥ�oidУ��
		return CErrorValueDefine::uiConstReturnFailed;
	}
 	switch( uipInOID[7] ){//����
 	case 1://sysDescr
 		{
 			CSnmpVariable objResponse((uint8*)"ISAP100",7,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 	case 2://sysObjectID
 		{
 			uint32 uiInOID[] = {1,3,6,1,4,1,25449,0,0};
 			uiInOID[7] = CCommonDefine::ucConstDeviceTypeID;
 			uiInOID[8] = DeviceComponent::getDeviceAttribute().getDeviceSubType();
 			CSnmpVariable objResponse(uiInOID,9);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
// 	case 3://sysUpTime
// 		{
// 			CSnmpVariable objResponse(CClassPointer::GetDataTimePointer()->GetCurrentTimeTicks()*100
// 					,CSnmpConstDefine::ucConstTimeTicks);
// 			objpCell->SetResponse(objpOID,&objResponse);
// 			return CErrorValueDefine::uiConstReturnSuccess;
// 		}
// 	case 4://sysContact
// 		{
// 			uint32 uiLen  =0 ;
// 			uint8* ucBuf = CClassPointer::GetMainPointer()->GetSystemObject()->GetDeviceAttributeObject()->GetDeviceContact(&uiLen);
//
// 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
// 			objpCell->SetResponse(objpOID,&objResponse);
// 			return CErrorValueDefine::uiConstReturnSuccess;
// 		}
 	case 5://sysName
 		{
 			uint32 uiLen  = sizeof(ucGlbConstDeviceName)-1;
 			CSnmpVariable objResponse((uint8*)ucGlbConstDeviceName,uiLen,CSnmpConstDefine::ucConstOctetString);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
// 	case 6://sysLocation
// 		{
// 			uint32 uiLen  =0 ;
// 			uint8* ucBuf = CClassPointer::GetMainPointer()->GetSystemObject()->GetDeviceAttributeObject()->GetDeviceLocation(&uiLen);
// 			CSnmpVariable objResponse(ucBuf,uiLen,CSnmpConstDefine::ucConstOctetString);
// 			objpCell->SetResponse(objpOID,&objResponse);
// 			return CErrorValueDefine::uiConstReturnSuccess;
// 		}
 	case 7://sysServices
 		{
 			CSnmpVariable objResponse(0);
 			objpCell->SetResponse(objpOID,&objResponse);
 			return CErrorValueDefine::uiConstReturnSuccess;
 		}
 	}
	return CErrorValueDefine::uiConstReturnFailed;
}


/**********************************************************************************************************************
** Function name:			SetResponse
** Descriptions:			Set����Ӧ����
** input parameters:		objpCell��		SNMP�������
** output parameters:		None
** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-09
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CStdSystem::SetResponse(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnFailed;
	}
	CSnmpVariable* objpOID = objpCell->GetCurrentVariable();
	uint32 uiOIDLen = 0;
	uint32* uipInOID = objpOID->GetOIDValue(&uiOIDLen);
	if( uiOIDLen != 9 || uipInOID[8] != 0 ){//���Ⱥ�oidУ��
		return CErrorValueDefine::uiConstReturnFailed;
	}
	switch( uipInOID[7] ){//����
	case 1://sysDescr
	case 2://sysObjectID
	case 3://sysUpTime
	case 4://sysContact
	case 5://sysName
	case 6://sysLocation
	case 7://sysServices
		{
			objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorNotWriteable);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
	/*case 4://sysContact
		{
			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//���ʹ���
				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
				return CErrorValueDefine::uiConstReturnSuccess;
			}
			uint32 uiTempLen = 0;
			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
			ucTempContact[0] = uiTempLen;
			for(uint32 i=0;i<uiTempLen;i++){
				ucTempContact[1+i] = ucpTempBuf[i];
			}
			CSnmpVariable objResponse(CErrorValueDefine::uiConstReturnSuccess);
			objpCell->SetResponse(objpOID,&objResponse);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
	case 5://sysName
		{
			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//���ʹ���
				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
				return CErrorValueDefine::uiConstReturnSuccess;
			}
			uint32 uiTempLen = 0;
			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
			ucTempName[0] = uiTempLen;
			for(uint32 i=0;i<uiTempLen;i++){
				ucTempName[1+i] = ucpTempBuf[i];
			}
			CSnmpVariable objResponse(CErrorValueDefine::uiConstReturnSuccess);
			objpCell->SetResponse(objpOID,&objResponse);
			return CErrorValueDefine::uiConstReturnSuccess;
		}
	case 6://sysLocation
		{
			CSnmpVariable* objInvalue = objpCell->GetRequestVB()->GetValueObject();
			if( objInvalue->GetSyntax() != CSnmpConstDefine::ucConstOctetString ){//���ʹ���
				objpCell->SetErrorResponse(objpOID,CSnmpConstDefine::ucConstSnmpErrorWrongType);
				return CErrorValueDefine::uiConstReturnSuccess;
			}
			uint32 uiTempLen = 0;
			uint8* ucpTempBuf = objInvalue->GetStringValue(&uiTempLen);
			ucTempLocation[0] = uiTempLen;
			for(uint32 i=0;i<uiTempLen;i++){
				ucTempLocation[1+i] = ucpTempBuf[i];
			}
			CSnmpVariable objResponse(CErrorValueDefine::uiConstReturnSuccess);
			objpCell->SetResponse(objpOID,&objResponse);
			return CErrorValueDefine::uiConstReturnSuccess;
		}*/
	}
	return CErrorValueDefine::uiConstReturnFailed;
}
/**********************************************************************************************************************
** Function name:			GetFirstValidOID
** Descriptions:			GetNext���÷���1����õ�һ�������OID
** input parameters:		objpCell��		SNMP�������
** output parameters:		None
** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-10
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CStdSystem::GetFirstValidOID(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	uint32 uiInOID[] = {1,3,6,1,2,1,1,1,0};
	CSnmpVariable objFirst(uiInOID,9);
	objpCell->GetCurrentVariable()->Clone(&objFirst);
	return CErrorValueDefine::uiConstReturnSuccess;
}
/**********************************************************************************************************************
** Function name:			GetNextValidOID
** Descriptions:			GetNext���÷���2�������һ�������OID
** input parameters:		objpCell��		SNMP�������
** output parameters:		None
** Returned value:			ִ�гɹ�����CErrorValueDefine::uiConstReturnSuccess;
** 							ִ��ʧ�ܷ���CErrorValueDefine::uiConstReturnFailed;
** 							��ָ�뷵��CErrorValueDefine::uiConstReturnInputNULLPointer;
** 							���ڴ�����CErrorValueDefine::uiConstReturnProcessing;
** Created by:				WangChangRong
** Created date:			2011-08-10
**---------------------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Descriptions:
**
**********************************************************************************************************************/
uint32 CStdSystem::GetNextValidOID(CSnmpCell* objpCell)
{
	if( objpCell == NULL ){
		return CErrorValueDefine::uiConstReturnInputNULLPointer;
	}
	CSnmpVariable objTemp;
	objTemp.Clone(objpCell->GetCurrentVariable());
	uint32 uiBaseLen = 0;
	uint32* uipBaseOID = objTemp.GetOIDValue(&uiBaseLen);
	for(uint32 i=uiBaseLen;i<9;i++){
		uipBaseOID[i] = 0;
	}
	if( uiBaseLen == 8 ){//such as 1.3.6.1.2.1.1.3
		if( uipBaseOID[7] == 0 ){
			uipBaseOID[7] = 1;
		}
		else if( uipBaseOID[7] > 7 ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
	}
	else{//���ȴ��ڵ���9
		uipBaseOID[7] ++;
		if( uipBaseOID[7] > 7 ){
			return CErrorValueDefine::uiConstReturnFailed;
		}
		uipBaseOID[8] = 0;
	}
	CSnmpVariable objNext(uipBaseOID,9);
	objpCell->GetCurrentVariable()->Clone(&objNext);
	return CErrorValueDefine::uiConstReturnSuccess;
}

