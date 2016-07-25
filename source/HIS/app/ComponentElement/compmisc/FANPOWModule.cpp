/*
 * FANPOWModule.cpp
 *
 *  Created on: 2015��3��6��
 *      Author: Administrator
 */

#include "FANPOWModule.h"
#include "Uart1.h"
#include "VFCommand.h"
#include "CRC7.h"
#include <string.h>
#include <stdio.h>
#include "rtl.h"
FANPOWModule::FANPOWModule() {
	// TODO Auto-generated constructor stub

}

FANPOWModule::~FANPOWModule() {
	// TODO Auto-generated destructor stub
}
/*
 * ��ȡ������Ч���buff[0]��ʾ���buff[1]��ʾ��Ч���
 */
uint8  FANPOWModule::getBackData(uint8* buff) {
	uint8 ucFrameSumA = 0;
	uint8 ucFrameSumX = 0;
	uint8 i = 0;
	uint8 rxget = 2;//֡ͷ�����ȣ������ݣ�У��
	uint8 ucVerifyLen = 0;
	uint8 rxbuf[10] = {0};
	uint8 temp[2] = {0,0};
	if( buff == NULL ){
		return DEFErrorNullPointer;
	}
//    while(huart_dat_in(rxbuf, 10) > 0);
    if(huart_dat_in(rxbuf, 10) <= 0) {
        os_dly_wait(10);
        if(huart_dat_in(rxbuf, 10) <= 0) {
            os_dly_wait(10);
            if(huart_dat_in(rxbuf, 10) <= 0) {
#ifdef FAN_DEBUG
                printf("\nFANPOWModule::getBackData No back data\n");
#endif
                return DEFErrorNoBackMsg;
            }
        }

    }
#ifdef FAN_DEBUG
    printf("\nhuart_dat_in :");
    for( i = 0; i < 10; i++ ) {
        printf(" 0x%2x", rxbuf[i]);
    }
    printf("\n");
#endif
    if( (rxbuf[1] > 2) && (rxbuf[1] < 10) ){
        ucVerifyLen = rxbuf[1]-2;//length,command,data
        ucFrameSumA += rxbuf[1];
        ucFrameSumX ^= rxbuf[1];
        /* CheckFrameSum */
        for( i = 0; i < ucVerifyLen; i++){
            if( rxbuf[rxget] == 0x7D ){
                rxget++;
                if( rxbuf[rxget] == 0x5E ){
                    temp[i] = 0x7E;
                }
                else if( rxbuf[rxget] == 0x5D ){
                    temp[i] = 0x7D;
                }
                else{
                    return 0;
                }
            }
            else{
                temp[i] = rxbuf[rxget];
            }
            rxget++;
            ucFrameSumA += temp[i];
            ucFrameSumX ^= temp[i];
        }
        /* Check end */
        if( (ucFrameSumA == rxbuf[rxbuf[1]]) && (ucFrameSumX == rxbuf[rxbuf[1]+1]) ){
            buff[0] = temp[0];//commmand
            buff[1] = temp[1];//data
            return DEFErrorSuccess;
        }
        else{
            buff[0] = 0;
            buff[1] = 0;
        }
    }
#ifdef EZ_DEBUG
                printf("\n!!!FANPOWModule::getBackData CRC Error!!!\n");
#endif
	return DEFErrorCheckSum;
}
/*
 * ��ucLen���ȵ�ucData�������֡����
 * ucLen0λ��ʾ���ȣ���1λ��ʾ���Ĭ��Ϊ2
 */
uint8 FANPOWModule::settoFrame(uint8* ucData, uint8 ucLen){
	uint8 i = 0;
	uint8 DataSend[10];
	uint8 txsize = 0;
	uint8 ucSumA = 0;
	uint8 ucSumX = 0;
	if( ucData == NULL ){
		return DEFErrorNullPointer;
	}
	if( ucLen > 28 ){
		return DEFErrorOutOfRange;
	}
	DataSend[txsize++] = (DEFSerialDataHead);
	DataSend[txsize++] = (ucLen+1);//��Ч����ܳ���
	ucSumA += DataSend[1];
	ucSumX ^= DataSend[1];
	for( i = 1; i < (ucLen); i++){
		if( ucData[i] == 0x7E ){
			DataSend[txsize++] = (0x7D);
			DataSend[txsize++] = (0x5E);
		}
		else if( ucData[i] == 0x7D){
			DataSend[txsize++] = (0x7D);
			DataSend[txsize++] = (0x5D);
		}
		else{
			DataSend[txsize++] = (ucData[i]);
		}
		ucSumA += ucData[i];
		ucSumX ^= ucData[i];
	}
	DataSend[txsize++] = (ucSumA);
	DataSend[txsize++] = (ucSumX);
#ifdef FAN_DEBUG
    printf("\nhuart_dat_out :");
    for( i = 0; i < txsize; i++ ) {
        printf(" 0x%2x", DataSend[i]);
    }
    printf("\n");
#endif

	huart_dat_out(DataSend,txsize);
	return DEFErrorSuccess;
}
uint8 FANPOWModule::processFANCommand(VFCommand& cmd){
	uint8* DataSend = cmd.toByteStream();
	uint8* DataBack = cmd.getResultBuff();
#ifdef FAN_DEBUG
	int i;
	printf("\nVFCommand :");
	for( i = 0; i < cmd.bytes(); i++ ) {
	    printf(" 0x%2x", DataSend[i]);
	}
	printf("\n");
#endif
    settoFrame(DataSend,cmd.bytes());
    return getBackData(DataBack);
}
