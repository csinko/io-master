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
#include "iopin.h"
#include "data.h"
#include "core.h"
#include "clock.h"
#include "gpio.h"
#include "io_dma.h"
#include "timer.h"
#include "dac.h"
#include "uart.h"
#include "stm32h7xx_hal_dma.h"
#include "stm32h743xx.h"
#include "log.h"
#include <stdlib.h>

#if defined( __ICCARM__ )
  #define DMA_BUFFER \
      _Pragma("location=\".dma_buffer\"")
#else
  #define DMA_BUFFER \
      __attribute__((section(".dma_buffer")))
#endif

uint8_t DMABusyFlag = 0;



int main(void)
{
  HAL_Init();
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  InitSystemClock();
  InitGPIO();
  InitDAC();
  //InitI2CDAC();
  InitTimers();
  InitDMA();
  //InitUSB();

  IOM_ERROR err = InitUART();
  if (err == IOM_ERROR_INVALID) {
    HAL_Delay(1000);
  }
  uint8_t* pData = malloc(2);
  UARTQueueRXData(pData, 2);

//  EnableTimer(1);
//  StartTimer(1);
//  EnableTimer(2);
//  StartTimer(2);
//  EnableTimer(3);
//  StartTimer(3);
//  EnableTimer(4);
//  StartTimer(4);

  SetIOPinDataState(1, IOCFG_DATA_STATE_OUTPUT);
  SetIOPinPolarity(1, IOCFG_POLARITY_FALSE);
  SetIOPinIdleState(1, IOCFG_IDLE_STATE_LOW);

  while (1)
  {

    //If the output queue is not empty and the DMA is not busy
    uint32_t counter = __HAL_DMA_GET_COUNTER(htim8.hdma[TIM_DMA_ID_CC4]);
    if ((output_buf_queue_size > 0) && (counter == 0)) {
      if (DMABusyFlag != 0) {
        GPIOD->ODR = 0b0000000000000000;
        ResetDMA();
        DMABusyFlag = 0;
      }
      DMABusyFlag = 1;
      SendOutputData();
      //Send the front of the output queue over DMA
    } 
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
