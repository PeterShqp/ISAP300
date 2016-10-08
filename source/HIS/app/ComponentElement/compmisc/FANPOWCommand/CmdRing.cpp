/*
 * CmdRing.cpp
 *
 *  Created on: 2016年9月20日
 *      Author: Administrator
 */

#include "CmdRing.h"

CmdRing::CmdRing(uint8 ring) {
    cmd = 6;
    para[0] = ring;

}

CmdRing::~CmdRing() {
    // TODO Auto-generated destructor stub
}

