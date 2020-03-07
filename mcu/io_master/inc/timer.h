#ifndef __IOM_TIMER_H
#define __IOM_TIMER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"
#include "stm32h7xx_hal.h"

TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim15;

IOM_ERROR InitTimers(void);

IOM_ERROR StartTimer(uint8_t pinNum);
IOM_ERROR StopTimer(uint8_t pinNum);

IOM_ERROR StartDMATimer();
IOM_ERROR StopDMATimer();

#ifdef __cplusplus
}
#endif
#endif