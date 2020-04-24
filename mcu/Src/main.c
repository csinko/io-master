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
  InitI2CDAC();
  InitTimers();
  InitDMA();
  InitIOPins();
  //InitUSB();

  IOM_ERROR err = InitUART();
  if (err == IOM_ERROR_INVALID) {
    HAL_Delay(1000);
  }
  uint8_t* pData = malloc(2);
  UARTQueueRXData(pData, 2);

//Clock Pin
//  SetIOPinDataState(1, IOCFG_DATA_STATE_CLOCK);
//  SetIOPinPolarity(1, IOCFG_POLARITY_FALSE);

//Output Pin
//  SetIOPinDataState(2, IOCFG_DATA_STATE_OUTPUT);
//  SetIOPinPolarity(2, IOCFG_POLARITY_FALSE);
//  SetIOPinIdleState(2, IOCFG_IDLE_STATE_LOW);
//CS Pin
//  SetIOPinDataState(4, IOCFG_DATA_STATE_CS);
//  SetIOPinPolarity(4, IOCFG_POLARITY_FALSE);
//  SetIOPinIdleState(4, IOCFG_IDLE_STATE_HIGH);

SetIOPinIdleState(1, IOCFG_IDLE_STATE_LOW);
SetIOPinIdleState(2, IOCFG_IDLE_STATE_LOW);
SetIOPinIdleState(3, IOCFG_IDLE_STATE_LOW);
SetIOPinIdleState(4, IOCFG_IDLE_STATE_LOW);

SetIOPinDataState(1, IOCFG_DATA_STATE_CLOCK);
SetIOPinDataState(2, IOCFG_DATA_STATE_CLOCK);
SetIOPinDataState(3, IOCFG_DATA_STATE_CLOCK);
SetIOPinDataState(4, IOCFG_DATA_STATE_CLOCK);


//Write tristate due to current board issue
  //HAL_GPIO_WritePin(IO_1_TRIS_N_GPIO_Port, IO_1_TRIS_N_Pin, GPIO_PIN_RESET);

  uint32_t counter;
  while (1)
  {
    switch(IOMState) {
      case IOM_STATE_INIT:
        IOMState = IOM_STATE_READY;
        break;
      case IOM_STATE_BUSY:
        if (DMABusyFlag == 1) {
          counter = __HAL_DMA_GET_COUNTER(htim8.hdma[TIM_DMA_ID_CC4]);
          if (counter != 0) {
            HAL_GPIO_TogglePin(STATUS_G_GPIO_Port, STATUS_G_Pin);
          } else {
            HAL_GPIO_WritePin(STATUS_G_GPIO_Port, STATUS_G_Pin, GPIO_PIN_RESET);
            DMABusyFlag = 0;
          }
        } else {
          if (output_buf_queue_size > 0) {
            DMABusyFlag = 1;
            SendOutputData();
          }
        }
      case IOM_STATE_CONF:
      case IOM_STATE_READY:
      if (command_buf_queue_size > 0) {
        ProcessCommand();
      }
        break;
      case IOM_STATE_ERROR:
          HAL_GPIO_TogglePin(STATUS_R_GPIO_Port, STATUS_R_GPIO_Pin);
        break;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
