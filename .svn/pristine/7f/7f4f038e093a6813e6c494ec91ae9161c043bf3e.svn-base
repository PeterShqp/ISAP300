/*
 * BAlarmDisplay.cpp
 *
 *  Created on: 2014
 *      Author: Administrator
 */

#include "BAlarmDisplay.h"
#include "AlarmInstance.h"

BAlarmDisplay::BAlarmDisplay(const char* n) : name(n) {

}

BAlarmDisplay::~BAlarmDisplay() {
    // TODO Auto-generated destructor stub
}



void BAlarmDisplay::addInstance(AlarmInstance* i) {
    Obs.push_back(i);
}

void BAlarmDisplay::delInstance(AlarmInstance* i) {
    std::list<AlarmInstance*>::iterator it = Obs.begin();
    while( it != Obs.end() ) {
        if( (*it)->equelTo(i) ) {
            Obs.erase(it);
            break;
        }
        it++;
    }
}
