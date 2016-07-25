/*
 * ClockSourceDefine.h
 *
 *  Created on: 2014-3-1
 *      Author: Administrator
 */

#ifndef CLOCKSOURCEDEFINE_H_
#define CLOCKSOURCEDEFINE_H_

#if defined (__cplusplus)
extern "C"
{
#endif

typedef enum {
    RCLKLocal = 300,
    RCLKB = 1,
    RCLKA,
    RCLKExt,
    RCLK2MB = 11,
    RCLK2MA,
    RCLK2MExt,
}USEABLE_RCLOCK;


#if defined (__cplusplus)
}
#endif
#endif /* CLOCKSOURCEDEFINE_H_ */
