/*
 * NMPort.h
 *
 *  Created on: 2015年10月12日
 *      Author: Administrator
 */

#ifndef NMPORT_H_
#define NMPORT_H_

#include <string>
#include "Resource.h"
#include <vector>
#include <map>
#include "FE1ConfigDataDefine.h"

#define EZ_DEBUG

#ifdef EZ_DEBUG
#include "SwTrace.h"
#endif

class RealPortBase;
class SwitchPortInner;
class NMChannel;

class NMPort : public Resource {
public:
    NMPort(RealPortBase* phyPort, FE1_NM_Config_Data_T* cfgdata);
    virtual ~NMPort();

    bool start(void);
    bool stop(void);

    std::string& itsName(void);

    /* data IO */
    bool receivData(void);
    void sendData(uint8* d, uint32 len);

    /* config */
    uint8 getEnable(void);
    bool setEnable(uint8 en, bool save = true);
    uint8 getType(void);
    bool setType(uint8 ntype, bool save = true);
    uint32 getTopoDirection(void);
    bool setTopoDirection(uint32 dir, bool save = true);
    std::string getTsInfo(void);
    bool addNMTs(uint32 tsuid, bool save = true);
    bool deleteNMTs(uint32 tsuid, bool save = true);
    uint8* getPortDescription(uint8* len);
    bool setPortDescription(uint8* d, uint8 len, bool save = true);
    uint32 getTsMap(void);
    bool setTsMap(uint32 map, bool save = true);

    uint8* getTopoInfo(void) {
        return upstreamIP;
    };

    /* for Topo */
    uint32 getUpStreamPortUid(void) {
        return upstreamUid;
    };

    uint8* getUpStreamIP(void) {
        return upstreamIP;
    };

    uint8* getUpStreamIpMask(void) {
        return upstreamIpMask;
    };

    void setUpStreamPortUid(uint32 id) {
        upstreamUid = id;
    };

    void setUpStreamIP(uint8* ip) {
        for( int i = 0; i < 4; i++ ) {
            upstreamIP[i] = ip[i];
        }
    };

    void setUpStreamIpMask(uint8* mask) {
        for( int i = 0; i < 4; i++ ) {
            upstreamIpMask[i] = mask[i];
        }
    };

    void setInnerPort(SwitchPortInner* p) {
        port = p;
    };

    SwitchPortInner* getInnerPort(void) {
        return port;
    };

    /*for nmchannel*/
    void addNmChannel(NMChannel* c);

    void resetAgingCounter(void) {
        topoAgingCounter = 300;
    };
    bool AgingTopo(void) {
        if(topoAgingCounter == 0) {
            return false;
        }
        --topoAgingCounter;
        return topoAgingCounter == 0;
    };

    //for ip port list
    bool printIpInfo(std::string& os);
    bool addAnIp(char* ip);
    bool deleteAIP(char* ip);

private:
    uint16 topoAgingCounter;
    std::vector<NMChannel*> useableCH;
    RealPortBase* phyPort;
    NMChannel* WorkingNMCh;
    SwitchPortInner* port;
    uint32 upstreamUid;
    uint8 upstreamIP[4];
    uint8 upstreamIpMask[4];
    FE1_NM_Config_Data_T* ConfigData;
    /* for group operation */
    static std::map<uint32, NMPort*> NMPortMap;
#ifdef EZ_DEBUG
    SwTrace* trace;
#endif
public:
    static NMPort* getInstance(uint32 uid) {
        std::map<uint32, NMPort*>::iterator it = NMPortMap.find(uid);
        if( it != NMPortMap.end() ) {
            return it->second;
        }
        return 0;
    };

    static NMPort* getFirstInstance(void) {
        std::map<uint32, NMPort*>::iterator it = NMPortMap.begin();
        if( it != NMPortMap.end() ) {
            return it->second;
        }
        return 0;
    };

    static NMPort* getNextInstance(uint32 suid) {
        std::map<uint32, NMPort*>::iterator it = NMPortMap.find(suid);
        if( it != NMPortMap.end() ) {
            it++;
            if( it != NMPortMap.end() ) {
                return it->second;
            }
        }
        return 0;
    };
};

#endif /* NMPORT_H_ */
