/*
 * switchPortSNMP.cpp
 *
 *  Created on: 2013-6-25
 *      Author: Administrator
 */

#include "switchPortSNMP.h"
#include "SoftSwitch_define.h"
#include "PriPacket.h"
#include <string>

extern "C" void SendPacketDirect(uint8* pkt, uint32 pktlen);


switchPortSNMP::switchPortSNMP() : SwitchPortStd(SNMP_Port_Sn){
	// TODO Auto-generated constructor stub

}

switchPortSNMP::~switchPortSNMP() {
	// TODO Auto-generated destructor stub
}


int switchPortSNMP::outputPacket(PriPacket& pkg) {
	if( pkg.getSourcePort() == SNMP_Port_Sn ) {
		return -1;
	}
#ifdef EZ_DEBUG
	trace->sendOnePkg();
#endif
	uint16 len = 0;
	uint8* d = pkg.getStdStream(&len);
	SendPacketDirect(d, len);
	return 1;
}
