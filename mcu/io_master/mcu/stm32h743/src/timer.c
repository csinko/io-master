#include "timer.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"
#include "mcu_conf.h"

IOM_ERROR InitTimers(void) {
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  htim8.Instance = TIM8;
  TIM8->BDTR |= TIM_BDTR_MOE;
  htim8.Init.Prescaler = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 10;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }
  TIM8->BDTR |= TIM_BDTR_MOE;
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig); 


  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 10;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }
  sConfigOC.Pulse = 1;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }
  sConfigOC.Pulse = 1;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }

  TIM8->BDTR |= TIM_BDTR_MOE;

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig);

  //HAL_TIM_MspPostInit(&htim8); //TODO make this work
  TIM8->BDTR |= TIM_BDTR_MOE;

  if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1) != HAL_OK) {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }
  if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3) != HAL_OK) {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }
  if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4) != HAL_OK) {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }
    TIM8->BDTR |= TIM_BDTR_MOE;
    return IOM_OK;


}

IOM_ERROR EnableTimer(uint8_t pinNum) {
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};

switch(pinNum) {
  case 1:
    __HAL_RCC_TIM2_CLK_ENABLE();
    HAL_GPIO_DeInit(IO_1_CLK_GPIO_Port, IO_1_CLK_Pin);



    GPIO_InitStruct.Pin = IO_1_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(IO_1_CLK_GPIO_Port, &GPIO_InitStruct);


    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE; //TODO put a better error here
    }

    break;
  case 2:

    __HAL_RCC_TIM5_CLK_ENABLE();
    HAL_GPIO_DeInit(IO_2_CLK_GPIO_Port, IO_2_CLK_Pin);



    GPIO_InitStruct.Pin = IO_2_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(IO_2_CLK_GPIO_Port, &GPIO_InitStruct);


    htim2.Instance = TIM5;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    break;
    case 3:

    __HAL_RCC_TIM15_CLK_ENABLE();
    HAL_GPIO_DeInit(IO_3_CLK_GPIO_Port, IO_3_CLK_Pin);

    GPIO_InitStruct.Pin = IO_3_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_TIM15;
    HAL_GPIO_Init(IO_3_CLK_GPIO_Port, &GPIO_InitStruct);


    htim2.Instance = TIM15;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    if (HAL_TIM_PWM_Init(&htim15) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    break;
  case 4:
    __HAL_RCC_TIM3_CLK_ENABLE();
    HAL_GPIO_DeInit(IO_4_CLK_GPIO_Port, IO_4_CLK_Pin);

    GPIO_InitStruct.Pin = IO_4_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(IO_4_CLK_GPIO_Port, &GPIO_InitStruct);


    htim2.Instance = TIM3;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    break;
  default:
    return IOM_ERROR_INVALID;
}


return IOM_OK;
}

IOM_ERROR StartTimer(uint8_t pinNum) {

  switch(pinNum) {
    case 1:
      if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    case 2:
      if (HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    case 3:
      if (HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    case 4:
      if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    default:
      return IOM_ERROR_INVALID;
  }

  return IOM_OK;

}