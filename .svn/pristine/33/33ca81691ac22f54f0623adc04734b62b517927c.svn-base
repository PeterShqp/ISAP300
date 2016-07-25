/*
 * SwitchPortInner.h
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#ifndef SWITCHPORTINNER_H_
#define SWITCHPORTINNER_H_

#include "SwitchPort.h"
#include <map>
#include "os.h"

class NMPort;

class SwitchPortInner : public SwitchPort {
	static uint32 pSnBase;
public:
	SwitchPortInner();
	SwitchPortInner(uint32 sn);
	virtual ~SwitchPortInner();

	virtual int outputPacket(PriPacket& pkg);

	//  void addDcc(DCCChannelRcv*);
	//  void addDcc(DCCChannelSnd*);
	//
	//  void removeDcc(DCCChannelRcv*);
	//  void removeDcc(DCCChannelSnd*);

	    void addNmPort(NMPort*);
	    void removePort(NMPort*);

	    uint8 getNMPortNumber(void) {
	        return nmport.size();
	    };

	    virtual bool ifDropThePacket(PriPacket& pkt);
	private:
	    friend class InnerDCCManager;
	//  std::map<uint32, DCCChannelRcv*> dccRcv;
	//  std::map<uint32, DCCChannelSnd*> dccSnd;
	    std::map<uint32, NMPort*> nmport;
	    uint8 ch[1024];
};

#endif /* SWITCHPORTINNER_H_ */
