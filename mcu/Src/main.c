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
#include "usb.h"
#include "dac.h"

#if defined( __ICCARM__ )
  #define DMA_BUFFER \
      _Pragma("location=\".dma_buffer\"")
#else
  #define DMA_BUFFER \
      __attribute__((section(".dma_buffer")))
#endif

DMA_HandleTypeDef hdma_dma_generator0;
uint8_t DMABusyFlag = 0;



int main(void)
{
  HAL_Init();

  InitSystemClock();
  InitGPIO();
  InitDAC();
  HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1);
  HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);
  unsigned int num1 = 0, num2 = 2048;
  
  InitUSB();
  InitTimers();
  InitDMA();
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




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == USER_Btn_Pin) {
      //Queue the data to be sent
      uint8_t dataToSend = 0b10111111;
      QueueOutputDataToSend(&dataToSend, 1, 1);
    }
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
