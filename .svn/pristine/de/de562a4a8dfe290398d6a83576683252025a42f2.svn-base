/*
 * SwTrace.h
 *
 *  Created on: 2015年12月11日
 *      Author: Administrator
 */

#ifndef SWTRACE_H_
#define SWTRACE_H_

#include <string>
#include <vector>
#include "EZ_types.h"

class SwTrace {
public:
    SwTrace(std::string& n);
    virtual ~SwTrace();

    void print(void);
    void receiveOnePkg(void) {
        rcvPackets++;
    };
    void sendOnePkg(void) {
        sndPackets++;
    };
    void resetCounter(void) {
        rcvPackets = 0;
        sndPackets = 0;
    };

    static void printAll(void) {
        for (int i = 0; i < swTraceArray.size(); ++i) {
            swTraceArray[i]->print();
        }
    };

    static void print(uint8 port) {
        if( port < 20 ) {
            swTraceArray[port]->print();
        }
    };

    static void clearAll(void) {
        for (int i = 0; i < swTraceArray.size(); ++i) {
            swTraceArray[i]->resetCounter();
        }
    };

    static void clear(uint8 port) {
        if( port < 20 ) {
            swTraceArray[port]->resetCounter();
        }
    };
private:
    std::string& name;
    uint32 rcvPackets;
    uint32 sndPackets;
    uint8 itsSn;
    static std::vector<SwTrace*> swTraceArray;
};

#endif /* SWTRACE_H_ */
