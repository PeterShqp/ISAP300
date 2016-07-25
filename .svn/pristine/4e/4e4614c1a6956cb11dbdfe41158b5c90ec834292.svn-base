/*
 * SlotModule.cpp
 *
 *  Created on: 2013-11-19
 *      Author: Administrator
 */

#include "SlotModule.h"
#include "ComponentFactory.h"
#include "CCardOnlineChecker.h"
#include "CBaseSlot.h"
#include <stdio.h>

#ifdef EZ_DEBUG
#include <iostream>
#endif

std::vector<CBaseSlot*> SlotModule::slots;
ComponentFactory* SlotModule::fac;
CCardOnlineChecker* SlotModule::onch;

//SlotModule::SlotModule(ComponentFactory* f) {
//    fac = f;
//    fac->makeSlot(slots);
//
////    onch = new CCardOnlineChecker(this);
//
//}
SlotModule::SlotModule() {

}

SlotModule::~SlotModule() {
//    delete onch;
//    fac->clearSlot(slots);
}

void SlotModule::resetPLL(int sn) {
#ifdef EZ_DEBUG
    printf("\nSlotModule::resetPLL(%d)\n", sn);
#endif
    for (int i = 2; i < 7; ++i) {
        if( slots[i]->cardExist() ) {
            slots[i]->resetPLL(sn);
        }
    }
}

void SlotModule::startExtChecking(void) {
    for (int i = 2; i < 7; ++i) {
        slots[i]->stopExt(false);
    }
}
void SlotModule::stopExtChecking(void) {
    for (int i = 2; i < 7; ++i) {
        slots[i]->stopExt(true);
    }
}

void SlotModule::initSlotModule(ComponentFactory* f) {
    fac = f;
    fac->makeSlot(slots);
}

void SlotModule::initSlotModuleWorking(void) {
    onch = new CCardOnlineChecker();
}
void SlotModule::clearSlotModuleWorking(void) {
    delete onch;
    for (int i = 0; i < 7; ++i) {
        slots[i]->RemoveCard();
    }

}
