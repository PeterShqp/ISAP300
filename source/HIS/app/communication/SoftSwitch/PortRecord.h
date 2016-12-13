/*
 * PortRecord.h
 *
 *  Created on: 2016年11月29日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMMUNICATION_SOFTSWITCH_PORTRECORD_H_
#define SOURCE_HIS_APP_COMMUNICATION_SOFTSWITCH_PORTRECORD_H_

#include "EZ_types.h"

class PortRecord {
    PortRecord();
    uint8 selWeight;
public:
    ~PortRecord();
    PortRecord(uint32 port);

    uint32 portSn;
    uint16 AgingCounter;
    PortRecord& operator = ( const PortRecord& t) {
        portSn = t.portSn;
        AgingCounter = t.AgingCounter;
        return *this;
    };

    bool advance(void) {
        if( selWeight != 7 ) {
            ++selWeight;
            if( selWeight == 7 ) {
                return true;
            }
        }
        return false;
    };

    bool reduce(void) {
        if( selWeight != 0 ) {
            --selWeight;
            if( selWeight == 0 ) {
                return true;
            }
        }
        return false;
    };
};

#endif /* SOURCE_HIS_APP_COMMUNICATION_SOFTSWITCH_PORTRECORD_H_ */
