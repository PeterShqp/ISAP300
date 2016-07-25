/*
 * InnerDCCManager.h
 *
 *  Created on: 2013-7-1
 *      Author: Administrator
 */

#ifndef INNERDCCMANAGER_H_
#define INNERDCCMANAGER_H_

#include "EZ_types.h"
#include <map>

class NMPort;

class InnerDCCManager {
    InnerDCCManager();
    InnerDCCManager(InnerDCCManager&);
    InnerDCCManager& operator= (InnerDCCManager&);
    virtual ~InnerDCCManager();
    static InnerDCCManager dccmng;
public:
    static InnerDCCManager& instance(void) {
        return dccmng;
    };

	void start(bool first = false);
	void stop(bool first = false);

    bool join(NMPort* port, uint8 swportid = 0);
    void leave(NMPort* port);

    NMPort* getfirstNMPort(void) {
        std::map<uint32, NMPort*>::iterator it = workingNMPort.begin();
        return it->second;
    };
    NMPort* getNextNMPort(uint32 uid) {
        std::map<uint32, NMPort*>::iterator it = workingNMPort.find(uid);
        if( it != workingNMPort.end() ) {
            it++;
            if( it != workingNMPort.end() ) {
                return it->second;
            }
        }
        return 0;
    }

private:
	std::map<uint32, NMPort*> workingNMPort;

};

#endif /* INNERDCCMANAGER_H_ */
