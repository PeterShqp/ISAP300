/*
 * ComponentFactory.h
 *
 *  Created on: 2013-11-13
 *      Author: Administrator
 */

#ifndef COMPONENTFACTORY_H_
#define COMPONENTFACTORY_H_

#include <vector>

class CBaseSlot;
class CBaseCard;

class ComponentFactory {
public:
    ComponentFactory();
    virtual ~ComponentFactory();

    virtual CBaseCard* makeCard(int iTypeID, CBaseSlot*) = 0;
    virtual int destroyCard(CBaseCard*);

    void makeSlot(std::vector<CBaseSlot*>& v);
    void clearSlot(std::vector<CBaseSlot*>& v);

    static int getCSBySlotNumber(int sltNum);

};

#endif /* COMPONENTFACTORY_H_ */
