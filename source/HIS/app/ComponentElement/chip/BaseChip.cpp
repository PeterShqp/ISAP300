/*
 * BaseChip.cpp
 *
 *  Created on: 2013-11-26
 *      Author: Administrator
 *
 *      NOTE: 对于地址，分为寄存器地址（芯片手册中定义的寄存器编号）和内存地址（映射为EMC控制器中的地址）
 */

#include "BaseChip.h"
#include "CBaseCard.h"

#ifdef EZ_DEBUG
#include <iostream>
#endif

BaseChip::BaseChip(const std::string& n) : name(n){
#ifdef EZ_DEBUG
    std::cout << "Init chip " << name << std::endl;
#endif
}

BaseChip::~BaseChip() {
    // TODO Auto-generated destructor stub
}

