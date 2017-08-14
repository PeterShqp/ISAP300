/*
 * PriPacket.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "PriPacket.h"
#include <string.h>
#include "EthMemory.h"
#include <stdio.h>
#include "os.h"

const uint8 PriPacket::multicastAddress[6] = {0x1c, 0x88, 0x88, 0x88, 0x88, 0x88};
const uint8 PriPacket::broadcastAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

uint32 PriPacket::MIN_DURATION = 0xffff;  	//最短生存时间
uint32 PriPacket::MAX_DURATION = 0;			//最长生存时间
uint32 PriPacket::AVR_DURATION = 0;			//总平均生存时间
uint32 PriPacket::RECT_AVR_DURATION = 0;	//最近20次平均生存时间
uint32 PriPacket::TOTAL_TIMES = 0;			//总包数

int PriPacket::TRACE = 0;

/*
 * ��׼������յ����ô˹��캯��
 */
PriPacket::PriPacket(Layer2Tag& tag, uint32 swport, LAYER2FRAME* f) {
	srcPort = swport;
	priTag = tag;
	frame = f;
	stdData = f->frame;
	stdDataLen = f->length;
	refenceCounter = 1;
	nmport = 0;
	TicksOfbirth = os_time_get();
	TicksOfDeath = 0;
}


void PriPacket::deletePacket(void) {
    --refenceCounter;
    if( refenceCounter == 0 ) {
#ifdef SW_DEBUG
        printf("pkt %d real delete\n", getPrivateTag().sn);
#endif
        free_Eth_mem(frame);
        TicksOfDeath = os_time_get();
        calculateLifeTime(TicksOfbirth, TicksOfDeath);
        if( TRACE < 0 ) {
        	printLivingInfo();
        }
        else if( TRACE > 0 ) {
        	TRACE--;
        	printLivingInfo();
        }
        delete this;
    }
}

int PriPacket::packetType() {
	if( memcmp(priTag.decMAC, multicastAddress, 6) == 0 ) {
		return 2;//multicast;
	}
	else if( memcmp(priTag.decMAC, broadcastAddress, 6) == 0 ) {
		return 1;//broadcast;
	}
	return 0;//unicast;
}

void PriPacket::calculateLifeTime(uint32 start, uint32 end) {
	if( end > start ) {
		TOTAL_TIMES++;
		uint32 duration = end - start;
		if( duration < MIN_DURATION ) {
			MIN_DURATION = duration;
		}
		if( duration > MAX_DURATION ) {
			MAX_DURATION = duration;
		}

	}
}

void PriPacket::printTotalLifeTimeInfo(void) {
	printf("\ntotal life time info:\r\n");
	printf( "\tThe min is %d \r\n"
			"\tThe max is %d \r\n"
			"\tThe rcnavg is %d \r\n"
			"\tThe Total pkgs is %d\r\n"
			,MIN_DURATION, MAX_DURATION, RECT_AVR_DURATION, TOTAL_TIMES );
}

void PriPacket::printLivingInfo(void) {
	printf("\npacket id: %d \r\n", getPrivateTag().sn);
	printf("\tTicksBirth: %d \r\n", TicksOfbirth);
	printf("\tTicksDeath: %d \r\n", TicksOfDeath);
//	printf("\tprocess info: %s \r\n",processinfo.c_str());
	printf("\tprocess: %d \r\n", processLastCnt);

}
