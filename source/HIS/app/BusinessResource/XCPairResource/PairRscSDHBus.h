/*
 * PairRscSDHBus.h
 *
 *  Created on: 2014Äê11ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRRSCSDHBUS_H_
#define PAIRRSCSDHBUS_H_

#include "PairRscConnectable.h"

class PairRscSDHChannel;
class PairRscSDHBus : public PairRscConnectable {
public:
    PairRscSDHBus(uint32 uid);
    virtual ~PairRscSDHBus();

private:
    PairRscSDHChannel* sdhch_obj[63];

private:
    static std::map<uint32, PairRscSDHBus*> group;
public:
    /* group option */
    static PairRscSDHBus* getInstance(uint32 uid) {
        std::map<uint32, PairRscSDHBus*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscSDHBus* getFirstInstance(void) {
        std::map<uint32, PairRscSDHBus*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscSDHBus* getNextInstance(uint32 suid) {
        std::map<uint32, PairRscSDHBus*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRRSCSDHBUS_H_ */
