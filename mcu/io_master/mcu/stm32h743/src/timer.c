#include "timer.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"
#include "mcu_conf.h"
#include "data.h"
#include "io_dma.h"

IOM_ERROR InitTimers(void) {
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM5_CLK_ENABLE();
    __HAL_RCC_TIM15_CLK_ENABLE();
    __HAL_RCC_TIM3_CLK_ENABLE();
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};

  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 32;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 10;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig); 


  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 9;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    return IOM_ERROR_INVALID; //TODO put a better error here
  }


  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig);


    HAL_NVIC_SetPriority(TIM8_CC_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(TIM8_CC_IRQn);

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 32;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 10;
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
    sConfigOC.Pulse = 5;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE; //TODO put a better error here
    }

    htim2.Instance = TIM5;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 100;
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
    sConfigOC.Pulse = 50;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
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

    return IOM_OK;


}

IOM_ERROR StartTimer(uint8_t pinNum) {

  switch(pinNum) {
    case 1:
      TIM2->CCER &= ~(TIM_CCER_CC1E);
      TIM2->CCER |= TIM_CCER_CC1E;
      TIM2->BDTR |= TIM_BDTR_MOE;
      TIM2->CR1 |= TIM_CR1_CEN;
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

IOM_ERROR StopTimer(uint8_t pinNum) {
  switch(pinNum) {
    case 1:
      if (HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    case 2:
      if (HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_2) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    case 3:
      if (HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_1) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    case 4:
      if (HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1) != HAL_OK) {
        return IOM_ERROR_INTERFACE;
      }
      break;
    default:
      return IOM_ERROR_INVALID;
  }
  return IOM_OK;
}

IOM_ERROR StartDMATimer() {
  TIM8->CCER &= ~(TIM_CCER_CC4E);
  TIM8->CCER |= TIM_CCER_CC4E;
  TIM8->BDTR |= TIM_BDTR_MOE;
  TIM8->DIER |= TIM_DIER_CC4IE;
  TIM8->CR1 |= TIM_CR1_CEN;
  return IOM_OK;
}

IOM_ERROR StopDMATimer() {
  if (HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_4) != HAL_OK) {
    return IOM_ERROR_INTERFACE;
  }
  return IOM_OK;
}

void TIM8_CC_IRQHandler() {
  //Disable flag
  TIM2->CCER |= TIM_CCER_CC1E;
  TIM8->SR &= ~(TIM_SR_CC4IF);
  if (bytesToSend == 1) {
    TIM2->CR1 &= ~(TIM_CR1_CEN);
    TIM8->CR1 &= ~(TIM_CR1_CEN);
    TIM2->CNT = 5;
    ResetDMA();
  } else {
  bytesToSend--;
  }
  //Disable timer
}
