/*
 * ChipRC6400.h
 *
 *  Created on: 2014-3-26
 *      Author: Administrator
 */

#ifndef CHIPRC6400_H_
#define CHIPRC6400_H_

#include "BaseChip.h"
#include "RC6400.h"

class RegisterAccess;
class CBaseSlot;

class ChipRC6400: public BaseChip {
public:
    ChipRC6400(CBaseSlot* slt, uint32 baseAddr);
    virtual ~ChipRC6400();

    virtual Chip_INIT_RESULT ChipInit(void);

    bool setEnable(int vcg, int en);
    bool setLcas(int vcg, int en);
    bool AddTu12ToVCGSimple(uint8 tsNum, uint8 vcgNum);
    bool DeleteTu12FromVCGSimple(uint8 tsNum);
    bool setSNCP(int tsNUm, int en);
    void RC6400_Pause_Config(U8 VCGNum,U8 flag);
    bool getGFPStatus(int vcg);
    void RC6400_TU12_Bus_Exp_Sel_Rx_Set(uint8 TsNum, uint8 flag);

private:
    RegisterAccess* ra;
    uint32 regBase;

    U8 read(U16 addr);
    void write(U16 addr , U8 data, U8 bits = 0xff);

    void RC6400_TU12_V5_Config_Tx_Set(U8 TsNum, U8 val);
    void RC6400_TU12_V5_Config_Rx_Set(U8 TsNum, U8 val);
    void RC6400_TU12_K4_Config_Tx_Set(U8 TsNum, U8 val);
    void RC6400_TU12_K4_Config_Rx_Set(U8 TsNum, U8 val);

    void RC6400_VC12_GRP_Sel_Rx_Set(U8 TsNum,U8 VCGNum);
    void RC6400_VC12_GRP_Sel_Tx_Set(U8 TsNum, U8 VCGNum);
    void RC6400_TU12_En_Rx_Set(U8 TsNum, U8 flag);
    void RC6400_TU12_En_Tx_Set(U8 TsNum, U8 flag);
    void RC6400_VC12_En_Rx_Set(U8 TsNum, U8 flag);
    void RC6400_VC12_En_Tx_Set(U8 TsNum, U8 flag);



    void RC6400_VCAT_En_Tx_Set(U8 VCGNum, U8 flag);
    void RC6400_VCAT_En_Rx_Set(U8 VCGNum, U8 flag);
    void RC6400_LCAS_En_Rx_Set(U8 VCGNum,U8 flag);
    void RC6400_LCAS_En_Tx_Set(U8 VCGNum,U8 flag);

    void RC6400_TU12_Bus_Sel_Mode_Rx_Set(U8 TsNum, U8 flag);
    bool RC6400_GFP_DeFrame_Syn_Status_Read(uint8 VCGNum);
};

#endif /* CHIPRC6400_H_ */
