/**
  ******************************************************************************
  * File Name          : stm32h7xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include "main.h"
#include "mcu_conf.h"
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
  if(htim_pwm->Instance==TIM8)
  {
    __HAL_RCC_TIM8_CLK_ENABLE();
  }

}

void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hdac->Instance==DAC1)
  {
    __HAL_RCC_DAC12_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = Vout_SETPOINT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(Vout_SETPOINT_GPIO_Port, &GPIO_InitStruct);
  }

}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
  if(hdac->Instance==DAC1)
  {
    __HAL_RCC_DAC12_CLK_DISABLE();
    HAL_GPIO_DeInit(Vout_SETPOINT_GPIO_Port, Vout_SETPOINT_Pin);
  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim->Instance==TIM8)
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  }

}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
  if(htim_pwm->Instance==TIM8)
  {
    __HAL_RCC_TIM8_CLK_DISABLE();
  }

}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
