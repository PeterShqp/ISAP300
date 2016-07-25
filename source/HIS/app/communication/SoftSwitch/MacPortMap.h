/*
 * MacPortMap.h
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#ifndef MACPORTMAP_H_
#define MACPORTMAP_H_

#include <map>
#include <string.h>
#include "EZ_types.h"

class PriPacket;
class MacPortMap {
public:
	const static uint16 LiveSecs = 3600; //mac port记录表生存时间为1小时

	MacPortMap();
	virtual ~MacPortMap();

	void learnAddress(PriPacket&);

	int findOutputPort(PriPacket&);

	void aging(void);

	void Print(void);

private:
	class MACAddr {
	public:
		MACAddr() {};
		MACAddr(uint8* d) {
			memcpy( mac, d, 6);
		};
		~MACAddr() {};
	    uint8 mac[6];

	    bool operator < (const MACAddr& m) const {
	    	for( int i = 0; i < 6; i++ ) {
	    		if( mac[i] != m.mac[i] ) {
	    			return mac[i] < m.mac[i];
	    		}
	    	}
	    	return false;
	    };

	};

	class PortRecord {
		PortRecord();
		uint8 selWeight;
	public:
		~PortRecord() {};
		PortRecord(uint32 port) {
			portSn = port;
			AgingCounter = MacPortMap::LiveSecs;
			selWeight = 3;
		};

		uint32 portSn;
		uint16 AgingCounter;
		PortRecord& operator = ( const PortRecord& t) {
			portSn = t.portSn;
			AgingCounter = t.AgingCounter;
			return *this;
		};

		bool advance(void) {
		    if( selWeight != 7 ) {
		        ++selWeight;
		        if( selWeight == 7 ) {
		            return true;
		        }
		    }
		    return false;
		};

		bool reduce(void) {
		    if( selWeight != 0 ) {
		        --selWeight;
		        if( selWeight == 0 ) {
		            return true;
		        }
		    }
		    return false;
		};
	};

	std::map<MACAddr, PortRecord> macPortTable;

};

#endif /* MACPORTMAP_H_ */
