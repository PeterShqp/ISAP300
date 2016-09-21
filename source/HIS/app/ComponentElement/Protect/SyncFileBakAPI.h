/*
 * SyncFileBakAPI.h
 *
 *  Created on: 2016年8月3日
 *      Author: Administrator
 */

#ifndef SOURCE_HIS_APP_COMPONENTELEMENT_PROTECT_SYNCFILEBAKAPI_H_
#define SOURCE_HIS_APP_COMPONENTELEMENT_PROTECT_SYNCFILEBAKAPI_H_

#include "os.h"

class OMUStatus;
class SyncFileBakAPI {
public:
    SyncFileBakAPI(OMUStatus* status);
    virtual ~SyncFileBakAPI();

    static bool getFileFrom(const char* fileName, uint8* ip = 0);

    static bool putFileTo(const char* fileName, uint8* ip = 0);

    void lockStandby(bool lock);
private:
    uint8 udp_cmd;
    OS_TID t_sync_files;
    OMUStatus* sta;
};

#endif /* SOURCE_HIS_APP_COMPONENTELEMENT_PROTECT_SYNCFILEBAKAPI_H_ */
