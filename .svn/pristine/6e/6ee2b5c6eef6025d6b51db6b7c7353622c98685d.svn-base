/*
 * FANPOWOnLine.h
 *
 *  Created on: 2015��3��6��
 *      Author: Administrator
 */

#ifndef FANPOWONLINE_H_
#define FANPOWONLINE_H_

#include "VFCommand.h"
#ifdef FAN_DEBUG
#include <stdio.h>
#endif

class FANPOW_OnLine: public VFCommand {
	FANPOW_OnLine();
public:
	FANPOW_OnLine(int slt){
#ifdef FAN_DEBUG
	    printf("\ncreat FANPOW_OnLine(%d)\n", slt);
#endif
		slot = slt;
	}
	virtual ~FANPOW_OnLine();
	virtual uint8 getNMByte(void) {
	    return slot;
	};
	virtual uint8 getParaLen(void){
		return 0;
	}
	virtual uint8* getPara(void){
		return 0;
	}
private:
	int slot;
};

#endif /* FANPOWONLINE_H_ */
