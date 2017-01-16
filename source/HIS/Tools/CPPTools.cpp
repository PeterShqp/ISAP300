/*
 * CPPTools.cpp
 *
 *  Created on: 2013-4-12
 *      Author: Administrator
 */

#include "CPPTools.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "CCheckData.h"
#include "os.h"

CPPTools::CPPTools() {
	// TODO Auto-generated constructor stub

}

CPPTools::~CPPTools() {
	// TODO Auto-generated destructor stub
}

std::string CPPTools::number2string(uint32 number) {
	std::ostringstream s;
	s << number;
	return s.str();

}


std::string CPPTools::hex2string(uint32 h) {
    std::ostringstream s;
    s << std::hex << h;
    return s.str();
}
/*
 * �������ʽ��IP��ַת��Ϊ32λ����
 * ��"192.168.100.1" ת��Ϊ  IP = 0xC0A86401
 */
uint32 CPPTools::ezip_aton(std::string& s) {
    uint32 netIP = 0;
    uint8 p[4] = {0};
    ezip_aton(s, p);
    netIP = (p[0] << 24) |
            (p[1] << 16) |
            (p[2] <<  8) |
            (p[3] <<  0) ;
    return netIP;
}

/*
 * �������ʽ��IP��ַת��Ϊchar���飬
 * �磺"192.168.100.1" ת��Ϊ  ip[] = {192, 168, 100, 1}
 */
void CPPTools::ezip_aton(std::string& s, uint8* ip) {
	ezip_aton(s.c_str(), ip);
}

void CPPTools::ezip_aton(const char* s, uint8* ip) {
    int p[4] = {0};
    sscanf(s, "%d.%d.%d.%d", &p[0], &p[1], &p[2], &p[3]);
    for( int i = 0; i < 4; i++ ) {
        ip[i] = (uint8)p[i];
    }

}

// uint64 CPPTools::ezmac_aton(std::string& s) {
//     uint64 macaddr = 0;
//     uint8 mac[6] = {0};
//     ezmac_aton(s, mac);
//     macaddr =   (mac[0] << 40) |
//                 (mac[1] << 32) |
//                 (mac[2] << 24) |
//                 (mac[3] << 16) |
//                 (mac[4] <<  8) |
//                 (mac[5] <<  0) ;
//     return macaddr;

// }


void CPPTools::ezmac_aton(std::string& s, uint8* mac) {
    int p[6] = {0};
    sscanf(s.c_str(), "%x-%x-%x-%x-%x-%x", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5]);
    for( int i = 0; i < 6; i++ ) {
        mac[i] = (uint8)p[i];
    }
}

bool CPPTools::getFileCRC(const char* fileName, uint32* outCRC, int crcpoint) {
    FILE* f = fopen(fileName, "rb");
//     uint32 crc = 0;
    if( f ) {
        if( fseek(f, crcpoint, SEEK_END) != 0 ) {
            return false;
        }
        uint8 buf[4] = {0};
        fread(buf, 1, sizeof(buf), f);
        fclose(f);
        *outCRC = (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | (buf[3]<<0);
//        printf("file %s CRC is 0x%8x\n", fileName, *outCRC);
        return true;
    }
    return false;
}

bool CPPTools::calculateFileCRC(const char* fileName, uint32* outCRC, int endpoint) {
    if( fileName == 0 || outCRC == 0 ) {
        return false;
    }
    FILE* fp = fopen(fileName, "rb");
    if( fp ) {
        fseek(fp, 0, SEEK_END);
        int len = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char* fileBuf = new char[len-endpoint];
        fread(fileBuf, 1, len-endpoint, fp);
        CCheckData::CRCCheck1((uint8*)fileBuf, len-endpoint, outCRC);
        delete []fileBuf;
        fclose(fp);
		return true;
    }
    return false;
}

int CPPTools::getFileSize(const char* fileName) {
    FINFO info;
    memset(&info, 0, sizeof(info));
    while (ffind (fileName,&info) == 0) {
        return info.size;
    }
    return -1;
}
