#include "Ethernet.h"
#include "EZ_types.h"


extern void Write_PHY (uint16 phyadd,int PhyReg, int Value);
extern uint16 Read_PHY ( uint16 phyadd ,unsigned char PhyReg);

int32 rtl8306_setAsicPhyReg(uint32 phyad, uint32 regad, uint32 npage, uint32 value) {
	uint32 rdata; 

	if ((phyad >= 7) || (regad >= 32) ||
		(npage >= 4))	
		return 0;
	/* Select PHY Register Page through configuring PHY 0 Register 16 [bit1 bit15] */
	value = value & 0xFFFF;
	rdata = Read_PHY(0, 16); 
	switch (npage) {
	case 0: //RTL8306_REGPAGE0:
		Write_PHY(0, 16, (rdata & 0x7FFF) | 0x0002);
		break;
	case 1: //RTL8306_REGPAGE1:
		Write_PHY(0, 16, rdata | 0x8002 );
		break;
	case 2: //RTL8306_REGPAGE2:
		Write_PHY(0, 16, rdata & 0x7FFD);
		break;
	case 3: //RTL8306_REGPAGE3:
		Write_PHY(0, 16, (rdata & 0xFFFD) | 0x8000);
		break;
	default:
		return 0;
	}
	
	Write_PHY(phyad, regad, value);
	return 1;
}


int32 rtl8306_getAsicPhyReg(uint32 phyad, uint32 regad, uint32 npage, uint32 *pvalue) {
	uint32 rdata;

	if ((phyad >= 7) || (regad >= 32) ||
		(npage >= 4))	
		return 0;

	/* Select PHY Register Page through configuring PHY 0 Register 16 [bit1 bit15] */
	rdata = Read_PHY(0, 16); 
	switch (npage) {
	case 0: //RTL8306_REGPAGE0:
		Write_PHY(0, 16, (rdata & 0x7FFF) | 0x0002);
		break;
	case 1: //RTL8306_REGPAGE1:
		Write_PHY(0, 16, rdata | 0x8002 );
		break;
	case 2: //RTL8306_REGPAGE2:
		Write_PHY(0, 16, rdata & 0x7FFD);
		break;
	case 3: //RTL8306_REGPAGE3:
		Write_PHY(0, 16, (rdata & 0xFFFD) | 0x8000);
		break;
	default:
		return 0;
	}

	*pvalue = Read_PHY(phyad, regad);
	*pvalue = *pvalue & 0xFFFF;
	return 1;
	
}






int32 rtl8306_setAsicPhyRegBit(uint32 phyad, uint32 regad, uint32 bit, uint32 npage,  uint32 value) {
	uint32 rdata;
	if ((phyad >= 7) || (regad >= 32) || 
		(npage >= 4) || (bit > 15) || (value >1))
		return 0;
	rtl8306_getAsicPhyReg(phyad, regad,  npage, &rdata);
	if (value) 
		rtl8306_setAsicPhyReg(phyad, regad, npage, rdata | (1 << bit));
	else
		rtl8306_setAsicPhyReg(phyad, regad, npage, rdata & (~(1 << bit)));
	return 1;
}


int32 rtl8306_getAsicPhyRegBit(uint32 phyad, uint32 regad, uint32 bit, uint32 npage,  uint32 * pvalue) {
	uint32 rdata;

	if ((phyad >= 7) || (regad >= 32) ||
		(npage >= 4) || (bit > 15) || (pvalue == NULL))
		return 0;
	rtl8306_getAsicPhyReg(phyad, regad, npage, &rdata);
	if (rdata & (1 << bit))
		*pvalue =1;
	else 
		*pvalue =0;
		
	return 1;
}




uint32 SetRTL8306StaticLUTUnicastEntry(uint8* ucMacAddr, uint32 uiPort)
{
    uint32 age = 0x2;
    uint32 isAuth = 1;
    uint32 isStatic = 1;
    uint32 regValue;
    uint32 index;
    uint32 entry = 0;
    uint32 pollcnt;
    uint32 bitValue;
    entry = ((ucMacAddr[4] & 0x7) << 6) |((ucMacAddr[5] & 0xFC) >>2);
    if( (ucMacAddr == NULL) || (uiPort > 5) ){
        return 0;
    }
    /*For unicast entry, MAC[47] is 0*/
    if(ucMacAddr[0] & 0x01){
        return 0;
    }
    /*Enable lookup table access*/
	rtl8306_setAsicPhyRegBit(0, 16, 13, 0, 1);
	
	regValue = ((isAuth == 1 ? 1:0 ) << 7) | ((isStatic == 1 ? 1:0) << 6) | (age << 4) | uiPort;
	rtl8306_setAsicPhyReg(4, 17, 0, regValue & 0xFF);
	/*write Data[47:32]*/
	rtl8306_setAsicPhyReg(4, 18, 0, ucMacAddr[5] << 8 | ucMacAddr [4]);
	/*wrtie Data[31:16]*/
	rtl8306_setAsicPhyReg(4, 19, 0, ucMacAddr[3] << 8 | ucMacAddr [2]);
	/*wrtie Data[15:0]*/	
	rtl8306_setAsicPhyReg(4, 20, 0, ucMacAddr[1] << 8 | ucMacAddr [0]);	
	/*LUT index : MAC[13:15] + MAC[0:5]*/
	index = ((ucMacAddr[4] & 0x7) << 6) | ((ucMacAddr[5] & 0xFC) >> 2);
	/*Write Command, 2-bit indicating four-way lies in highest bit of Entry_Addr[10:0]*/
    
	regValue = (entry << 13) | (index << 4) | 0x2;	
	rtl8306_setAsicPhyReg(4, 16, 0, regValue);
	/*Waiting for write command done and prevent polling dead loop*/
	for (pollcnt = 0; pollcnt < 100; pollcnt ++) {
		rtl8306_getAsicPhyRegBit(4, 16, 1, 0, &bitValue);
		if (!bitValue)
			break;
	}
	if (pollcnt == 100)
		return 0;
	/*Disable lookup table access*/
	rtl8306_setAsicPhyRegBit(0, 16, 13, 0, 0);
	return 1;
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

