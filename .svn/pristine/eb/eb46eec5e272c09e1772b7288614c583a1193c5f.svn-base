/*****************************Copyright(c)****************************************************************
**                    Guangzhou ZHIYUAN electronics Co.,LTD.
**                                     
**                           http://www.embedtools.com
**
**------File Info-----------------------------------------------------------------------------------------
** File Name:            slc_nand.h
** Latest modified Date: 2008-11-10        
** Latest Version:       V1.0    
** Description:          nand flash 控制器接口函数头文件
**                       
**--------------------------------------------------------------------------------------------------------
** Created By:           Faqiang wang
** Created date:         2008-11-10    
** Version:              V1.0    
** Descriptions:         初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:          
** Modified date:        
** Version:             
** Description:          
**                      
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*********************************************************************************************************/

#ifndef __SLC_NAND_H
#define __SLC_NAND_H

#ifdef __cplusplus
extern "C" {
#endif   
	
#include "EZ_types.h"
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
	
#ifndef NULL
#define NULL ((void*)0)
#endif
   /*
    * NAND Flash Commands
    */
#define NAND_CMD_READ0         0x00                                     /*  Read mode (1) command       */
#define NAND_CMD_READ1         0x01                                     /*  Read mode (2) command       */
#define NAND_CMD_PAGEPROG      0x10                                     /*  Auto program command        */
#define NAND_CMD_READSTART     0x30                                     /*  Read start command          */
#define NAND_CMD_READ2         0x50                                     /*  Read mode (3) command       */
#define NAND_CMD_ERASE1ST      0x60                                     /*  Auto block erase 1-st command */
#define NAND_CMD_STATUS        0x70                                     /*  Status read (1) command     */
#define NAND_CMD_STATUS_MULTI  0x71                                     /*  Status read (2) command     */
#define NAND_CMD_SDIN          0x80                                     /*  Serial data input command   */
#define NAND_CMD_READID        0x90                                     /*  ID read (1) command         */
#define NAND_CMD_ERASE2ND      0xD0                                     /*  Auto block erase 2-nd command */
#define NAND_CMD_RESET         0xFF                                     /*  Reset command               */


/*********************************************************************************************************
** Function name:       __SLCNANDInit
** Descriptions:        __SLC NAND Flash 控制器初始化
** input parameters:    None
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern void __SLCNANDInit(void);

/*********************************************************************************************************
** Function name:       __ReadByte
** Descriptions:        读某一页的数据
** input parameters:    index    : 在页中的开始地址
                        pageaddr : 页地址
                        num      ：编程的字节数
                        *buff    : 存放数据指针
** output parameters:   None
** Returned value:      TRUE/FALSE
*********************************************************************************************************/
extern uint8 __ReadByte(uint32 index, uint32 pageaddr, uint32 num, uint8 *buff);

/*********************************************************************************************************
** Function name:       __EraseBlock
** Descriptions:        擦除某一个块
** input parameters:    pageaddr : 页地址
** output parameters:   None
** Returned value:      None
*********************************************************************************************************/
extern uint8 __EraseBlock(uint32 pageaddr);

/*********************************************************************************************************
** Function name:       __ProgramByte
** Descriptions:        读某一页的数据
** input parameters:    index    : 在页中的开始地址
                        pageaddr : 页地址
                        num      ：编程的字节数
                        *buff    : 存放数据指针
** output parameters:   None
** Returned value:      TRUE/FALSE
*********************************************************************************************************/
extern uint8 __ProgramByte(uint32 index, uint32 pageaddr, uint32 num, uint8 *buff);

/*********************************************************************************************************
** Function name:       __ReadID
** Descriptions:        读Nand ID
** input parameters:     *buff    : 存放数据指针
** output parameters:   None
** Returned value:      TRUE/FALSE
*********************************************************************************************************/
extern uint8 __ReadID(uint8 *buff);

#ifdef __cplusplus
    }
#endif 
	
#endif
