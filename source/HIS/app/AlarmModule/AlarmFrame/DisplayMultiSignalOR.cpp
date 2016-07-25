/*
 * DisplayMultiSignalOR.cpp
 *
 *  Created on: 2014Äê10ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "DisplayMultiSignalOR.h"
#include "AlarmInstance.h"

DisplayMultiSignalOR::DisplayMultiSignalOR(const char* name) : BAlarmDisplay(name) {
    // TODO Auto-generated constructor stub

}

DisplayMultiSignalOR::~DisplayMultiSignalOR() {
    // TODO Auto-generated destructor stub
}

void DisplayMultiSignalOR::update(AlarmInstance* i) {

    std::list<AlarmInstance*>::iterator it = Obs.begin();
    bool result = false;
    bool exist = false;
    while( it != Obs.end() ) {
        result |= (*it)->currentState();
        if( (*it)->equelTo(i) ) {
            //if my instance
            exist = true;
        }
        it++;
    }
    display(result && exist);
}
