#ifndef __IOM_UART_H
#define __IOM_UART_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"
#include "stm32h7xx_hal.h"

UART_HandleTypeDef hUART;

IOM_ERROR InitUART(void);

IOM_ERROR UARTSendString(const char* string);

#ifdef __cplusplus
}
#endif
#endif