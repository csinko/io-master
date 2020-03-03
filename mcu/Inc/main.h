/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"
#include "core.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void Error_Handler(void);

void writeAllExtDac(float Vout);
void writeExtDac(uint8_t channel, float Vout);

#ifdef __cplusplus
}
#endif
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
