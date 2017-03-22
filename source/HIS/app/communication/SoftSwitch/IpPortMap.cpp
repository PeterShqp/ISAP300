/*
 * IpPortMap.cpp
 *
 *  Created on: 2016年11月29日
 *      Author: Administrator
 */

#include "IpPortMap.h"
#include "PriPacket.h"
#include <rtl.h>
#include <stdio.h>
#include <iostream>
#include "CPPTools.h"

OS_MUT mut_portip;

IpPortMap::IpPortMap() {
    // TODO Auto-generated constructor stub
    os_mut_init(mut_portip);
}

IpPortMap::~IpPortMap() {
    // TODO Auto-generated destructor stub
}

void IpPortMap::clear() {
    os_mut_wait(mut_portip, 0xffff);
    ipPortTable.clear();
    os_mut_release(mut_portip);
}

void IpPortMap::learnAddress(PriPacket& pkt) {
    uint8* ip = pkt.getSrcIP();
    if( ip == 0 ) {
        return;
    }
    IPAddr m(ip);
    PortRecord r(pkt.getSourcePort());
    os_mut_wait(mut_portip, 0xffff);
    std::map<IPAddr, PortRecord>::iterator it = ipPortTable.find(m);
    if( it != ipPortTable.end() ) {
        //已有记录，则判断变化
        if( it->second.portSn != r.portSn ) {
            //有变化
            if( it->second.reduce() ) { //降低原记录权重
                //权重降低到阈值，则替换原记录
#ifdef SW_DEBUG
        FILE* f = fopen("ipport.txt", "a");
                fprintf(f, "%8dIPAddress %d.%d.%d.%d changed from %d to %d\n",
                        os_time_get(), m.ip[0],m.ip[1],m.ip[2],m.ip[3],
                        it->second.portSn, r.portSn);
        fclose(f);
#endif
                it->second = r;
            }
        }
        else {
            //无变化
            it->second.advance(); //增加原记录权重
            it->second.AgingCounter = IpPortMap::LiveSecs; //更新老化计数

        }
    }
    else {
        //无记录，则新增记录
        ipPortTable.insert( std::pair<IPAddr, PortRecord>(m, r));
//#ifdef EZ_DEBUG
//        printf("IPAddress %02x-%02x-%02x-%02x-%02x-%02x detected at port %d\n",
//                m.mac[0],m.mac[1],m.mac[2],m.mac[3],m.mac[4],m.mac[5],
//                r.portSn);
//#endif
    }
    os_mut_release(mut_portip);
}

int IpPortMap::findOutputPort(PriPacket& pkt) {
    uint8* ip = pkt.getDesIP();
    if( ip == 0 ) {
        return -1;
    }
    IPAddr m(ip);
    os_mut_wait(mut_portip, 0xffff);
    std::map<IPAddr, PortRecord>::iterator it = ipPortTable.find(m);
    if( it != ipPortTable.end() ) {
        os_mut_release(mut_portip);
        return it->second.portSn;
    }
    os_mut_release(mut_portip);
    return -1;
}


void IpPortMap::aging(void) {
    os_mut_wait(mut_portip, 0xffff);
    std::map<IPAddr, PortRecord>::iterator it = ipPortTable.begin();
    while( it != ipPortTable.end() ) {
    	if( it->second.AgingCounter == FLAG_FIX_IP ) {
    		//fix ip 不老化
				++it;
    	}
    	else if( it->second.AgingCounter == 0 ) {
            ipPortTable.erase(it++);
        }
        else{
            --(it->second.AgingCounter);
            ++it;
        }
    }
    os_mut_release(mut_portip);
}

void IpPortMap::Print(void) {
    os_mut_wait(mut_portip, 0xffff);
    std::map<IPAddr, PortRecord>::iterator it = ipPortTable.begin();
    while( it != ipPortTable.end() ) {
        printf("IPAddress %d.%d.%d.%d at port %d\n",
                it->first.ip[0],it->first.ip[1],it->first.ip[2],it->first.ip[3],
                it->second.portSn);
        ++it;
    }
    os_mut_release(mut_portip);
}

std::string IpPortMap::listIpsAtPort(uint8 psn) {
	if( psn == 0 ) {
		std::string s("NULL");
		return s;
	}
    std::map<IPAddr, PortRecord>::iterator it = ipPortTable.begin();
    std::string rts;
    while( it != ipPortTable.end() ) {
    	if( it->second.portSn == psn ) {
    		std::string s = CPPTools::number2string(it->first.ip[0]);
    		for (int i = 1; i < 4; ++i) {
    			s += ".";
				s += CPPTools::number2string(it->first.ip[i]);
			}
    		if( it->second.AgingCounter == FLAG_FIX_IP ) {
    			s += "(s)";
    		}
    		s += ",";
    		rts += s;
    	}
    	it++;
    }
    return rts;
}

bool IpPortMap::addFixIP(uint8* ip, uint8 swport) {
	IPAddr* p =  new IPAddr(ip);

    PortRecord* r = new PortRecord(swport);
	r->AgingCounter = FLAG_FIX_IP;
    os_mut_wait(mut_portip, 0xffff);
    std::map<IPAddr, PortRecord>::iterator it = ipPortTable.find(*p);
    if( it != ipPortTable.end() ) {
    	it->second = *r;
    }
    else {
        ipPortTable.insert( std::pair<IPAddr, PortRecord>(*p, *r));
    }
    delete r;
    delete p;
    os_mut_release(mut_portip);
    return true;
}
bool IpPortMap::deleteAnIP(uint8* ip) {
	IPAddr p(ip);
    std::map<IPAddr, PortRecord>::iterator it = ipPortTable.find(p);
    if( it != ipPortTable.end() ) {
        os_mut_wait(mut_portip, 0xffff);
    	ipPortTable.erase(it);
    	os_mut_release(mut_portip);
    	return true;
    }
    return false;

}
