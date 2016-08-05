/*
 * SyncFileAPI.cpp
 *
 *  Created on: 2015��1��31��
 *      Author: Administrator
 */

#include "SyncFileAPI.h"
#include "os.h"
#include <string.h>
#include "CPPTools.h"
#include <stdio.h>
#include "ProtectAssistCell.h"
#include "DeviceComponent.h"
#include "DeviceAttribute.h"

SyncFileAPI SyncFileAPI::api;
static uint16 udp_listen_ack(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len);

static uint8 soc_massage = 0;

os_mbx_declare(mbox_sync_cmd, 50);
OS_TID task_sync_cmd;
TASK void ProcessSyncCmd(void);

os_mbx_declare(mbx_udp, 10);


bool SyncFileAPI::initSyncFileAPI(void) {
    Protected = false;
    soc_massage = udp_get_socket(0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_listen_ack);
    if( soc_massage == 0 ) {
        printf("\n!!!soc_massage = udp_get_socket failed!!!\n");
        return false;
    }
    if( !udp_open( soc_massage, 10001 ) ) {
        return false;
    }
    os_mbx_init(mbox_sync_cmd, sizeof(mbox_sync_cmd));
    os_mbx_init(mbx_udp, sizeof(mbx_udp));
    DeviceComponent::getDeviceAttribute().getProtectMCUIP(RemoteIP);

    task_sync_cmd = os_tsk_create(ProcessSyncCmd, P_SYNC + 1);
    return true;
}

bool SyncFileAPI::clearSyncFileAPI(void) {
#ifdef EXT_DEBUG
    printf("\nSyncFileAPI::clearSyncFileAPI()\n");
#endif
    os_tsk_delete(task_sync_cmd);
    udp_close(soc_massage);
    udp_release_socket(soc_massage);
    return true;
}

bool SyncFileAPI::sendAfileToRemote( const char* filename ) {
    if( !Protected ) {
        return false;
    }
    char* cmd = new char[50];
    sprintf(cmd, "%d %s", 2, filename);
    if( os_mbx_check(mbox_sync_cmd) == 0 ) {
        delete []cmd;
        return false;
    }
    os_mbx_send(mbox_sync_cmd, cmd, 0xffff);
    return true;
}

bool SyncFileAPI::sendAllFiles(void) {
    if( !Protected ) {
        return false;
    }
    FINFO info;
    memset(&info, 0, sizeof(info));
    while (ffind ("*.cfg",&info) == 0) {
        sendAfileToRemote( (char*)info.name );
    }
    memset(&info, 0, sizeof(info));
    while (ffind ("*.bit",&info) == 0) {
        sendAfileToRemote( (char*)info.name );
    }
    char* cmd = new char[50];
    sprintf(cmd, "%d %s %s", 1, "over", "Roger");
    if( os_mbx_check(mbox_sync_cmd) == 0 ) {
        delete []cmd;
        return false;
    }
    os_mbx_send(mbox_sync_cmd, cmd, 0xffff);
	return true;
}

/*
 * ����һ��UDP��Ϣ�����ȴ����Ϣ��
 *      ���ʱ������Ϣ���أ�����false
 *      ������Ϣ��������Ϣ��һ�£�����false
 *      ������Ϣ��������Ϣһ�£��򷵻�true
 *
 *      msg_ack Ϊ��ѡ��������Ϣ����ʱ������������Ϣ��msg_ack
 */
bool SyncFileAPI::sendUDPMassage(const char* msg_snd, const char* msg_expect, char* msg_ack) {

    enum { Msg_Port = 10001 };
    if( msg_snd == 0 || msg_expect == 0 ) {
#ifdef EZ_DEBUG
        if( msg_ack )
            strcpy(msg_ack, "error input");
#endif
        return false;
    }
    uint8* send_buff = udp_get_buf(strlen(msg_snd)+1);
    if( send_buff == 0 ) {
#ifdef EZ_DEBUG
        if( msg_ack )
            strcpy(msg_ack, "error udp_get_buf");
#endif
        return false;
    }
    strcpy( (char*)send_buff, msg_snd );

    while( arp_cache_ip(getRemoteIP(), ARP_FIXED_IP) != __TRUE ) {
        if( !Protected ) {
#ifdef EZ_DEBUG
        if( msg_ack )
            strcpy(msg_ack, "Remote loss");
#endif
            return false;
        }
        os_dly_wait(100);
    };
    if( udp_send(soc_massage, RemoteIP, Msg_Port, send_buff, strlen(msg_snd)+1) != __TRUE ) {
#ifdef EZ_DEBUG
        if( msg_ack )
            strcpy(msg_ack, "error udp_send");
#endif
        return false;
    }
    /* wait ack */
    void* backmsg = 0;
    bool returnV = false;
    OS_RESULT rst = os_mbx_wait(mbx_udp, &backmsg, 500);
    if( rst == OS_R_TMO ) {
#ifdef EZ_DEBUG
        if( msg_ack )
            strcpy(msg_ack, "error OS_R_TMO");
#endif
    }
    else {
        char* msg = reinterpret_cast<char*>(backmsg);
        if( msg_ack ) {
            strcpy(msg_ack, msg);
        }

        if( strcmp( msg_expect, msg) == 0 ) {
            returnV = true;
        }
    }
    delete []backmsg;
    return returnV;
}

/*
 * ����Ƿ���Ҫͬ���ļ�
 *  1.�����ļ�CRC������� CRC+�ļ������Ϣ��ͨ��UDP���͵��Զˡ�
 *  2.�ȴ�Զ˻�Ӧ
 *      2.1 �Զ˻�Ӧyes, ����1�� ��ʾ��Ҫͬ��
 *      2.2 �Զ˻�Ӧno������0�� ��ʾ����Ҫͬ��
 *      2.3 �Զ��޻�Ӧ������-1����ʾ����
 */
int SyncFileAPI::needSync( const char* filename ) {
    uint32 crc = 0;
    if( !CPPTools::getFileCRC(filename, &crc) ) {
#ifdef EZ_DEBUG
        printf("\n%s Calculate CRC Error!\n", filename);
#endif
        return -1;
    }
    char sendbuf[50] = {0};
    sprintf(sendbuf, "0x%8x+%s", crc, filename);
    char ack[50] = {0};
    if( sendUDPMassage(sendbuf, "yes", ack) ) {
#ifdef EZ_DEBUG
        printf("\n%s will sync!\n", filename);
#endif
        return 1;
    }
    else if( strcmp(ack, "no") == 0 ){
#ifdef EZ_DEBUG
        printf("\n%s same!\n", filename);
#endif
        return 0;
    }
    else {
#ifdef EZ_DEBUG
        printf("\n%s %s\n", filename, ack);
#endif
    }

    return -1;
}


uint16 udp_listen_ack(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len) {
    char* msg = new char[len];
    memcpy(msg, buf, len);
    if( os_mbx_check(mbx_udp) == 0 ) {
        delete []msg;
        return false;
    }
    os_mbx_send(mbx_udp, msg, 0xffff);
    return 0;
}

/*
 * ����Զ��ͬ�����
 * �������� 1. ��UDP��Ϣ����������ظ��ȶ�
 *          ��ʽ "1 msg" , ����msg�������� ������Ϣ�������Ӧ��Ϣ���Զ��Ÿ���
 *      2. tftp����һ���ļ�
 *          ��ʽ"2 filename"
 *         2.1 �����ļ�ǰ����ȷ���ļ�CRC�Ƿ�һ��
 *         2.2 �ļ���ͬ��������
 */
TASK void ProcessSyncCmd(void) {
    while( 1 ) {
        void* amsg = 0;
        os_mbx_wait(mbox_sync_cmd, &amsg, 0xffff);
        int cmd; //同步命令 1 发送udp消息， 2 tftp传输
        char s[30]; //udp发送消息，或 文件名
        char s2[30];//udp期待回应消息
		char* msg = (char*)amsg;
        sscanf(msg, "%d %s %s", &cmd, s, s2);
        delete []msg;
        if( !SyncFileAPI::instance().ifProtected() ) {
#ifdef EZ_DEBUG
                printf("\n!!!%s Cancel!!!\n", s);
#endif
            continue;
        }
        switch( cmd ) {
        case 1: {//upd massage
            int retryCnt = 0;
            while( retryCnt < 3 ) {
                if( SyncFileAPI::instance().sendUDPMassage(s, s2) ) {
#ifdef EZ_DEBUG
                    if( strcmp(s, "over") == 0 ) {
                        printf("\nAll files check over!\n");
                    }
                    else {
                        printf("\n%s\n", s);
                    }
#endif
                    break;
                }
                ++retryCnt;
            }
#ifdef EZ_DEBUG
            if( retryCnt == 3 )
                printf("\n!!!%s Failed!!!\n", s);
#endif
        }
        break;
        case 2: {//tftp
            int retryCnt = 0;
            int needResult = -1;
            while( retryCnt < 3 ) {
                needResult = SyncFileAPI::instance().needSync(s);
                if( needResult >= 0 ) {
                    break;
                }
                ++retryCnt;
            }
//            if( needResult == 1 ) {
//                retryCnt = 0;
//                while( retryCnt < 3 ) {
//                    if( SyncFileAPI::instance().syncFileToRemote(s) ) {
//                        std::string s1("check");
//                        s1 += s;
//                        SyncFileAPI::instance().sendUDPMassage(s1.c_str(), "succeed"); //检查*。temp文件
//                        if( memcmp(s, "main.bit", 8) == 0 ||
//                            memcmp(s, "MAIN.BIT", 8) == 0) {
//                            SyncFileAPI::instance().sendUDPMassage("upmain", "succeed");
//                        }
//                        break;
//                    }
//                    ++retryCnt;
//                }
//            }
        }
        break;
        }

    }
}
