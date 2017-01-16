/*
 * SyncFileBakAPI.cpp
 *
 *  Created on: 2016年8月3日
 *      Author: Administrator
 */

#include "SyncFileBakAPI.h"
#include <list>
#include "DeviceAttribute.h"
#include "DeviceComponent.h"
#include <string.h>
#include <string>
#include <stdio.h>
#include "CPPTools.h"
#include "Lpc3250upload.h"
#include "OMUStatus.h"
#include "CBaseSlot.h"
#include "SlotModule.h"
#include "CardCPU.h"
#include "EZLog.h"

static void tftpc_notify(uint8 event);
static uint16 udp_callback(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len);
TASK void tsk_getFile(void* api);
static std::list<std::string> filesWaitingSync;
OS_MUT mut_syncfiles;
os_mbx_declare(mbx_tftpc, 10);

SyncFileBakAPI::SyncFileBakAPI(OMUStatus* status) {
    // TODO Auto-generated constructor stub
    sta = status;
    udp_cmd = udp_get_socket(0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
    udp_open( udp_cmd, 10001 );
    os_mut_init(mut_syncfiles);
    t_sync_files = os_tsk_create_ex(tsk_getFile, P_FILE_SYNC, this);
    os_mbx_init(mbx_tftpc, sizeof(mbx_tftpc));

}

SyncFileBakAPI::~SyncFileBakAPI() {
    // TODO Auto-generated destructor stub
    os_tsk_delete(t_sync_files);
    udp_close(udp_cmd);
    udp_release_socket(udp_cmd);
}

bool SyncFileBakAPI::getFileFrom(const char* fileName, uint8* ip) {
    bool returnV = false;
    uint8 cip[4] = {0};
    if( ip == 0 ) {
        DeviceComponent::getDeviceAttribute().getDeviceIP(cip);
    }
    else {
        memcpy(cip, ip, 4);
    }
    if( tftpc_get(cip, 69, fileName, NULL, tftpc_notify) == __TRUE ) {
        printf("File get started.\n");
        void* msg = 0;
        os_mbx_wait(mbx_tftpc, &msg, 0xffff);
        std::string* s = reinterpret_cast<std::string*>(msg);
        if( s ) {
            if( *s == "success" ) {
                returnV = true;
//                if( strcmp("main.bit", fileName) == 0 ) {
//                    updata_main("main.bit");
//                }
            }
            delete s;
        }
        else {
#ifdef EZ_DEBUG
            printf("\ntftpc_put back msg NULL\n");
#endif
        }

    }
    return returnV;
}

/*
 * ͨ��TFTP ͬ��һ���ļ���Զ��
 * �ȴ�TFTPC����ͳɹ�����true
 *            ���ͳ�ʱ������ʧ�ܷ���false
 */
bool SyncFileBakAPI::putFileTo(const char* fileName, uint8* ip) {
    bool returnV = false;
    uint8 rip[4] = {0};
    if( ip == 0 ) {
        DeviceComponent::getDeviceAttribute().getDeviceIP(rip);
    }
    else {
        memcpy(rip, ip, 4);
    }
    if( fileName ) {
        std::string str(fileName);
        str += ".temp";         //tftp传送的文件名改为*。temp
        if( tftpc_put(rip, 69, fileName, str.c_str(), tftpc_notify) == __TRUE ) {
            void* msg = 0;
            os_mbx_wait(mbx_tftpc, &msg, 0xffff);
            std::string* s = reinterpret_cast<std::string*>(msg);
            if( s ) {
                if( *s == "success" ) {
                    returnV = true;
                }
                delete s;
            }
            else {
#ifdef EZ_DEBUG
                printf("\ntftpc_put back msg NULL\n");
#endif
            }
        }
    }
    return returnV;
}

void SyncFileBakAPI::lockStandby(bool lock) {
    if( sta != 0 ) {
        sta->lockIt(lock);
    }
}

uint16 udp_callback(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len) {
    static char Sync[] = "yes";
    static char DontSync[] = "no";
    printf("\nReceive %s %d\n", buf, len);
    if( memcmp("over", buf, len) == 0 ) {
        uint8* send_buff = udp_get_buf(10);
        if( send_buff == 0 ) {
            printf("\n!!!udp_get_buf error!!!\n");
            return 0;
        }
        strcpy( (char*)send_buff, "Roger" );
        udp_send(socket, remip, remport, send_buff, strlen((char*)send_buff)+1);
    }
    else if( memcmp("upmain", buf, len) == 0 ) {
        uint8* send_buff = udp_get_buf(10);
        if( updata_main("main.bit") < 0 ) {

            strcpy( (char*)send_buff, "failed" );
        }
        else {
            strcpy( (char*)send_buff, "succeed" );
        }
        udp_send(socket, remip, remport, send_buff, strlen((char*)send_buff)+1);
    }
    else if( memcmp("check", buf, 5) == 0 ) {
        printf("\nstart check\n");
        char fileName[30] = {0};
        uint32 UCRC = 0;
        sscanf((char*)&buf[5], "0x%x+%s", &UCRC, fileName);
        uint32 MyCRC = 0;
        char* sendData = DontSync;
        if( CPPTools::getFileCRC(fileName, &MyCRC) ) {
            if( MyCRC == UCRC ) {
                sendData = Sync;
                printf("\nsame\n");
            }
        }
        uint8* send_buff = udp_get_buf(10);
        strcpy( (char*)send_buff, sendData );
        udp_send(socket, remip, remport, send_buff, strlen((char*)send_buff)+1);
    }
    else if( memcmp("reset", buf, 5) == 0 ) {
        uint8* send_buff = udp_get_buf(10);
        uint8 slotno = CardCPU::itsSlot() ? 0 : 1;
        CBaseSlot* objpSlot = SlotModule::getSlot(slotno);
            if (objpSlot) {
                strcpy( (char*)send_buff, "succeed" );
                objpSlot->reset(Warm_start);
            }
            else {
                strcpy( (char*)send_buff, "failed" );
            }
            udp_send(socket, remip, remport, send_buff, strlen((char*)send_buff)+1);
    }
    else if( memcmp("version", buf, 7) == 0 ) {
    	std::string s = CardCPU::GetVerInfo();
        uint8* send_buff = udp_get_buf(s.size());
        strcpy( (char*)send_buff, s.c_str() );
        udp_send(socket, remip, remport, send_buff, strlen((char*)send_buff)+1);
    }
    else {//if need sync
        char fileName[30] = {0};
        uint32 UCRC = 0;
        sscanf((char*)buf, "0x%8x+%s", &UCRC, fileName);
        uint32 MyCRC = 0;
        uint8* send_buff = udp_get_buf(10);
        char* sendData = 0;
        if( CPPTools::getFileCRC(fileName, &MyCRC) ) {
            if( MyCRC != UCRC ) {
                sendData = Sync;
                os_mut_wait(mut_syncfiles, 0xffff);
                filesWaitingSync.push_back(std::string(fileName));
                os_mut_release(mut_syncfiles);

            }
            else {
                sendData = DontSync;
            }

        }
        else {
            printf("\n!!!CRC Error!!!\n");
            os_mut_wait(mut_syncfiles, 0xffff);
            filesWaitingSync.push_back(std::string(fileName));
            os_mut_release(mut_syncfiles);
            sendData = Sync;
        }
        strcpy( (char*)send_buff, sendData );
        udp_send(socket, remip, remport, send_buff, strlen(sendData)+1);
    }
    return 0;
}

void tftpc_notify(uint8 event) {
    switch( event ) {
    case TFTPC_EVT_SUCCESS:
        if( os_mbx_check(mbx_tftpc) != 0 ) {
            os_mbx_send(mbx_tftpc, new std::string("success"), 0xffff);
        }
        else {
            printf("!!!mbx_tftpc full!!!\n");
        }
        break;
    case TFTPC_EVT_TIMEOUT:
        if( os_mbx_check(mbx_tftpc) != 0 ) {
            os_mbx_send(mbx_tftpc, new std::string("timeout"), 0xffff);
        }
        else {
            printf("!!!mbx_tftpc full!!!\n");
        }
        break;
    default:
        if( os_mbx_check(mbx_tftpc) != 0 ) {
            os_mbx_send(mbx_tftpc, new std::string("error"), 0xffff);
        }
        else {
            printf("!!!mbx_tftpc full!!!\n");
        }
        break;
    }
}

TASK void tsk_getFile(void* api) {
    SyncFileBakAPI* sync = (SyncFileBakAPI*)api;
    uint16 dlycout = 100;
    while(1) {
        os_dly_wait(dlycout);
        if( !filesWaitingSync.empty() ) {
            dlycout = 100;
            sync->lockStandby(true);
            os_mut_wait(mut_syncfiles, 0xffff);
            std::string f = filesWaitingSync.front();
            filesWaitingSync.pop_front();
            os_mut_release(mut_syncfiles);
            if( SyncFileBakAPI::getFileFrom(f.c_str()) ) {
				if( strcmp("main.bit", f.c_str()) == 0 ||
						strcmp("MAIN.BIT", f.c_str()) == 0 ) {
					updata_main("main.bit");
				}
            }
            else {
            	EZLog::instance().record("SyncFileBakAPI::getFileFrom failed!");
            }
        }
        else {
            dlycout = 500;
            sync->lockStandby(false);
        }
    }
}
