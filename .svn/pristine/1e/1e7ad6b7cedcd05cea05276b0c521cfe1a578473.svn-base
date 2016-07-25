/*
 * Uart2Fan.c
 *
 *  Created on: 2015��2��26��
 *      Author: Administrator
 */
#include "Uart1.h"
#include "os.h"
#include "lpc32xx_hsuart_driver.h"
#include "lpc32xx_hsuart.h"
#include "lpc_string.h"
#include "lpc32xx_intc_driver.h"
#include "lpc32xx_uart.h"


//OS_MUT mut_hsuart_snd;
//OS_MUT mut_hsuart_rcv;
//OS_SEM sem_hsuart_rcv;
/* HSUART device handles */
static INT_32 hsuartdev;
static UNS_8 txbuff [512], rxbuff [512];
volatile static int txsize, rxsize;
static int txfill, rxget, txget, rxfill;

extern void uart1_int_handler(void);

INTR_HANDLER void uart1_interrupt_handler(void) {
	uart1_int_handler();
}
/***********************************************************************
 *
 * Function: huart_dat_send_cb
 *
 * Purpose: HS UART transmit data callback
 *
 * Processing:
 *     Move data from the ring buffer to the driver.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: This function is called in interrupt context.
 *
 **********************************************************************/
void huart_dat_send_cb(void)
{
  INT_32 bwrite, tosend = 512 - txget;
  HSUART_CFG_T *phsuart = (HSUART_CFG_T *) hsuartdev;

  if (tosend > txsize)
  {
    tosend = txsize;
  }

  if (tosend == 0)
  {
    phsuart->regptr->ctrl &= ~HSU_TX_INT_EN;
  }
  else
  {
    phsuart->regptr->ctrl |= HSU_TX_INT_EN;
  }

  /* Write data */
  bwrite = hsuart_write(hsuartdev, &txbuff[txget], tosend);
  txsize = txsize - bwrite;
  txget = txget + bwrite;
  if (txget >= 512)
  {
    txget = 0;
  }

}

/***********************************************************************
 *
 * Function: huart_dat_recv_cb
 *
 * Purpose: HS UART receive data callback
 *
 * Processing:
 *     Read data from the driver into the RX ring buffer.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes:
 *     Ring buffer overflow is not accounted for in this application.
 *     This function is called in interrupt context.
 *
 **********************************************************************/
void huart_dat_recv_cb(void)
{
  INT_32 bread, toreadmax = 512 - rxfill;

  /* Read data */
  bread = hsuart_read(hsuartdev, &rxbuff[rxfill], toreadmax);
  rxsize = rxsize + bread;
  rxfill = rxfill + bread;
  if (rxfill >= 512)
  {
    rxfill = 0;
  }
}

/***********************************************************************
 *
 * Function: huart_dat_out
 *
 * Purpose: Send some data on the terminal interface
 *
 * Processing:
 *     Place data into the TX ring buffer and start HS UART transmission.
 *
 * Parameters:
 *     dat   : Data to send
 *     bytes : Number of bytes to send
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: Will block until all bytes are sent.
 *
 **********************************************************************/
void huart_dat_out(UNS_8 *dat, int bytes)
{
  while (bytes > 0)
  {
    while ((bytes > 0) && (txsize < 512))
    {
      txbuff[txfill] = *dat;
      txfill++;
      if (txfill >= 512)
      {
        txfill = 0;
      }
      dat++;
      bytes--;
      int_disable(IRQ_UART_IIR1);
      txsize++;
      int_enable(IRQ_UART_IIR1);
    }

    int_disable(IRQ_UART_IIR1);
    huart_dat_send_cb();
    int_enable(IRQ_UART_IIR1);
  }
}

/***********************************************************************
 *
 * Function: huart_dat_in
 *
 * Purpose: Read some data from the terminal interface
 *
 * Processing:
 *     Move data from the ring buffer to the passed buffer.
 *
 * Parameters:
 *     buff  : Where to place the data
 *     bytes : Number of bytes to read
 *
 * Outputs: None
 *
 * Returns: Number of bytes actually read
 *
 * Notes: None
 *
 **********************************************************************/
int huart_dat_in(UNS_8 *buff, int bytes)
{
  int bread = 0;

  while ((bytes > 0) && (rxsize > 0))
  {
    *buff = rxbuff[rxget];
    buff++;
    rxget++;
    if (rxget >= 512)
    {
      rxget = 0;
    }
    bytes--;
    bread++;
    int_disable(IRQ_UART_IIR1);
    rxsize--;
    int_enable(IRQ_UART_IIR1);
  }

  return bread;
}

/***********************************************************************
 *
 * Function: Uart2Fan.cInit
 *
 * Purpose: Initialize Uart2Fan I/O interface
 *
 * Processing:
 *     Use the UART driver to open and initialize the serial port
 *     session.
 *
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void huartInit(void) {
    HSUART_CBS_T cbs;
    HSUART_CONTROL_T hsucntl[3];
    hsucntl[0].baud_rate = 115200;
    hsucntl[0].cts_en = FALSE;
    hsucntl[0].rts_en = FALSE;

    /* Set UART3 to not use modem control pins */
    UARTCNTL->ctrl &= ~UART_U3_MD_CTRL_EN;

    hsuartdev = hsuart_open((void *) UART1, (INT_32) &hsucntl[0]);
    if (hsuartdev != 0) {
        /* Setup RX and TX callbacks */
        cbs.rxcb = huart_dat_recv_cb;
        cbs.txcb = huart_dat_send_cb;
        cbs.rxerrcb = NULL;
        hsuart_ioctl(hsuartdev, HSUART_INSTALL_CBS, (INT_32) &cbs);

        int_enable(IRQ_UART_IIR1);

        /* Initialize TX and RX ring buffers */
        txfill = txget = rxfill = rxget = txsize = rxsize = 0;

    }
}
