/****************************************Copyright (c)*****************************************************************
**                            Easy Broadband Technology Co., Ltd.
**                                      
**                                 http://www.ebbnetwork.com
**
**--------------File Info----------------------------------------------------------------------------------------------
** FileName:				CCommonDefine.h
** Created by:				WangChangRong
** Created date:			2011-7-26
** Version:					1.0
** Descriptions:			
**---------------------------------------------------------------------------------------------------------------------
** Modified by:				
** Modified date:			
** Version:					
** Descriptions:			
**********************************************************************************************************************/


#ifndef CCOMMONDEFINE_H_
#define CCOMMONDEFINE_H_

#include "EZ_types.h"
//�豸����
static const uint8 ucGlbConstDeviceName[] = "RC3000";

class CCommonDefine {
public:
	//�豸����ID����
	static const uint32 uiConstDeviceIndex	= 3000;
	static const uint32 uiConstMainBoardIndex = 100;
	//�豸�ͺ�����
//	static const uint8 ucConstDeviceTypeName[] = ;
	//�豸���ͣ�0x40
	static const uint32 ucConstDeviceTypeID = 300;
	//�豸������,ʹ�����ؿ�������
	static const uint32 ucConstDeviceSubTypeID = 30;
	static const uint32 uiconstSlotNumber = 10;
//	/*		������	Base  =   0x01000000  */
//	static const uint32 uiConstListNodeBasic = 0x01000000;
//	/*		����ڵ㶨��	Base  =   0x01010000  */
//	static const uint32 uiConstListNodeTypeBasic = uiConstListNodeBasic+0x00010000;
//	static const uint32 uiConstListNodeTypePrivateProtocol = uiConstListNodeTypeBasic+1;
	static const uint32 uiConstFactoryDateIndex = 30000;

};


#endif /* CCOMMONDEFINE_H_ */
