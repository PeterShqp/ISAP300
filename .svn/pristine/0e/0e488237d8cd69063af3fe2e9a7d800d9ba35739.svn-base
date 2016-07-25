/*
 * ChipEmuxLogic.h
 *
 *  Created on: 2015年6月3日
 *      Author: Administrator
 */

#ifndef CHIPEMUXLOGIC_H_
#define CHIPEMUXLOGIC_H_

#include "FPGAChip.h"
#include "DriverPCM.h"

class ChipEmuxLogic: public FPGAChip, public DriverPCM {
public:
    ChipEmuxLogic(CBaseSlot* slot);
    virtual ~ChipEmuxLogic();

    virtual Chip_INIT_RESULT ChipInit(void);
    virtual std::string GetVerInfo(void);

    /*Clock*/
    virtual void resetClockChip(void) {};
    virtual void selectClockSource(USEABLE_RCLOCK cs) {};
    virtual void setExtClockMode(USEABLE_RCLOCK c, ExtClock_type_E mode) {};

    virtual void selectPCMClock(uint8 src);

    /*64K cross connect*/
    virtual bool CreatCrossConnection(uint32 toCh, uint32 toTs, uint32 fromCh, uint32 fromTs);
    virtual bool RemoveCrossConnection(uint32 Ch, uint32 Ts);

    /*port state*/
    virtual uint16 getHID(uint32 uid);
    virtual bool itsLOS(int e1);
    virtual bool itsAIS(int e1);
    virtual bool itsLOF(int e1);
    virtual bool itsLOMF(int e1);

    /*
     * for DCC
     */
    virtual bool setDCCOH(int ch, uint16 data) {return false;};

    virtual bool ifHavePacket(NM_CH_E ch) {return false;};
    virtual int getPacketLen(NM_CH_E ch) {return 0;};
    virtual uint32 GetDCCPacket(NM_CH_E ch, uint8* buff, uint16 len, uint16 startPos = 0) {return 0;};
    virtual void DccSendPacket(NM_CH_E ch, uint8* data, uint16 len) {};
    virtual void clearDccRdBufForce(NM_CH_E ch) {};

    /*
     * for Sabit
     */
    virtual void setSabitInterruptEnable(uint8 ch, uint8 en){return;};
    virtual bool ifSaHavePacket(void);
    virtual uint8 getSourceCh(void);
    virtual int getSaPacketLen(void);
    virtual bool getSaPacket(uint8* buff, uint16 len, uint16 startPos = 0);
    virtual void readSaPacketOver(void);

    virtual void sendSaPacket(uint8 ch, uint8* data, uint16 len);

    /*
     * for dcn
     */
    virtual void setDcnInterruptEnable(uint8 ch, uint8 en){return;};
    virtual bool selectDcnTs(uint8 ch, uint32 tsmap) { return false;};
    virtual uint32 getDcnTsMap(uint8 ch) {return false;};
    virtual bool ifDcnHavePacket(uint8 ch) { return false;};
    virtual int getDcnPacketLen(uint8 ch) { return 0;};
    virtual bool getDcnPacket(uint8 ch, uint8* buff, uint16 len) {return false;};
    virtual void readDcnPacketOver(uint8 ch) {return;};

    virtual void sendDcnPacket(uint8 ch, uint8* data, uint16 len) {};
    /*
     * for protected
     */
    virtual void setAlarm(uint8 remote, uint8 local) {};
    virtual void protectFSMStart(void);

    /*
     * for loop
     */
    virtual void setPortLoopOut(uint8 ch, uint8 loop);
    virtual void setPortLoopIn(uint8 ch, uint8 loop);


    /**********for led*************/
    virtual void turnOnLedWork(uint8 sn, bool on);
    virtual void turnOnLedAlm(uint8 sn, bool on);
    void turnOnLedMaj(bool on);
    void turnOnLedMin(bool on);
    void turnOnledWorking(bool on);


    void sabitInterruptEnable(bool en);
    void resetRemote(uint8 port);
private:
    static const uint16 LED = 0x2fff; // bit0 MAJ; bit1 MIN
                                      // bit4~7 WORK1~4
                                      // bit8~12 ALM1~4
                                      // bit15 work


    static const uint16 VER = 0x000f;
    std::string ChipVerInfo;
    virtual std::string GetChipVerInfo(const std::string, const uint16);


    static const uint16 REG_VER_NUM       = 0x2020;
    static const uint16 REG_64K_CROSS_BASE= 0x8000;
                                                    //
    static const uint16 REG_E1_ALM_BASE   = 0x8410; //bit2 1 LOMF; bit3 1 RDI; bit4 0 LOF
    static const uint16 REG_E1_LOS        = 0x8460;
    static const uint16 REG_E1_AIS        = 0x8461;

    static const uint16 REG_LOOP_INNER      = 0x8465;
    static const uint16 REG_LOOP_OUTER      = 0x8466;
    static const uint16 REG_REMOTE_RESET    = 0x846c;
    static const uint16 REG_PCM_CLOCK_SEL = 0x8800;

    static const uint16 REG_CLOCK_SEL     = 0x8c03; //bit0~1 19.44M sel;
                                                    //bit14~15 2M sel; bit12~13 2Mbit(0)/Hz(1)
    static const uint16 REG_ClOCK_CTRL    = 0x8c04; //bit 4 in_sel, bit 15 tclr
                                                    //bit 1 modesel1, bit 0 modesel0
    static const uint16 REG_MSPI_ADDR    = 0x8c05;  //bit15 done(1)
                                                    //bit7 Read(1) Write(0)
                                                    //bit6~0(addr)
    static const uint16 REG_MSPI_DATA    = 0x8c06;  //bit15~8 dataRD, bit7~0 dataWR

    static const uint16 REG_RESET_CP1121A = 0x8c10;
    static const uint16 REG_PROTECT_XC    = 0x8c11; //bit15/14 slot0/1 Alarm(1)
    static const uint16 REG_RESET_ZL30122 = 0x8c12;

    static const uint16 REG_DCC_A_SEL   = 0x8C01;
    static const uint16 REG_DCC_B_SEL   = 0x8C02;

    static const uint16 REG_Alarm_STA   = 0x8d00; //bit15~8 remote; bit7~0 local
    static const uint16 REG_FSM_Start   = 0x8d01; //bit0 start(1)

    static const uint16 REG_DCC_A_TS    = 0x9001; //bit1 send done, bit0 send start
    static const uint16 REG_DCC_B_TS    = 0x9003; //bit1 send done, bit0 send start
    static const uint16 REG_DCC_A_RS    = 0x9007; //bit1 rcv ready, bit0 rcv done
    static const uint16 REG_DCC_B_RS    = 0x900b; //bit1 rcv ready, bit0 rcv done
    static const uint16 REG_DCN_A_TS    = 0x9101; //bit1 send done, bit0 send start
    static const uint16 REG_DCN_B_TS    = 0x9103; //bit1 send done, bit0 send start
    static const uint16 REG_DCN_A_RS    = 0x9107; //bit1 rcv ready, bit0 rcv done
    static const uint16 REG_DCN_B_RS    = 0x910b; //bit1 rcv ready, bit0 rcv done

    static const uint16 REG_DCC_A_T_LEN = 0xA000;
    static const uint16 REG_DCC_A_T_BUF = 0xA002;
    static const uint16 REG_DCC_B_T_LEN = 0xA400;
    static const uint16 REG_DCC_B_T_BUF = 0xA402;

    static const uint16 REG_DCC_A_R_LEN = 0xA800;
    static const uint16 REG_DCC_A_R_BUF = 0xA802;
    static const uint16 REG_DCC_B_R_LEN = 0xAC00;
    static const uint16 REG_DCC_B_R_BUF = 0xAC02;

    static const uint16 REG_DCN_A_T_LEN = 0xB000;
    static const uint16 REG_DCN_A_T_BUF = 0xB002;
    static const uint16 REG_DCN_B_T_LEN = 0xB400;
    static const uint16 REG_DCN_B_T_BUF = 0xB402;

    static const uint16 REG_DCN_A_R_LEN = 0xB800;
    static const uint16 REG_DCN_A_R_BUF = 0xB802;
    static const uint16 REG_DCN_B_R_LEN = 0xBC00;
    static const uint16 REG_DCN_B_R_BUF = 0xBC02;

    static const uint16 REG_SABIT_R_STA = 0x8403; //bit0 rcv ready
    static const uint16 REG_SABIT_R_CH  = 0x8404; //RCV channal sn
    static const uint16 REG_SABIT_R_LEN = 0x8405; //RCV len
    static const uint16 REG_SABIT_R_BUF = 0x8600; //RCV Data
    static const uint16 REG_SABIT_R_OVER= 0x840f; //RCV Over

    static const uint16 REG_SABIT_T_STA = 0x8400;
    static const uint16 REG_SABIT_T_BUF = 0x8500; //SND Data
    static const uint16 REG_SABIT_T_CH  = 0x8401; //SND channal sn
    static const uint16 REG_SABIT_T_LEN = 0x8402; //SND len
    static const uint16 REG_SABIT_T_OVER= 0x840c; //SND OVER 0x46 fix
    static const uint16 REG_SABIT_T_BROAD = 0x840d; //bit7 1
    static const uint16 REG_SABIT_T_CH_STA= 0x846a;


    static const uint16 REG_OPT_DISABLE = 0x2006;
    static const uint16 REG_VER_CPLD_GENERALLOGIC_XY   = 0x0010;
    static const uint16 REG_VER_CPLD_GENERALLOGIC_Z   = 0x0011;
    static const uint16 REG_VER_CPLD_UOPTLOGIC   = 0x2010;
    static const uint16 REG_VER_FPGA_PCMLOGIC    = 0x8C0F;
    static const uint16 REG_VER_FPGA_SDHLOGIC    = 0xC010;

    static const uint16 REG_INTRR_EN = 0x2040;
};

#endif /* CHIPEMUXLOGIC_H_ */
