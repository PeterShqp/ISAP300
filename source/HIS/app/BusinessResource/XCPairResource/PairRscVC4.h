/*
 * PairRscVC4.h
 *
 *  Created on: 2014Äê11ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRRSCVC4_H_
#define PAIRRSCVC4_H_

#include "PairRscConnectable.h"

class PairRscVC12;
class PairRscVC4: public PairRscConnectable {
public:
    PairRscVC4(uint32 uid);
    virtual ~PairRscVC4();

    uint8* getJ1Transmit(uint32* len);  //read config
    uint8* getJ1Expected(uint32* len);  //read config

    bool setJ1Transmit(uint8* d, uint32 len);
    bool setJ1Expected(uint8* d, uint32 len);

    uint8 getJ1TLen(void);
    bool setJ1TLen(uint8 len);
    uint8 getJ1RLen(void);
    bool setJ1RLen(uint8 len);

private:
    PairRscVC12* vc12_obj[63];
private:
    static std::map<uint32, PairRscVC4*> group;
public:
    /* group option */
    static PairRscVC4* getInstance(uint32 uid) {
        std::map<uint32, PairRscVC4*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscVC4* getFirstInstance(void) {
        std::map<uint32, PairRscVC4*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairRscVC4* getNextInstance(uint32 suid) {
        std::map<uint32, PairRscVC4*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRRSCVC4_H_ */
