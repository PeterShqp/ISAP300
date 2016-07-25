/*
 * PortSTM4.h
 *
 *  Created on: 2013-11-29
 *      Author: Administrator
 */

#ifndef PORTSTM4_H_
#define PORTSTM4_H_

#include "RealPortBase.h"
#include "STMConfigDataDefine.h"


//typedef struct {
//    uint8 J0ModeTransmit; //0 is 16bytes, 1 is single byte
//    uint8 J0ModeReceive;
//    uint8 J0Transmit[16];
//    uint8 J0Expect[16];
//    VC4_Config_Data_T RscVC4[4];
//    uint16 DCCSel;
//    uint8 TXEN;
//    uint8 ALSEnable;
//    char Desc[32];
//    uint8 DescLen;
//}STM_Config_Data_T;

class DriverSDH;
class RscVC4;

class PortSTM4 : public RealPortBase {
public:
    PortSTM4(uint32 uid, ConfigCell* card, DriverSDH& driver, STM_Config_Data_T* cfg, bool paired = false);
    virtual ~PortSTM4();

    virtual int setLoop(const int type);
//    virtual std::string& getName(void);
    virtual bool ifEnabled(void) {
        return getPortEnable() != 0;
    };

    uint32 getB1Counter(void);
    uint32 getB2Counter(void);
    uint8* getJ0Transmit(uint32* len);  //read config
    uint8* getJ0Transmit(void);         //read register
    uint8* getJ0Expected(uint32* len);  //read config
    uint8* getJ0Expected(void);         //read register
    uint8* getJ0Received(uint32* len);
    bool getLos(bool direct = false);
    bool getLof(void);
    bool getOof(void);

    bool getMsAis(void);
    bool getMsRdi(void);
    bool getMsRei(void);

    bool setJ0Transmit(uint8* d, uint32 len, bool save = true);
    bool setJ0Expected(uint8* d, uint32 len, bool save = true);

    uint8 getJ0TLen(void);
    bool setJ0TLen(uint8 len, bool save = true);
    uint8 getJ0RLen(void);
    bool setJ0RLen(uint8 len, bool save = true);

    //D1~D12����ѡ��
    uint16 getDCCSel(void);
    bool setDCCSel(uint16 v, bool save = true);

    //normal configuration
    uint8 getPortEnable(void);
    bool setPortEnable(uint8 en, bool save = true);

    uint8 getAlsEnable(void);
    bool setAlsEnable(uint8 als, bool save = true);

    std::string getDescription(void);
    bool setDescription(char* buf, uint8 len, bool save = true);


    uint8 itsHid() {
        return hid;
    };

    uint8 itsVC4Number(void) {
        return vc4Number;
    };
private:
//    std::string name;
    friend class SrcSTMPort;
    RscVC4* vc4_obj[4];
    DriverSDH& driver;
    STM_Config_Data_T* ConfigData;
    uint8 hid;
    uint8 vc4Number;

private:
    static std::map<uint32, PortSTM4*> group;
public:
    /* group option */
    static PortSTM4* getInstance(uint32 uid) {
        std::map<uint32, PortSTM4*>::iterator it = group.find(uid);
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortSTM4* getFirstInstance(void) {
        std::map<uint32, PortSTM4*>::iterator it = group.begin();
        if( it != group.end() ) {
            return it->second;
        }
        return 0;
    };

    static PortSTM4* getNextInstance(uint32 suid) {
        std::map<uint32, PortSTM4*>::iterator it = group.find(suid);
        if( it != group.end() ) {
            it++;
            if( it != group.end() ) {
                return it->second;
            }
        }
        return 0;
    };


};

#endif /* PORTSTM4_H_ */
