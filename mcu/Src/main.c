/**
  ******************************************************************************
  * @file           : (main.c
  * @brief          : Main program body
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
#include "usb_device.h"
#include "iopin.h"
#include "data.h"
#include "core.h"
#include "clock.h"
#include "gpio.h"

#if defined( __ICCARM__ )
  #define DMA_BUFFER \
      _Pragma("location=\".dma_buffer\"")
#else
  #define DMA_BUFFER \
      __attribute__((section(".dma_buffer")))
#endif

DMA_HandleTypeDef hdma_dma_generator0;
uint8_t DMABusyFlag = 0;

DAC_HandleTypeDef hdac1;
static void MX_DAC1_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM8_Init(void);


int main(void)
{
  HAL_Init();

  InitSystemClock();
  InitGPIO();
  MX_DAC1_Init();
  HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1);
  HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);
  unsigned int num1 = 0, num2 = 2048;
  
  MX_USB_DEVICE_Init();
  MX_TIM8_Init();
  MX_DMA_Init();
  GPIOF->ODR = 0xFFFF;
  while (1)
  {

    //If the output queue is not empty and the DMA is not busy
    uint32_t counter = __HAL_DMA_GET_COUNTER(htim8.hdma[TIM_DMA_ID_CC4]);
    if ((output_buf_queue_size > 0) && (counter == 0)) {
      if (DMABusyFlag != 0) {
        ResetDMA();
        DMABusyFlag = 0;
      }
      DMABusyFlag = 1;
      SendOutputData();
      //Send the front of the output queue over DMA
    }
  }
}


void SystemClock_Config(void)
{
}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */
  /** DAC Initialization 
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config 
  */
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

}

static void MX_TIM8_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  htim8.Instance = TIM8;
  TIM8->BDTR |= TIM_BDTR_MOE;
  htim8.Init.Prescaler = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 1;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
TIM8->BDTR |= TIM_BDTR_MOE;
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig); 


  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 1;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 1;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
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

  HAL_TIM_MspPostInit(&htim8);
  TIM8->BDTR |= TIM_BDTR_MOE;

  if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4) != HAL_OK) {
    Error_Handler();
  }
TIM8->BDTR |= TIM_BDTR_MOE;
}

static void MX_DMA_Init(void) 
{
  __HAL_RCC_DMA2_CLK_ENABLE();

  hdma_dma_generator0.Instance = DMA2_Stream7;
  hdma_dma_generator0.Init.Request = DMA_REQUEST_TIM8_CH4;
  hdma_dma_generator0.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_dma_generator0.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_dma_generator0.Init.MemInc = DMA_MINC_ENABLE;
  hdma_dma_generator0.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_dma_generator0.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_dma_generator0.Init.Mode = DMA_NORMAL;
  hdma_dma_generator0.Init.Priority = DMA_PRIORITY_VERY_HIGH;
  hdma_dma_generator0.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_dma_generator0.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
  hdma_dma_generator0.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_dma_generator0.Init.PeriphBurst = DMA_PBURST_SINGLE;
__HAL_LINKDMA(&htim8, hdma[TIM_DMA_ID_CC4], hdma_dma_generator0);
  HAL_DMA_Init(htim8.hdma[TIM_DMA_ID_CC4]);
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == USER_Btn_Pin) {
      //Queue the data to be sent
      uint8_t dataToSend = 0b10111111;
      QueueOutputDataToSend(&dataToSend, 1, 1);
    }
}



void Error_Handler(void)
{
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
