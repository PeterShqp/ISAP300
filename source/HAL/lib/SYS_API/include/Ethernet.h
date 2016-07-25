/*
 * Ethernet.h
 *
 *  Created on: 2013-11-29
 *      Author: Administrator
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"	
	

uint32 SetRTL8306StaticLUTUnicastEntry(uint8* ucMacAddr, uint32 uiPort);

#if defined (__cplusplus)
}
#endif
#endif /* ETHERNET_H_ */
