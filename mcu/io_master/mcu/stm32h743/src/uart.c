#include "uart.h"
#include "stm32h7xx_hal.h"
#include "mcu_conf.h"
#include <string.h>
#include <stdlib.h>
#include "command.h"

UART_HandleTypeDef  hUART = {0};

IOM_Output_Buffer uart_tx_buf_queue[UART_TX_BUF_QUEUE_MAX_SIZE] = {0};


uint8_t uart_tx_buf_queue_in_ptr = 0;
uint8_t uart_tx_buf_queue_out_ptr = 0;
uint8_t uart_tx_buf_queue_size = 0;

IOM_Output_Buffer uart_sent_buf = {0};

IOM_Queue_State uart_tx_state = IOM_QS_RDY;

IOM_Output_Buffer uart_rx_buf_queue[UART_RX_BUF_QUEUE_MAX_SIZE] = {0};

uint8_t uart_rx_buf_queue_in_ptr = 0;
uint8_t uart_rx_buf_queue_out_ptr = 0;
uint8_t uart_rx_buf_queue_size = 0;


IOM_ERROR InitUART(void) {
    __HAL_RCC_USART1_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    hUART.Instance          = USART1;
    hUART.Init.BaudRate     = 115200;
    hUART.Init.WordLength   = UART_WORDLENGTH_8B;
    hUART.Init.StopBits     = UART_STOPBITS_1;
    hUART.Init.Parity       = UART_PARITY_NONE;
    hUART.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    hUART.Init.Mode         = UART_MODE_TX_RX;
    hUART.Init.OverSampling = UART_OVERSAMPLING_16;
    hUART.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    HAL_StatusTypeDef ret = HAL_UART_DeInit(&hUART);
    if (ret != HAL_OK)
    {
        return IOM_ERROR_INVALID; //TODO replace with better error
    }  
    ret = HAL_UART_Init(&hUART);
    if (ret != HAL_OK)
    {
        return IOM_ERROR_INVALID; //TODO replace with better error
    }
  return IOM_OK;
}

IOM_ERROR UARTSendString(const char* string) {
    uint16_t size = 0;
    while (string[size] != '\0') size++;
    uint8_t* pData = malloc(size);
    memcpy(pData, string, size);
    return UARTQueueTXData(pData, size);
}

IOM_ERROR UARTQueueTXData(uint8_t* pData, size_t length) {
    if (uart_tx_buf_queue_size >= UART_TX_BUF_QUEUE_MAX_SIZE) {
        return IOM_ERROR_QUEUE_FULL;
    }
    //if the uart queue is empty and ready to send
    if (uart_tx_state == IOM_QS_RDY) {
        //send it directly
        uart_sent_buf.data = pData;
        uart_sent_buf.length = length;
        return UARTTXData();
    }
    uart_tx_buf_queue[uart_tx_buf_queue_in_ptr].data = pData;
    uart_tx_buf_queue[uart_tx_buf_queue_in_ptr].length = length;
    uart_tx_buf_queue_in_ptr = (uart_tx_buf_queue_in_ptr + 1) % UART_TX_BUF_QUEUE_MAX_SIZE;
    uart_tx_buf_queue_size++;
    return IOM_OK;
}

IOM_ERROR UARTDequeueTXData() {
    if (uart_tx_buf_queue_size == 0) {
        return IOM_ERROR_QUEUE_EMPTY;
    }
    if (uart_tx_state != IOM_QS_RDY) {
        return IOM_ERROR_BUFFER_FULL;
    }
    uart_sent_buf = uart_tx_buf_queue[uart_tx_buf_queue_out_ptr];
    uart_tx_buf_queue_out_ptr = (uart_tx_buf_queue_out_ptr + 1) % UART_TX_BUF_QUEUE_MAX_SIZE;
    uart_tx_buf_queue_size--;
    uart_tx_state = IOM_QS_RTS;
    return IOM_OK;
}

IOM_ERROR UARTTXData() {
    if (HAL_UART_Transmit_IT(&hUART, uart_sent_buf.data, uart_sent_buf.length) != HAL_OK) {
        return IOM_ERROR_INVALID; //TODO replace with better error
    }
    uart_tx_state = IOM_QS_BSY;
    return IOM_OK;
}

IOM_ERROR UARTQueueRXData(uint8_t* pData, size_t length) {
    if (uart_rx_buf_queue_size >= UART_RX_BUF_QUEUE_MAX_SIZE) {
        return IOM_ERROR_QUEUE_FULL;
    }

    uart_rx_buf_queue[uart_rx_buf_queue_in_ptr].data = pData;
    uart_rx_buf_queue[uart_rx_buf_queue_in_ptr].length = length;
    uart_rx_buf_queue_in_ptr = (uart_rx_buf_queue_in_ptr + 1) % UART_RX_BUF_QUEUE_MAX_SIZE;
    uart_rx_buf_queue_size++;
    if (HAL_UART_Receive_IT(&hUART, pData, length) != HAL_OK) {
        return IOM_ERROR_INVALID; //TODO replace with better error
    }
    return IOM_OK;
}


IOM_ERROR UARTDequeueRXData() {
    if (uart_rx_buf_queue_size == 0) {
        return IOM_ERROR_QUEUE_EMPTY;
    }
    ProcessCommand(uart_rx_buf_queue[uart_rx_buf_queue_out_ptr]);
    uart_sent_buf = uart_tx_buf_queue[uart_tx_buf_queue_out_ptr];
    uart_rx_buf_queue_out_ptr = (uart_rx_buf_queue_out_ptr + 1) % UART_RX_BUF_QUEUE_MAX_SIZE;
    uart_rx_buf_queue_size--;
    return IOM_OK;
}

///NVIC IRQ Functions

void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&hUART);
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    HAL_GPIO_TogglePin(STATUS_G_GPIO_Port, STATUS_G_Pin);
    free(uart_sent_buf.data);
    uart_tx_state = IOM_QS_RDY;
    if (uart_tx_buf_queue_size > 0) {
        UARTDequeueTXData();
    }
  
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    HAL_GPIO_TogglePin(STATUS_R_GPIO_Port, STATUS_R_Pin);
    UARTDequeueRXData();
}