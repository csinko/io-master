#include "uart.h"
#include "stm32h7xx_hal.h"

UART_HandleTypeDef  hUART = {0};

IOM_ERROR InitUART(void) {
    hUART.Instance          = USART1;
    hUART.Init.BaudRate     = 115200;
    hUART.Init.WordLength   = UART_WORDLENGTH_8B;
    hUART.Init.StopBits     = UART_STOPBITS_1;
    hUART.Init.Parity       = UART_PARITY_NONE;
    hUART.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    hUART.Init.Mode         = UART_MODE_TX_RX;
    hUART.Init.OverSampling = UART_OVERSAMPLING_16;
    hUART.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if(HAL_UART_DeInit(&hUART) != HAL_OK)
    {
        return IOM_ERROR_INVALID; //TODO replace with better error
    }  
    if(HAL_UART_Init(&hUART) != HAL_OK)
    {
        return IOM_ERROR_INVALID; //TODO replace with better error
    }
  return IOM_OK;
}

IOM_ERROR UARTSendString(const char* string) {
    uint16_t size = 0;
    while (string[size] != '\0') size++;
    if (HAL_UART_Transmit(&hUART, (uint8_t*)string, size, 5000) != HAL_OK) {
        return IOM_ERROR_INVALID; //TODO replace with better error
    }
    return IOM_OK;
}