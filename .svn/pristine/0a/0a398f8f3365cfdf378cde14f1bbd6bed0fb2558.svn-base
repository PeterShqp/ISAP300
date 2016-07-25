/*
 * SwitchCore.h
 *
 *  Created on: 2013-6-24
 *      Author: Administrator
 */

#ifndef SWITCHCORE_H_
#define SWITCHCORE_H_

#include <deque>
#include <map>
#include "CFinishedPacket.h"
#include "MacPortMap.h"
#include "os.h"

class SwitchPort;
class PriPacket;
class SwitchCore {
	SwitchCore();
	SwitchCore(const SwitchCore&);
	SwitchCore& operator= (SwitchCore&);
	virtual ~SwitchCore();

	static SwitchCore sw;
public:
	static SwitchCore& instance(void) {
		return sw;
	};

	void initSwitchCore(void);
	bool inputAPacket(PriPacket* p);
	int transmitAPacket(PriPacket& pkt);

	void aging(void);
	void finishedAPacket(PriPacket& p) {
	    finishedPkt.finishThePacket(p);
	};

	void showMacPortMap(void) {
		macPortTable.Print();
	};

	void setTransmitListTTL(uint16 time) {
		finishedPkt.setTTL(time);
	};
private:
	std::map<int, SwitchPort*> portMap;
	CFinishedPacket finishedPkt;
	MacPortMap macPortTable;
    OS_TID t_sw_proccess;
};

#endif /* SWITCHCORE_H_ */
