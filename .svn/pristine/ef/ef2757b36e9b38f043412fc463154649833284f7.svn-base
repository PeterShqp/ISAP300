/*
 * CRC7.h
 *
 *  Created on: 2014-4-11
 *      Author: Administrator
 */

#ifndef CRC7_H_
#define CRC7_H_

#include "EZ_types.h"

class CRC7 {
public:
    CRC7();
    virtual ~CRC7();
    static uint8 getCRC7(const uint8* src, uint32 cnt);
    static uint8 getCRC(const uint8* src, uint32 cnt);

private:
    static uint8 crc7Byte(uint8 crc, uint8 byte);
};

#endif /* CRC7_H_ */
