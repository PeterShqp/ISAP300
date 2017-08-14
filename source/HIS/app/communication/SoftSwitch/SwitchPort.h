/*
 * SwitchPort.h
 *
 *  Created on: 2013-6-24
 *      Author: Administrator
 */

#ifndef SWITCHPORT_H_
#define SWITCHPORT_H_

#include <deque>
#include <map>
#include "EZ_types.h"
#include "EthMemory.h"
#include "os.h"

class PriPacket;
class SwitchPort {
	static std::map<uint32, SwitchPort*> portGroup;
	SwitchPort();
public:
	SwitchPort(uint32 portSn);
	virtual ~SwitchPort();

	/* �����˿ڰ��շ�API */
	static int inputPacket(PriPacket* f);
	int outputAPacket(PriPacket& pkg);
	uint32 getPortSn(void) {
		return sn;
	};


	/* group option */
	static SwitchPort* getSwitchPort(uint32 sn) {
		std::map<uint32, SwitchPort*>::iterator it = portGroup.find(sn);
		if( it != portGroup.end() ) {
			return it->second;
		}
		return 0;
	};

	static int broadcastThePacket( PriPacket& pkt );

	uint32* getMyMbx(void) {
	    return mbx_send;
	};
private:
	friend TASK void taskPortSend(void* p);
	uint32 sn;
	os_mbx_declare(mbx_send, 20);
	OS_TID task_send_packet;
	bool sendAPacket(PriPacket* pkg);
protected:
	virtual int outputPacket(PriPacket& pkg) = 0;
	virtual bool ifDropThePacket(PriPacket& pkt) {
	    return false;
	};
};

#endif /* SWITCHPORT_H_ */
