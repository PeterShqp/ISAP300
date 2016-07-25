/*
 * CInnerE1.h
 *
 *  Created on: 2013-12-16
 *      Author: Administrator
 */

#ifndef CINNERE1_H_
#define CINNERE1_H_

#include "CSTBus.h"
#include <string>
class DriverPCM;

class CInnerE1 : public CSTBus {
public:
    CInnerE1(uint32 uid, ConfigCell* card, uint32 mapSdhCh, DriverPCM* chip, bool paired = false);
    virtual ~CInnerE1();

//    virtual std::string& getName(void) {
//    	return itsName;
//    };
//
//private:
//    std::string itsName;

};

#endif /* CINNERE1_H_ */
