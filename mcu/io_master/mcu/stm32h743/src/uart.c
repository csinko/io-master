#include "uart.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx.h"

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