/*
 * PairResource.h
 *
 *  Created on: 2014Äê11ÔÂ24ÈÕ
 *      Author: Administrator
 */

#ifndef PAIRRESOURCE_H_
#define PAIRRESOURCE_H_

#include "Resource.h"
#include <map>
#include "EZ_types.h"
#include <string>

typedef enum {
    Single_A,
    Single_B,
    Protected,
    Error
}Pair_Status_E;

class BaseResource;

class PairResource : public Resource {
public:
    PairResource(uint32 uid);
    virtual ~PairResource();

    Pair_Status_E getPairStatus(void);
    bool foundResource(BaseResource*);
    bool loseResource(BaseResource*);

    template<class T> T* getPartx(Pair_Status_E x) {
        if( x == Single_A ) {
            return (T*)part0;
        }
        else if( x == Single_B ) {
            return (T*)part1;
        }
        return 0;
    }

    template<class T> std::pair<T*,T*> getParts(void) {
        T* p1 = getPartx<T>(Single_A);
        T* p2 = getPartx<T>(Single_B);
        return std::pair<T*, T*>(p1, p2);
    }

private:
    void changePairStatus(void);
    Pair_Status_E state;
    BaseResource* part0;
    BaseResource* part1;

private:
    static std::map<uint32, PairResource*> group;
public:
    /* group option */
    static PairResource* getInstance(uint32 uid) {
        std::map<uint32, PairResource*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairResource* getFirstInstance(void) {
        std::map<uint32, PairResource*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairResource* getNextInstance(uint32 suid) {
        std::map<uint32, PairResource*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRRESOURCE_H_ */
