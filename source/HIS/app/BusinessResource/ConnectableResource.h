/*
 * ConnectableResource.h
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#ifndef ConnectableResource_H_
#define ConnectableResource_H_

#include "BaseResource.h"
#include <map>

//class CBaseCard;
class ConfigCell;

class ConnectableResource : public BaseResource {
	static std::map<uint32, ConnectableResource*> mapPort;
public:

	ConnectableResource(uint32 uid, ConfigCell* c = 0, bool paired = false);
	virtual ~ConnectableResource();

	/* group option */
	static ConnectableResource* getResrcInstance(uint32 uid) {
		std::map<uint32, ConnectableResource*>::iterator it = mapPort.find(uid);
		if( it != mapPort.end() ) {
			return it->second;
		}
		return 0;
	};

	static ConnectableResource* getFirstInstance(void) {
		std::map<uint32, ConnectableResource*>::iterator it = mapPort.begin();
		if( it != mapPort.end() ) {
			return it->second;
		}
		return 0;
	};

	static ConnectableResource* getNextInstance(uint32 suid) {
		std::map<uint32, ConnectableResource*>::iterator it = mapPort.find(suid);
		if( it != mapPort.end() ) {
			it++;
			if( it != mapPort.end() ) {
				return it->second;
			}
		}
		return 0;
	};


//	virtual std::string& getName(void) = 0;
	virtual int getSpeedLevel(void) = 0;
	virtual bool setFrom(int fromHID) = 0; // if fromHID < 0, disconnect
	virtual uint32 getHID() = 0;

	bool connectFrom(ConnectableResource* f);
	bool connectFrom(uint32 src);
	bool disConnect(void);

	bool connectFromForce(uint32 src);

	uint32 getConnectFrom(void) {
	    if( from ) {
	        return from->getUID();
	    }
	    return 0;
	};

private:
	ConnectableResource* from;
};

#endif /* ConnectableResource_H_ */
