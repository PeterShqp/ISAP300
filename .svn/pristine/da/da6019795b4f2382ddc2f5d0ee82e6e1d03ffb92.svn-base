/*
 * PairRscSDHChannel.h
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRRSCSDHCHANNEL_H_
#define PAIRRSCSDHCHANNEL_H_

#include "PairRscConnectable.h"

class PairRscSDHChannel: public PairRscConnectable {
public:
    PairRscSDHChannel(uint32 uid);
    virtual ~PairRscSDHChannel();

    uint32 getDownStream(void) {
        return downStream;
    };

    void setDownStream(uint32 d) {
        downStream = d;
    };
private:
    uint32 downStream;

private:
    static std::map<uint32, PairRscSDHChannel*> group;
public:
    /* group option */
    static PairRscSDHChannel* getInstance(uint32 uid) {
        std::map<uint32, PairRscSDHChannel*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscSDHChannel* getFirstInstance(void) {
        std::map<uint32, PairRscSDHChannel*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscSDHChannel* getNextInstance(uint32 suid) {
        std::map<uint32, PairRscSDHChannel*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRRSCSDHCHANNEL_H_ */
