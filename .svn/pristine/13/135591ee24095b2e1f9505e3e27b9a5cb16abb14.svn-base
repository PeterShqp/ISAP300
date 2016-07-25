/*
 * PairTSChannel.h
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRTSCHANNEL_H_
#define PAIRTSCHANNEL_H_

#include "PairRscConnectable.h"

class PairTSChannel: public PairRscConnectable {
public:
    PairTSChannel(uint32 uid);
    virtual ~PairTSChannel();

    uint32 getDownStream(void) {
        return DownStream;
    };

    void setDownStream(uint32 id) {
        DownStream = id;
    };
private:
    uint32 DownStream;

private:
    static std::map<uint32, PairTSChannel*> group;
public:
    /* group option */
    static PairTSChannel* getInstance(uint32 uid) {
        std::map<uint32, PairTSChannel*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairTSChannel* getFirstInstance(void) {
        std::map<uint32, PairTSChannel*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairTSChannel* getNextInstance(uint32 suid) {
        std::map<uint32, PairTSChannel*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRTSCHANNEL_H_ */
