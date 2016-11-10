/*
 * SyncFileAPI.h
 *
 *  Created on: 2015��1��31��
 *      Author: Administrator
 */

#ifndef SYNCFILEAPI_H_
#define SYNCFILEAPI_H_

#include "EZ_types.h"
#include "os.h"

class SyncFileAPI {
    SyncFileAPI(){Protected = false;};
    SyncFileAPI(SyncFileAPI&);
    SyncFileAPI& operator= (SyncFileAPI&);
    virtual ~SyncFileAPI(){};
    static SyncFileAPI api;
public:
    static SyncFileAPI& instance(void) {
        return api;
    };

    bool initSyncFileAPI(void);
    bool clearSyncFileAPI(void);

    bool sendAfileToRemote(const char* filename);
    bool sendAllFiles(void);
    void setProtectSignal(bool p) {
        Protected = p;
    };

    bool ifProtected(void) {
        return Protected;
    };

    uint8* getRemoteIP(void) {
        return RemoteIP;
    };
    int needSync( const char* filename );
    int ifSame(const char *filename);
    void resetBakCard(void);
    void updateBakCard(void);
private:
    friend TASK void ProcessSyncCmd(void);
    bool sendUDPMassage(const char* msg_snd, const char* msg_expect = 0, char* msg_ack = 0);
    bool Protected;
    uint8 RemoteIP[4];
    OS_SEM sem_msg;

};

#endif /* SYNCFILEAPI_H_ */
