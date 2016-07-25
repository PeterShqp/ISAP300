/*
 * CommunicationModule.h
 *
 *  Created on: 2013-11-27
 *      Author: Administrator
 */

#ifndef COMMUNICATIONMODULE_H_
#define COMMUNICATIONMODULE_H_

#include "EZ_types.h"

class CommunicationModule {
public:
    CommunicationModule();
    virtual ~CommunicationModule();

    static void initCommon(void);
    static void clearCommon(void);
    static void initWorking(void);
    static void clearWorking(void);

    static void initStandby(void);
    static void clearStandby(void);

    static uint8 getSnmpSocket(void) {
        return soc_snmp;
    };
private:
    static uint8 soc_snmp;
    static void initIpPotocal(void);

};

#endif /* COMMUNICATIONMODULE_H_ */
