/*
 * FANPOWModule.h
 *
 *  Created on: 2015��3��6��
 *      Author: Administrator
 */

#ifndef FANPOWMODULE_H_
#define FANPOWMODULE_H_
#include "EZ_types.h"
class VFCommand;
//	0x0X for common error code
#define ERR_INPUT			0x01		/*0x01, invalid input parameter*/
#define DEFErrorInput		0x01
#define DEFErrorNullPointer	0x02		/*0x02, input parameter is null pointer*/
#define DEFErrorOutOfRange	0x03		/*0x03,	input parameter out of range*/
#define DEFErrorNotFrame	0x04		/*0x04, no data need process*/
#define DEFErrorCheckSum	0x05		/*0x05, check sum of frame is error*/
#define DEFErrorMallocFailed 0x06
#define DEFErrorMacAddress 	0x07
#define DEFErrorIpAddress 	0x08
#define DEFErrorProtocal	 0x09
#define DEFErrorNotSupport	 0x0a
#define DEFErrorNoBackMsg    0x0b
#define DEFSerialDataHead		0x7E
#define DEFErrorSuccess		0x5A
#define DEFErrorFailed		0xEE
class FANPOWModule {
public:
	FANPOWModule();
	virtual ~FANPOWModule();

	uint8 processFANCommand(VFCommand& cmd);
private:
	uint8 settoFrame(uint8* ucData, uint8 ucLen);
	uint8 getBackData(uint8* ucNmByte);
};

#endif /* FANPOWMODULE_H_ */
