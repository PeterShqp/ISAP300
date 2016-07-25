/*
 * Chip16DATALogic.h
 *
 *  Created on: 2015��1��21��
 *      Author: Administrator
 */

#ifndef CHIP16DATALOGIC_H_
#define CHIP16DATALOGIC_H_
#include "BaseChip.h"
#include "s1l_line_input.h"
class CBaseSlot;
class RegisterAccess;
typedef enum {
	type_RS485 = 5,
	type_RS422,
	type_RS232,
}Data_Port_E;
/* spi channel 0 */
#define Chip_16DT_Type	0x00
#define Chip_16DT_VER	0x0f
/* spi channel 1 & 2 */
#define Chip_16DT_ChType     0x0001
#define Chip_16DT_ChEnable   0x0002 // bit7 ~ 4 -> RS422/485 CH1~4;
								//bit3 ~ 0 -> RS232 CH1~4;
#define Chip_16DT_LoopOut    0x0003
#define Chip_16DT_LoopIn	 0x0004
#define Chip_16DT_TS_Sel     0x0005 //bit0 0 (1~4, 17~20); 1 (5~8, 21~24)

#define RWSpiRegAddr ( 0x0000 )//bit15=1,W;bit15=0,R
#define WSpiRegData  ( 0x0001 ) //bit0~bit7 �Ͱ�λ
#define RSpiRegData  ( 0x0001 )//bit8~bit15�߰�λ
#define ReadyGoReg   ( 0x0002 )//bit15=1,ready;or busy;
#define LedReg		 ( 0x0003 )//bit0 run led/bit1 status led
#define CardCsReg	 ( 0x0004 )
#define CardCSEn     ( 0x0004 )
#define CardCSDisEn  ( 0x0000 )
typedef enum {
     LED_WRK,LED_STA,
}DATA_LED_E;
class Chip16DATALogic: public BaseChip {
    static const uint16 REG_LED_CTRL = 0x0003;//BTI0:RUN;BIT1:STATUS
	Chip16DATALogic();
public:
	Chip16DATALogic(CBaseSlot* slt, uint8 pn);
	virtual ~Chip16DATALogic();

	int getDPtype( uint8 port);
    virtual Chip_INIT_RESULT ChipInit(void);
    virtual std::string GetVerInfo(void);
    int ExtCPLDRegWriteBit(uint8 cs,uint16 regAddr, uint8 bitpos,uint8 value);
	void setPortEnable(uint8 port, uint8 en);
	void setPortLoopOut(uint8 port, uint8 loop);
	void setPortLoopIn(uint8 port, uint8 loop);

	void led(DATA_LED_E led ,bool on);
    void ledSta(bool on);
    void ledWrk(bool on);
private:
    uint8 readSpiReg(uint8 board, uint8 regaddr);
    void writeSpiReg(uint8 board, uint8 regaddr, uint8 regdata);
    void spiselect(uint8 board);
    void spidiselect(void);
    uint8 getBoardByPortID(uint8 port) {
        return port >> 2;
    };
	RegisterAccess* ra;
	uint8 MaxBoard;
	std::string getBoardVerInfo(uint8 boardsn);
};


#endif /* CHIP16DATALOGIC_H_ */
