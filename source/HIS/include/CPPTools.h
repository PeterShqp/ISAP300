/*
 * CPPTools.h
 *
 *  Created on: 2013-4-12
 *      Author: Administrator
 */

#ifndef CPPTOOLS_H_
#define CPPTOOLS_H_

#include <string>
#include "EZ_types.h"


class CPPTools {
public:
	CPPTools();
	virtual ~CPPTools();

	static std::string number2string(uint32 i);
	static std::string hex2string(uint32 h);
	static uint32 ezip_aton(std::string& s);
	static void ezip_aton(std::string& s, uint8* ip);
// 	static uint64 ezmac_aton(std::string& s);
    static void ezmac_aton(std::string& s, uint8* mac);

    static bool getFileCRC(const char* fileName, uint32* outCRC, int crcpoint = -4);
    static bool calculateFileCRC(const char* fileName, uint32* outCRC, int endpoint = 4);


};

#endif /* CPPTOOLS_H_ */
