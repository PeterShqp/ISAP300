/*
 * OMUIdle.cpp
 *
 *  Created on: 2014��12��9��
 *      Author: Administrator
 */

#include "OMUIdle.h"
#include "os.h"
#include "CommunicationModule.h"
#include <string.h>
#include <stdio.h>
#include "CPPTools.h"
#include <iostream>
#include "DeviceComponent.h"
#include "DeviceAttribute.h"
#include "Lpc3250upload.h"
#include "net_api.h"
//#include "SyncFileAPI.h"

static uint16 udp_callback(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len);
static OMUIdle* pidle = 0;

OMUIdle::OMUIdle() : OMUStatus(10) {
    pidle = this;
    CommunicationModule::initStandby();
    lockIt(true);
    soc_syn_over = udp_get_socket(0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
    if( soc_syn_over != 0 ) {
        udp_open( soc_syn_over, 10001 );
    }

}

OMUIdle::~OMUIdle() {
    if( soc_syn_over != 0 ) {
        udp_close(soc_syn_over);
        udp_release_socket(soc_syn_over);
    }
    CommunicationModule::clearStandby();
    pidle = 0;
}

Working_STATE_E OMUIdle::getStatus(void) {
    return OMU_Idle;
}

uint16 udp_callback(uint8 socket, uint8 *remip, uint16 remport, uint8 *buf, uint16 len) {
    static char Sync[] = "yes";
    static char DontSync[] = "no";
    printf("\nReceive %s %d\n", buf, len);
    if( memcmp("over", buf, len) == 0 ) {
        pidle->lockIt(false);
        uint8* send_buff = udp_get_buf(10);
        strcpy( (char*)send_buff, "Roger" );
        udp_send(socket, remip, remport, send_buff, strlen((char*)send_buff)+1);
    }
    else if( memcmp("upmain", buf, len ) == 0 ) {
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
        char* fileName = (char*)&buf[5];
        printf("\nstart check %s\n", fileName);
        std::string tmpname(fileName);
        tmpname += ".temp";
        uint8* send_buff = udp_get_buf(10);
        fdelete(fileName);
        if( frename(tmpname.c_str(), fileName) != 0 ) {
            strcpy( (char*)send_buff, "failed" );
            printf("failed\n");
        }
        else {
            strcpy( (char*)send_buff, "succeed" );
            printf("succeed\n");
        }
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
            }
            else {
                sendData = DontSync;
            }

        }
        else {
            printf("\n!!!CRC Error!!!\n");
            sendData = Sync;
        }
        strcpy( (char*)send_buff, sendData );
        udp_send(socket, remip, remport, send_buff, strlen(sendData)+1);
    }
    return 0;
}
