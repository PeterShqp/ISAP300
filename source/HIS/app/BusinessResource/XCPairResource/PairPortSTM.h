/*
 * PairPortSTM.h
 *
 *  Created on: 2014年11月24日
 *      Author: Administrator
 */

#ifndef PAIRPORTSTM_H_
#define PAIRPORTSTM_H_

#include "PairResource.h"

class PairRscVC4;
class PairPortSTM : public PairResource {
public:
    PairPortSTM(uint32 uid);
    virtual ~PairPortSTM();

    uint8* getJ0Transmit(uint32* len);
    uint8* getJ0Expected(uint32* len);
    bool setJ0Transmit(uint8* d, uint32 len);
    bool setJ0Expected(uint8* d, uint32 len);

    uint8 getJ0TLen(void);
    bool setJ0TLen(uint8 len);
    uint8 getJ0RLen(void);
    bool setJ0RLen(uint8 len);

    //D1~D12开销选择
    uint16 getDCCSel(void);
    bool setDCCSel(uint16 v);

    //normal configuration
    uint8 getPortEnable(void);
    bool setPortEnable(uint8 en);

    uint8 getAlsEnable(void);
    bool setAlsEnable(uint8 als);

    std::string getDescription(void);
    bool setDescription(char* buf, uint8 len);
private:
    PairRscVC4* vc4_obj[4];
    int vc4Number;
private:
    static std::map<uint32, PairPortSTM*> group;
public:
    /* group option */
    static PairPortSTM* getInstance(uint32 uid) {
        std::map<uint32, PairPortSTM*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairPortSTM* getFirstInstance(void) {
        std::map<uint32, PairPortSTM*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PairPortSTM* getNextInstance(uint32 suid) {
        std::map<uint32, PairPortSTM*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* PAIRPORTSTM_H_ */
