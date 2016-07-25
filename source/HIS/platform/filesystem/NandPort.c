/*
 * NandPort.c
 *
 *  Created on: 2013-9-27
 *      Author: Administrator
 */
 /*
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <File_Config.h>
#include "bsp_nand.h"
#include "os.h"

OS_MUT NandMut;
/*-----------------------------------------------------------------------------
 *      Initialise NAND flash driver
 *
 *  *cfg = Pointer to configuration structure
 *
 *  Return: RTV_NOERR             - NAND Flash Initialisation successful
 *          ERR_NAND_HW_TOUT      - NAND Flash Reset Command failed
 *          ERR_NAND_UNSUPPORTED  - Page size invalid
 *----------------------------------------------------------------------------*/
static U32 Init (NAND_DRV_CFG *cfg) {
    U32 pgSz = cfg->PageSize;
#ifdef EXT_DBG
    printf("\n >>>Nand Init() start\n");
#endif

    /* Setup OneNAND Page Layout on K9F2G08U0C */
    cfg->PgLay->Pos_LSN  =    2;
    cfg->PgLay->Pos_COR  =    1;
    cfg->PgLay->Pos_BBM  =    0;
    cfg->PgLay->Pos_ECC  =    8;
    cfg->PgLay->SectInc  =  512;
    cfg->PgLay->SpareOfs = 2048;
    cfg->PgLay->SpareInc =   16;

    switch (pgSz) {
      case 2112:
        break;
      default:
        return ERR_NAND_UNSUPPORTED;
    }

    if( bsp_nand_init() < 0 ) {
        return ERR_FTL_FATAL;
    }
    os_mut_init(NandMut);
#ifdef EXT_DBG
    printf("\n <<<Nand Init() end\n");
#endif
    return RTV_NOERR;
}

/*-----------------------------------------------------------------------------
 *      Uninitialise NAND flash driver
 *  *cfg = Pointer to configuration structure
 *
 *  Return: RTV_NOERR         - UnInit successful
 *----------------------------------------------------------------------------*/
static U32 UnInit(NAND_DRV_CFG *cfg) {
    return RTV_NOERR;
}



/*-----------------------------------------------------------------------------
 *      Erase block
 *  row  = Block address
 *  *cfg = Pointer to configuration structure
 *
 *  Return: RTV_NOERR         - Block erase successful
 *          ERR_NAND_ERASE    - Block erase failed
 *          ERR_NAND_HW_TOUT  - Hardware transfer timeout
 *----------------------------------------------------------------------------*/
static U32 BlockErase(U32 row, NAND_DRV_CFG *cfg) {
//    U32 blockindex = row / cfg->NumPages;
    os_mut_wait(NandMut, 0xffff);
#ifdef EXT_DBG
    printf("\n >>>BlockErase(row:%d) start\n", row);
#endif
    if( bsp_nand_block_erase(row) < 0 ) {
        os_mut_release(NandMut);
        return ERR_NAND_ERASE;
    }
    os_mut_release(NandMut);
#ifdef EXT_DBG
    printf("\n <<<BlockErase(row:%d) end\n", row);
#endif
    return RTV_NOERR;
}

/*-----------------------------------------------------------------------------
 *      Read page
 *  row  = Page address
 *  *buf = Pointer to data buffer
 *  *cfg = Pointer to configuration structure
 *
 *  Return: RTV_NOERR         - Page read successful
 *          ERR_NAND_HW_TOUT  - Hardware transfer timeout
 *          ERR_ECC_COR       - ECC corrected the data within page
 *          ERR_ECC_UNCOR     - ECC was not able to correct the data
 *----------------------------------------------------------------------------*/
static U32 PageRead(U32 row, U8 *buf, NAND_DRV_CFG *cfg) {
    os_mut_wait(NandMut, 0xffff);
#ifdef EXT_DBG
    printf("\n >>>PageRead(row:%d) start\n", row);
#endif
    if( bsp_nand_read_page(row, buf, cfg->PageSize) < 0 ) {
        os_mut_release(NandMut);
        return ERR_ECC_UNCOR;
    }
    os_mut_release(NandMut);
#ifdef EXT_DBG
    printf("\n <<<PageRead(row:%d) end\n", row);
#endif
    return RTV_NOERR;
}


/*-----------------------------------------------------------------------------
 *      Write page
 *  row  = Page address
 *  *buf = Pointer to data buffer
 *  *cfg = Pointer to configuration structure
 *
 *  Return: RTV_NOERR         - Page write successful
 *          ERR_NAND_PROG     - Page write failed
 *          ERR_NAND_HW_TOUT  - Hardware transfer timeout
 *----------------------------------------------------------------------------*/
static U32 PageWrite(U32 row, U8 *buf, NAND_DRV_CFG *cfg) {
    os_mut_wait(NandMut, 0xffff);
#ifdef EXT_DBG
    printf("\n >>>PageWrite(row:%d) start\n", row);
#endif
    if( bsp_nand_write_page(row, buf, cfg->PageSize) < 0 ) {
       os_mut_release(NandMut);
       return ERR_NAND_PROG;
    }
    os_mut_release(NandMut);
#ifdef EXT_DBG
    printf("\n <<<PageWrite(row:%d) end\n", row);
#endif
    return RTV_NOERR;
}


/*----------------------------------------------------------------------------
  NAND Device Driver Control Block
 *----------------------------------------------------------------------------*/
const NAND_DRV nand1_drv = {
    Init,
    UnInit,
    PageRead,
    PageWrite,
    BlockErase,
};
