/****************************************Copyright (c)*****************************************************************
 **                           
 **                               Easy Broadband Technology Co., Ltd.                       
 **                         
 **                                  http://www.ebbnetwork.com  
 **
 **
 **--------------File Info----------------------------------------------------------------------------------------------
 ** File name:			CCrossConnection.h
 ** File path:			/EMUX300/Src/Main_Code/3G/CCrossConnection.h
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

#ifndef CCROSSCONNECTION_H_
#define CCROSSCONNECTION_H_

#include <string>
#include "EZ_types.h"
/*
 *
 */

typedef struct {
    uint32 E1;
    uint32 VC12;
    uint8 name[32];
    uint8 desc[32];
    uint8 sncp;
}cross_conn_data_T;

class CCrossConnection {
public:
	CCrossConnection(int sn, uint32 src, uint32 dest);
	virtual ~CCrossConnection();

	int GetSn() {
		return itsSn;
	};
	int GetSrcUID() {
		return itsSrc;
	};
	int GetdestUID() {
		return itsDest;
	};
	std::string& GetName(void);
	std::string& GetDescription(void);

	void SetName(std::string& newName);
	void SetDescription(std::string& newDesc);

//	void setCouple(CCrossConnection* c) {
//	    coupleCC = c;
//	};
//
//	bool ifCouple() {
//	    return coupleCC != 0;
//	};
//	int GetSNCP() {
//		return itsSNCP;
//	};

	void setSncp(int s);
private:
	int itsDest;
	int itsSrc;
	int itsSn;
	std::string itsName;
	std::string itsDescription;
//	CCrossConnection* coupleCC;
//	int itsSNCP;
};

#endif /* CCROSSCONNECTION_H_ */
