/*
 * bsp_nand.h
 *
 *  Created on: 2013-9-27
 *      Author: Administrator
 */

#ifndef BSP_NAND_H_
#define BSP_NAND_H_

#if defined (__cplusplus)
extern "C"
{
#endif

#include "EZ_types.h"	

int bsp_nand_init(void);
int bsp_nand_block_erase(uint32 blockindex);
int bsp_nand_read_page(uint32 pageAddr, uint8* buf, uint32 nums);
int bsp_nand_write_page(uint32 pageAddr, uint8* buf, uint32 nums);
//int bsp_nand_chip_erase(void);
//int bsp_nand_chip_check_bad(void);

#if defined (__cplusplus)
}
#endif
#endif /* BSP_NAND_H_ */
