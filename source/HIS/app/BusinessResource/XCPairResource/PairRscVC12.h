/*
 * PairRscVC12.h
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRRSCVC12_H_
#define PAIRRSCVC12_H_

#include "PairRscConnectable.h"

class PairRscVC12 : public PairRscConnectable {
public:
    PairRscVC12(uint32 uid);
    virtual ~PairRscVC12();

private:
    static std::map<uint32, PairRscVC12*> group;
public:
    /* group option */
    static PairRscVC12* getInstance(uint32 uid) {
        std::map<uint32, PairRscVC12*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscVC12* getFirstInstance(void) {
        std::map<uint32, PairRscVC12*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscVC12* getNextInstance(uint32 suid) {
        std::map<uint32, PairRscVC12*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRRSCVC12_H_ */
