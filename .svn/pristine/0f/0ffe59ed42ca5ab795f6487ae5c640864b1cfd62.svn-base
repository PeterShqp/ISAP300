/*
 * RealPortBase.h
 *
 *  Created on: 2013-5-27
 *      Author: Administrator
 */

#ifndef REALPORTBASE_H_
#define REALPORTBASE_H_

#include "BaseResource.h"
#include <map>

typedef enum {
	dev_and_line_loop,
	dev_loop,
	line_loop,
	no_loop
}LOOP_TYPE_E;

//class CBaseCard;

class RealPortBase : public BaseResource {
	static std::map<uint32, RealPortBase*> mapPort;
public:

	RealPortBase(uint32 uid, ConfigCell* card, bool paired = false);
	virtual ~RealPortBase();

	/* group option */
	static RealPortBase* getInstance(uint32 uid) {
		std::map<uint32, RealPortBase*>::iterator it = mapPort.find(uid);
		if( it != mapPort.end() ) {
			return it->second;
		}
		return 0;
	};

	static RealPortBase* getFirstInstance(void) {
		std::map<uint32, RealPortBase*>::iterator it = mapPort.begin();
		if( it != mapPort.end() ) {
			return it->second;
		}
		return 0;
	};

	static RealPortBase* getNextInstance(uint32 suid) {
		std::map<uint32, RealPortBase*>::iterator it = mapPort.find(suid);
		if( it != mapPort.end() ) {
			it++;
			if( it != mapPort.end() ) {
				return it->second;
			}
		}
		return 0;
	};


	virtual int setLoop(const int type) = 0;
	virtual bool ifEnabled(void) = 0;
//	virtual std::string& getName(void) = 0;

};

#endif /* REALPORTBASE_H_ */
