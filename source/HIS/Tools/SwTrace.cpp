/*
 * SwTrace.cpp
 *
 *  Created on: 2015年12月11日
 *      Author: Administrator
 */

#include "SwTrace.h"
#include <iostream>

std::vector<SwTrace*> SwTrace::swTraceArray;

SwTrace::SwTrace(std::string& n) : name(n) {
    rcvPackets = 0;
    sndPackets = 0;
    swTraceArray.push_back(this);
    itsSn = swTraceArray.size()-1;
}

SwTrace::~SwTrace() {
    swTraceArray.erase(swTraceArray.begin() + itsSn);
}

void SwTrace::print(void) {
    std::cout << std::endl;
    std::cout << " " << name << ":" << std::endl;
    std::cout << " " << "rcvPacket:" << rcvPackets << std::endl;
    std::cout << " " << "sndPacket:" << sndPackets << std::endl;
}

