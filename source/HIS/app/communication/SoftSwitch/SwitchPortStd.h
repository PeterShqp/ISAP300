/*
 * SwitchPortStd.h
 *
 *  Created on: 2013-6-26
 *      Author: Administrator
 */

#ifndef SWITCHPORTSTD_H_
#define SWITCHPORTSTD_H_

#include "SwitchPort.h"

#ifdef EZ_DEBUG
#include "SwTrace.h"
#endif

class SwitchPortStd : public SwitchPort {
public:
	SwitchPortStd(uint8 sn);
	virtual ~SwitchPortStd();

	static PriPacket* makePacket(LAYER2FRAME* f, uint32 portindex);	//������ʵ��˽�ж��������
	virtual int outputPacket(PriPacket& pkg) = 0;
#ifdef EZ_DEBUG
	std::string name;
    SwTrace* trace;
#endif
};

#endif /* SWITCHPORTSTD_H_ */
