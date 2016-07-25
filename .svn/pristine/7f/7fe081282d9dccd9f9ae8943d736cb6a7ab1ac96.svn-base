/*
 * bsp_nand.c
 *
 *  Created on: 2013-9-27
 *      Author: Administrator
 */

#include <stdio.h>                    /* standard I/O .h-file                */
#include "bsp_nand.h"
#include "slc_nand.h"
//#include "Mid_NandFlash.h"


#define FILE_SYSTEM_START_BLOCK  (1024)
#define Page_offs	(FILE_SYSTEM_START_BLOCK * 64)

/*
 * bsp_nand_init
 * ��ʼ��
 */
int bsp_nand_init(void) {
    __SLCNANDInit();
//    InitNandFlash();
    return 1;
}
int bsp_nand_block_erase(uint32 blockindex) {
    __EraseBlock(blockindex+Page_offs);
//    if( flash_erase_block(blockindex+FILE_SYSTEM_START_BLOCK) == TRUE )
        return 1;
//    return -1;
}
int bsp_nand_read_page(uint32 pageAddr, uint8* buf, uint32 nums) {
    if( __ReadByte(0, pageAddr+Page_offs, nums, buf) == TRUE ) {
        return 1;
    }
    return -1;
//    if( flash_read_sector(pageAddr+Page_offs, buf, buf+2048) == TRUE ) {
//        return 1;
//    }
//    return -1;
}
int bsp_nand_write_page(uint32 pageAddr, uint8* buf, uint32 nums) {
    if( __ProgramByte(0, pageAddr+Page_offs, nums, buf) == TRUE ) {
        return 1;
    }
    return -1;
//    if( flash_write_sector(pageAddr+Page_offs, buf, buf+2048) == TRUE ) {
//        return 1;
//    }
//    return -1;
}

//int bsp_nand_chip_erase(void) {
//    int i = 0;
//
//    for( i = 0; i < 2048; i++ ) {
//        if( slcnand_erase_block(nand, i) < 0 ) {
//            printf ("\nBad block at: %d", i);
//            slcnand_mark_block_bad(nand, i);
//
//        }
//    }
//    return 0;
//}
//
//int bsp_nand_chip_check_bad(void) {
//    int i = 0;
//
//    for( i = 0; i < 2048; i++ ) {
//        if( slcnand_is_block_bad(nand, i) ) {
//            printf ("\nOld Bad block at: %d", i);
//        }
//    }
//   return 0;
//}
