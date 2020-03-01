#ifndef __IOM_UART_H
#define __IOM_UART_H
#ifdef __cplusplus
extern "C" {
#endif

#include "mcu_conf.h"
#include "core.h"
#include "stm32h7xx_hal.h"

UART_HandleTypeDef hUART;

IOM_Output_Buffer uart_tx_buf_queue[UART_TX_BUF_QUEUE_MAX_SIZE];

uint8_t uart_tx_buf_queue_in_ptr;
uint8_t uart_tx_buf_queue_out_ptr;
uint8_t uart_tx_buf_queue_size;

IOM_Output_Buffer uart_sent_buf;

IOM_Queue_State uart_tx_state;

IOM_Output_Buffer uart_rx_buf_queue[UART_RX_BUF_QUEUE_MAX_SIZE];

uint8_t uart_rx_buf_queue_in_ptr;
uint8_t uart_rx_buf_queue_out_ptr;
uint8_t uart_rx_buf_queue_size;

IOM_ERROR InitUART(void);

IOM_ERROR UARTSendString(const char* string);

IOM_ERROR UARTQueueTXData(uint8_t* pData, size_t length);

IOM_ERROR UARTDequeueTXData();

IOM_ERROR UARTQueueRXData(uint8_t* pData, size_t length);

IOM_ERROR UARTDequeueRXData();

IOM_ERROR UARTTXData();

#ifdef __cplusplus
}
#endif
#endif