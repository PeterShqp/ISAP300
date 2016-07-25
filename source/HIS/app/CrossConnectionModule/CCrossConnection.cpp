/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CCrossConnection.cpp
 ** File path:			/EMUX300/Src/Main_Code/3G/CCrossConnection.cpp
 ** Created by:          Shqp
 ** Created date:        2012-3-29
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

#include "CCrossConnection.h"
#include <string.h>
#include "ConnectableResource.h"
#include "SysError.h"

CCrossConnection::CCrossConnection(int sn, uint32 src, uint32 dest ) {
	itsSn = sn;
	itsDest = dest;
	itsSrc = src;
	itsName = "";
	itsDescription = "";
//	coupleCC = 0;
	ConnectableResource* r = ConnectableResource::getResrcInstance(dest);
	if(r) {
	    if( r->connectFrom(src) ) {
	        return;
	    }
	}
	throw SysError("creat cross connect failed!");
}

CCrossConnection::~CCrossConnection() {
	// TODO Auto-generated destructor stub
    ConnectableResource* r = ConnectableResource::getResrcInstance(itsDest);
    if(r) {
        r->disConnect();
    }
}


std::string& CCrossConnection::GetName(void) {
	return itsName;
}
std::string& CCrossConnection::GetDescription(void) {
	return itsDescription;
}

void CCrossConnection::SetName(std::string& newName) {
//    if( coupleCC != 0 ) {
//        coupleCC->SetName(newName);
//    }
	itsName.assign(newName);
}
void CCrossConnection::SetDescription(std::string& newDesc) {
//    if( coupleCC != 0 ) {
//        coupleCC->SetDescription(newDesc);
//    }
	itsDescription.assign(newDesc);
}

//void CCrossConnection::setSncp(int s) {
//	itsSNCP = s;
//}

