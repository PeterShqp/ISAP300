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

const uint8 PriPacket::multicastAddress[6] = {0x1c, 0x88, 0x88, 0x88, 0x88, 0x88};
const uint8 PriPacket::broadcastAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};


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
}


void PriPacket::deletePacket(void) {
    --refenceCounter;
    if( refenceCounter == 0 ) {
#ifdef SW_DEBUG
        printf("pkt %d real delete\n", getPrivateTag().sn);
#endif
        free_Eth_mem(frame);
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
