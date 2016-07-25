/*
 * DeviceComponent.h
 *
 *  Created on: 2013-11-19
 *      Author: Administrator
 */

#ifndef DEVICECOMPONENT_H_
#define DEVICECOMPONENT_H_

class DeviceAttribute;
class SlotModule;
class XCPair;
class ComponentFactory;

class DeviceComponent {
public:
    DeviceComponent();
    virtual ~DeviceComponent();

    static int initDeviceComponent(void);
    static void clearDeviceCompnent(void);

    static int initDeviceComponentCommon(void);
//    static void clearDeviceCompnentStandby(void);

    static DeviceAttribute& getDeviceAttribute(void) {
        return *pdevattr;
    };

//    static XCPair& getXCPair(void) {
//        return *xcpair;
//    };

private:
    static DeviceAttribute* pdevattr;
    static ComponentFactory* f;

};

#endif /* DEVICECOMPONENT_H_ */
