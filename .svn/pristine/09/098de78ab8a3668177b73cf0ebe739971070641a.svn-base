/*
 * BaseResource.h
 *
 *  Created on: 2014-3-28
 *      Author: Administrator
 */

#ifndef BASERESOURCE_H_
#define BASERESOURCE_H_

#include "Resource.h"

class ConfigCell;
class BaseResource : public Resource {
    BaseResource();
public:
    BaseResource(uint32 uid, ConfigCell* card = 0, bool paired = false);
    virtual ~BaseResource();

    bool saveConfig(void);
    bool ifPaired(void) {
        return Paired;
    };
private:
    ConfigCell* BelongCard;
    bool Paired;

};

#endif /* BASERESOURCE_H_ */
