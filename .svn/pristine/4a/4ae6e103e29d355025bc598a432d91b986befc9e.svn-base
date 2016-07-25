/*
 * Chip16DATALogic.cpp
 *
 *  Created on: 2015��1��21��
 *      Author: Administrator
 */

#include "Chip16DATALogic.h"
#include "CBaseSlot.h"
#include "RegisterAccess.h"
#include <stdio.h>
#include "CPPTools.h"

static uint8 bitMapPort_422_485[] = {3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0};
static uint8 bitMapPort_232[] = {7, 6, 5, 4, 7, 6, 5, 4, 7, 6, 5, 4, 7, 6, 5, 4};
static const std::string chipName = "16DATALOGIC";

Chip16DATALogic::Chip16DATALogic(CBaseSlot* slt, uint8 pn):
		BaseChip(chipName){
	// TODO Auto-generated constructor stub

    MaxBoard = pn/4;
	ra = slt->getRegisterAccess();
}

Chip16DATALogic::~Chip16DATALogic() {
	// TODO Auto-generated destructor stub
}

Chip_INIT_RESULT Chip16DATALogic::ChipInit(void) {
    for (int i = 0; i < MaxBoard; ++i) {
        writeSpiReg(i, 5, i/2);
    }
    return succeed;
}

std::string Chip16DATALogic::GetVerInfo(void) {
    std::string info;
    for (int i = 0; i < MaxBoard; ++i) {
        info += getBoardVerInfo(i);
    }
    return info;
}

std::string Chip16DATALogic::getBoardVerInfo(uint8 boardsn) {
    uint8 vernum = readSpiReg(boardsn, Chip_16DT_VER);
    std::string info = "PortCPLD-" + CPPTools::number2string(boardsn+1) + ":"
            "V" + CPPTools::number2string(vernum>>4) + "." + CPPTools::number2string(vernum & 0xf) +
            ",";
    return info;
}

void Chip16DATALogic::spiselect(uint8 board){
	while(!(ra->readReg(ReadyGoReg)));
	ra->writeReg(CardCsReg,(CardCSEn | board));
	while(!(ra->readReg(ReadyGoReg)));
}
void Chip16DATALogic::spidiselect(void){
	while(!(ra->readReg(ReadyGoReg)));
    ra->writeReg(CardCsReg,(CardCSDisEn));
    while(!(ra->readReg(ReadyGoReg)));
}
/*
port0~port3��Ӧ����һ��С��
port4~port7��Ӧ���ڶ���С��
port8~port11��Ӧ�������С��
port12~port15��Ӧ�����Ŀ�С��
RWSpiRegAddr��������ȡС���Ĵ���
*/
int Chip16DATALogic::getDPtype(uint8 port) {
	int type = 0;
	spiselect(getBoardByPortID(port));
    ra->writeReg(RWSpiRegAddr, Chip_16DT_ChType);
    while(!(ra->readReg(ReadyGoReg)));
    type = ra->readReg(RSpiRegData) >> 8;
    spidiselect();
    if((type == type_RS232) || (type == type_RS422) || (type == type_RS485) )
        return type;
    else
        return 0;
}
void Chip16DATALogic::setPortEnable(uint8 port, uint8 en) {
	uint8 type = getDPtype(port);
// 	printf("type = %d,port = %d,en = %d\n",type,port,en);
	if( type == type_RS422 || type == type_RS485 ) {
		ExtCPLDRegWriteBit(getBoardByPortID(port), Chip_16DT_ChEnable, bitMapPort_422_485[port], en);
	}
	else if(type == type_RS232){
		ExtCPLDRegWriteBit(getBoardByPortID(port), Chip_16DT_ChEnable, bitMapPort_232[port], en);
	}
}

void Chip16DATALogic::setPortLoopOut(uint8 port, uint8 loop) {
	uint8 type = getDPtype(port);
// 	printf("type = %d,port = %d,loop = %d\n",type,port,loop);
	if( type == type_RS422 || type == type_RS485 ) {
		ExtCPLDRegWriteBit(getBoardByPortID(port), Chip_16DT_LoopOut, bitMapPort_422_485[port], loop);
	}
	else if(type == type_RS232){
		ExtCPLDRegWriteBit(getBoardByPortID(port), Chip_16DT_LoopOut, bitMapPort_232[port], loop);
	}
}
void Chip16DATALogic::setPortLoopIn(uint8 port, uint8 loop) {
	uint8 type = getDPtype( port);
// 	printf("type = %d,port = %d,loop = %d\n",type,port,loop);
	if( type == type_RS422 || type == type_RS485 ) {
		ExtCPLDRegWriteBit(getBoardByPortID(port), Chip_16DT_LoopIn, bitMapPort_422_485[port], loop);
	}
	else if(type == type_RS232){
		ExtCPLDRegWriteBit(getBoardByPortID(port), Chip_16DT_LoopIn, bitMapPort_232[port], loop);
	}
}
/*
*cs��Ƭѡ��regAddr��С���Ĵ�����bitpos��С�����ܼĴ�����Ӧλ��value��С������ֵ
*/
int Chip16DATALogic::ExtCPLDRegWriteBit(uint8 board,uint16 regAddr, uint8 bitpos,uint8 value) {
	uint16 temp = 0;
	temp = readSpiReg(board, regAddr);

    temp &= ~(1 << bitpos);
    temp |= (value << bitpos);
    writeSpiReg(board, regAddr, temp);
    return 0x5A;

}
void Chip16DATALogic::ledSta(bool on){
	led(LED_STA,on);
}
void Chip16DATALogic::ledWrk(bool on){
	led(LED_WRK,on);
}
void Chip16DATALogic::led(DATA_LED_E led,bool on){
	int temp = ra->readReg(REG_LED_CTRL);
	if(on){
		temp &= ~(1 << led);
	}
	else{
		temp |= (1 << led);
	}
	ra->writeReg(REG_LED_CTRL,temp);
}

uint8 Chip16DATALogic::readSpiReg(uint8 board, uint8 regaddr) {
    uint16 temp = 0;
    spiselect(board);
    ra->writeReg(RWSpiRegAddr,(regaddr));//read small card register
    while(!(ra->readReg(ReadyGoReg)));
    temp = ra->readReg(RSpiRegData) >> 8;
    spidiselect();
    return static_cast<uint8>(temp);
}
void Chip16DATALogic::writeSpiReg(uint8 board, uint8 regaddr, uint8 regdata) {
    spiselect(board);
    ra->writeReg(WSpiRegData,( regdata),0);//prevent ezbus error
    ra->writeReg(RWSpiRegAddr,((regaddr)| 0x8000));
    spidiselect();
}
