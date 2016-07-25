/*
 * Resource.h
 *
 *  Created on: 2014Äê11ÔÂ26ÈÕ
 *      Author: Administrator
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include "EZ_types.h"

class Resource {
public:
    Resource(uint32 uid);
    virtual ~Resource();

    virtual std::string& getName(void) {
        return name;
    };
    uint32 getUID(void) {
        return itsUID;
    };
private:
    const uint32 itsUID;
    std::string name;
};

#endif /* RESOURCE_H_ */
