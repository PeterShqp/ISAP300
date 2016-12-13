/*
 * PortRecord.cpp
 *
 *  Created on: 2016年11月29日
 *      Author: Administrator
 */

#include "PortRecord.h"
#include "MacPortMap.h"

PortRecord::PortRecord() {
    // TODO Auto-generated constructor stub

}

PortRecord::~PortRecord() {
    // TODO Auto-generated destructor stub
}

PortRecord::PortRecord(uint32 port) {
    portSn = port;
    AgingCounter = MacPortMap::LiveSecs;
    selWeight = 3;
};
