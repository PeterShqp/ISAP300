/*
 * CmdFanCtrl.cpp
 *
 *  Created on: 2016年9月29日
 *      Author: Administrator
 */

#include "CmdFanCtrl.h"

CmdFanCtrl::CmdFanCtrl(uint8 sn, uint8 en) {
    cmd = 10;
    para[0] = sn;
    para[1] = en;
}

CmdFanCtrl::~CmdFanCtrl() {
    // TODO Auto-generated destructor stub
}

