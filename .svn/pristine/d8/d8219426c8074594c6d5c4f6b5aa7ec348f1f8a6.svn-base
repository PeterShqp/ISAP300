/*
 * PairPortFE1.h
 *
 *  Created on: 2015年7月4日
 *      Author: Administrator
 */

#ifndef PAIRPORTFE1_H_
#define PAIRPORTFE1_H_

#include "PairResource.h"

class PairPortFE1 : public PairResource  {
public:
    PairPortFE1(uint32 uid);
    virtual ~PairPortFE1();

    //normal configuration
    uint8 getPortEnable(void);
    bool setPortEnable(uint8 en);

    char* getDescription(uint32* len);
    bool setDescription(char* s, uint32 len);

private:
    static std::map<uint32, PairPortFE1*> group;
public:
    /* group option */
    static PairPortFE1* getInstance(uint32 uid) {
        std::map<uint32, PairPortFE1*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairPortFE1* getFirstInstance(void) {
        std::map<uint32, PairPortFE1*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairPortFE1* getNextInstance(uint32 suid) {
        std::map<uint32, PairPortFE1*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRPORTFE1_H_ */
