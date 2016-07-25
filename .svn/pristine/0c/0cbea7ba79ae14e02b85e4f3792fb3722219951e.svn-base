/*
 * ChipRC6400.cpp
 *
 *  Created on: 2014-3-26
 *      Author: Administrator
 */

#include "ChipRC6400.h"
#include "RegisterAccess.h"
#include "CBaseSlot.h"

static const std::string chipName = "Chip8EOSLogic";

ChipRC6400::ChipRC6400(CBaseSlot* slt, uint32 baseAddr) : BaseChip(chipName) {
    // TODO Auto-generated constructor stub
    ra = slt->getRegisterAccess();
    regBase = baseAddr;
}

ChipRC6400::~ChipRC6400() {
    // TODO Auto-generated destructor stub
}


Chip_INIT_RESULT ChipRC6400::ChipInit(void) {
    for( int i = 0; i < 63; i++ ) {
        RC6400_TU12_V5_Config_Tx_Set(i, 0x0a);
        RC6400_TU12_V5_Config_Rx_Set(i, 0x05);
        RC6400_TU12_K4_Config_Tx_Set(i, 0x0d);
        RC6400_TU12_K4_Config_Rx_Set(i, 0x0d);
    }
    return succeed;
}


bool ChipRC6400::setEnable(int vcg, int en) {
    RC6400_VCAT_En_Tx_Set(vcg, en);
    RC6400_VCAT_En_Rx_Set(vcg, en);
    return true;
}

bool ChipRC6400::setLcas(int vcg, int en) {
    RC6400_LCAS_En_Rx_Set(vcg, en);
    RC6400_LCAS_En_Tx_Set(vcg, en);
	return true;
}


bool ChipRC6400::AddTu12ToVCGSimple(uint8 tsNum, uint8 vcgNum) {

    /* Set virtual connect group for vc12
     * NOTE: must call first
     */
    RC6400_VC12_GRP_Sel_Rx_Set(tsNum, vcgNum);
    RC6400_VC12_GRP_Sel_Tx_Set(tsNum, vcgNum);


    /* enable all mapping layer tu12
     * NOTE: must call second
     */
    RC6400_TU12_En_Rx_Set(tsNum, ENABLE);
    RC6400_TU12_En_Tx_Set(tsNum, ENABLE);

    /* enable VCAT layer vc12
     * NOTE: must call latest
     */
    RC6400_VC12_En_Rx_Set(tsNum, ENABLE);
    RC6400_VC12_En_Tx_Set(tsNum, ENABLE);

//  /* tu12 add enable */
    RC6400_TU12_En_Tx_Set(tsNum, ENABLE);

    return true;
}

bool ChipRC6400::DeleteTu12FromVCGSimple(uint8 tsNum) {

    /* disable VCAT layer vc12
     * NOTE: must call first
     */
    RC6400_VC12_En_Rx_Set(tsNum, DISABLE);
    RC6400_VC12_En_Tx_Set(tsNum, DISABLE);

    /* disable mapping layer tu12
     * NOTE: must call second
     */
    RC6400_TU12_En_Rx_Set(tsNum, DISABLE);
    RC6400_TU12_En_Tx_Set(tsNum, DISABLE);

    /* clear virtual connect group for vc12
     * NOTE: must call latest
     */
    RC6400_VC12_GRP_Sel_Rx_Set(tsNum, 0);
    RC6400_VC12_GRP_Sel_Tx_Set(tsNum, 0);

    /* tu12 add enable */
    RC6400_TU12_En_Tx_Set(tsNum, DISABLE);

    return true;
}

bool ChipRC6400::setSNCP(int tsNUm, int en) {
    uint8 mode = 0; // 0 is ˫����ѡ�� 1 is ������
    if( en == 0 ) {
        mode = 1;
    }
    RC6400_TU12_Bus_Sel_Mode_Rx_Set(tsNUm, mode);
	return true;
}



void ChipRC6400::RC6400_VCAT_En_Tx_Set(U8 VCGNum, U8 flag) {
    U8 tval;

    tval=read(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9));
    if(flag==VCAT_ENABLE)
    {
        tval|=cTVCAT;
    }
    else if(flag==VCAT_DISABLE)
    {
        tval&=~cTVCAT;
    }
    write(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9),tval);
}
void ChipRC6400::RC6400_VCAT_En_Rx_Set(U8 VCGNum, U8 flag) {
    U8 tval;

    tval=read(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9));
    if(flag==VCAT_ENABLE)
    {
        tval|=cRVCT;
    }
    else if(flag==VCAT_DISABLE)
    {
        tval&=~cRVCT;
    }
    write(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9),tval);

}

void ChipRC6400::RC6400_LCAS_En_Rx_Set(U8 VCGNum,U8 flag) {
    U8 tval;

    tval=read(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9));
    if(flag==LCAS_ENABLE)
    {
        tval|=cRLCAS;
    }
    else if(flag==LCAS_DISABLE)
    {
        tval&=~cRLCAS;
    }
    write(cGROUP_VCAT_RECV_CONFIG+(VCGNum<<9), tval);
}

void ChipRC6400::RC6400_LCAS_En_Tx_Set(U8 VCGNum,U8 flag) {
    U8 tval;

    tval=read(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9));
    if(flag==LCAS_ENABLE)
    {
        tval|=cTLCAS;
    }
    else if(flag==LCAS_DISABLE)
    {
        tval&=~cTLCAS;
    }
    write(cGROUP_VCAT_SEND_CONFIG+(VCGNum<<9),tval);
}

void ChipRC6400::RC6400_TU12_Bus_Sel_Mode_Rx_Set(U8 TsNum, U8 flag) {
    U8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
    flag=flag<<3;
    if(flag!=(tval&cTU12_RECV_SEL_MOD)) {
        write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),flag, cTU12_RECV_SEL_MOD);
    }
}

void ChipRC6400::RC6400_TU12_Bus_Exp_Sel_Rx_Set(uint8 TsNum, uint8 flag)
{
    uint8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
    if(flag==0)     /*A bus*/
    {
        tval&=~cTU12_RECV_SEL_CONFIG;
    }
    else if(flag==1)    /*B Bus*/
    {
        tval|=cTU12_RECV_SEL_CONFIG;
    }
    write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),tval, 0x02);
}

//true is sync
bool ChipRC6400::RC6400_GFP_DeFrame_Syn_Status_Read(uint8 VCGNum)
{
    uint8 tval;

    tval = read(sGROUP_GFP_DEFRAME_SYN + (VCGNum << 9));
    tval &= 0x01;
    if (tval) {
        return true;
    } else {
        return false;
    }
}


U8 ChipRC6400::read(U16 addr) {
    return ra->readReg(addr+regBase);
}
void ChipRC6400::write(U16 addr , U8 data, U8 bits) {
    U8 temp ;
    U8 tempData;

    addr += regBase;
    /* ��ͬ����д��д�����У�飬���10��  */
    for(temp = 0 ; temp < 10; temp++) {
        tempData = ra->readReg(addr);
        if(tempData != data)
        {
            /* unprotect regs */
            ra->writeReg(sGLOBAL_REGS_PROTECT + regBase, RC6400_REGS_FREE_CODE);

            /* write */
            ra->writeReg(addr, data, 1, bits);

            /* protect regs */
            ra->writeReg(sGLOBAL_REGS_PROTECT + regBase, RC6400_REGS_PROTECT_CODE);
       }
        else {
            break;
        }
    }
    return;
}

void ChipRC6400::RC6400_TU12_V5_Config_Tx_Set(U8 TsNum, U8 val) {
    U8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_V5_BYTE+(TsNum<<6));
    if(val!=tval)
        write(TU12_BASE_ADDR+cTU12_V5_BYTE+(TsNum<<6),val);
}

void ChipRC6400::RC6400_TU12_V5_Config_Rx_Set(U8 TsNum, U8 val) {
    U8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_RECV_TSL_EXP+(TsNum<<6));
    if(val!=tval)
        write(TU12_BASE_ADDR+cTU12_RECV_TSL_EXP+(TsNum<<6),val);
}

void ChipRC6400::RC6400_TU12_K4_Config_Tx_Set(U8 TsNum, U8 val) {
    U8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_SEND_K4_B1+(TsNum<<6));
    if(val!=tval)
    {
        write(TU12_BASE_ADDR+cTU12_SEND_K4_B1+(TsNum<<6), val);
    }
}

void ChipRC6400::RC6400_TU12_K4_Config_Rx_Set(U8 TsNum, U8 val)
{
    U8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_RECV_K4_B1_ESL_EXP+(TsNum<<6));
    if(val!=tval)
        write(TU12_BASE_ADDR+cTU12_RECV_K4_B1_ESL_EXP+(TsNum<<6), val);
}

void ChipRC6400::RC6400_VC12_GRP_Sel_Rx_Set(U8 TsNum,U8 VCGNum)
{
    U8 tval;

    tval=read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
    if(VCGNum!=(tval&cVC12_RECV_LOVCG))
    {
        tval&=0xF8;
        tval|=VCGNum;
        write(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6),tval);
    }
}

void ChipRC6400::RC6400_VC12_GRP_Sel_Tx_Set(U8 TsNum, U8 VCGNum) {
    U8 tval;

    tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
    if(VCGNum!=(tval&cVC12_SEND_LOVCG))
    {
        tval&=0xF8;
        tval|=VCGNum;
        write(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6),tval);
    }
}

void ChipRC6400::RC6400_TU12_En_Rx_Set(U8 TsNum, U8 flag) {
    U8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
    if(flag==1)
    {
        tval|=cTU12_RECV_DROPEN;
    }
    else if(flag==0)
    {
        tval&=~cTU12_RECV_DROPEN;
    }
    write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),tval);
}

void ChipRC6400::RC6400_TU12_En_Tx_Set(U8 TsNum, U8 flag) {
    U8 tval;

    tval=read(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6));
    if(flag==1)
    {
        tval|=cTU12_RECV_ADDEN;
    }
    else if(flag==0)
    {
        tval&=~cTU12_RECV_ADDEN;
    }
    write(TU12_BASE_ADDR+cTU12_RECV_ADD_DROP_BYTE+(TsNum<<6),tval);
}

void ChipRC6400::RC6400_VC12_En_Rx_Set(U8 TsNum, U8 flag) {
    U8 tval;

    tval= read(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6));
    if(flag==1)
    {
        tval|=cRLOUSE;
    }
    else if(flag==0)
    {
        tval&=~cRLOUSE;
    }
    write(VC12_BASE_ADDR+cVC12_RECV_CONFIG+(TsNum<<6),tval);
}

void ChipRC6400::RC6400_VC12_En_Tx_Set(U8 TsNum, U8 flag) {
    U8 tval;

    tval=read(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6));
    if(flag==1)
    {
        tval|=cTLOUSE;
    }
    else if(flag==0)
    {
        tval&=~cTLOUSE;
    }
    write(VC12_BASE_ADDR+cVC12_SEND_CONFIG+(TsNum<<6), tval);
}

void ChipRC6400::RC6400_Pause_Config(U8 VCGNum,U8 flag) {
    U8 tval=0;

    tval=read(0x01+(VCGNum<<9));
    tval &= ~1;
    tval |= flag;
    write(0x01+(VCGNum<<9), tval);
}

bool ChipRC6400::getGFPStatus(int vcg) {
    return RC6400_GFP_DeFrame_Syn_Status_Read(vcg);
}

