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
#include "IpPortMap.h"
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

	void showIpPortMap(void) {
	    ipPortTable.Print();
	};
	void setTransmitListTTL(uint16 time) {
		finishedPkt.setTTL(time);
	};
	bool broadcastFilter(void);
	void resetBcCount(void) {
	    bcCount = 0;
	    timer_filter_broadcast = NULL;
	};

	void setMaxBroadcastPerSecond(uint16 data) {
	    MaxBroadcastPerSec = data;
	};
	uint16 getMaxBroadcastPerSecond(void) {
	    return MaxBroadcastPerSec;
	};
//	void startFilter(void) {
//		bcfilt = true;
//	};
//	void stopFilter(void) {
//		bcfilt = false;
//	};
private:
	std::map<int, SwitchPort*> portMap;
	CFinishedPacket finishedPkt;
	MacPortMap macPortTable;
	IpPortMap ipPortTable;
    OS_TID t_sw_proccess;
//    OS_TID t_broad_filter;
    uint16 bcCount;
    uint16 MaxBroadcastPerSec;
    OS_ID timer_filter_broadcast;
};

#endif /* SWITCHCORE_H_ */
