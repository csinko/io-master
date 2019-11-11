//generate_data.c
//Author: Cameron Sinko
#include "generate_data.h"
#include "stm32h7xx_hal.h"
#include <stdlib.h>
#include <string.h>
#include "main.h"


void generate_data(DMA_HandleTypeDef *DMAHandle, TIM_HandleTypeDef *TIMHandle) {
  //Generate some dummy data to send
  uint8_t dummyData = 0b11111111;
  uint8_t* dataToSend = malloc(256);
  memset(dataToSend, dummyData, 256);
  __HAL_TIM_DISABLE(TIMHandle);
	__HAL_DMA_CLEAR_FLAG(DMAHandle, DMA_FLAG_TCIF1_5 | DMA_FLAG_HTIF1_5 | DMA_FLAG_TEIF1_5);
	__HAL_TIM_CLEAR_FLAG(TIMHandle, TIM_FLAG_UPDATE | TIM_FLAG_CC1 | TIM_FLAG_CC2 | TIM_FLAG_CC3 | TIM_FLAG_CC4);
  HAL_DMA_Start_IT(DMAHandle, (uint32_t)dataToSend, (uint32_t)&GPIOF->ODR, 128);
  __HAL_TIM_ENABLE_DMA(TIMHandle, TIM_DMA_UPDATE);
    __HAL_TIM_ENABLE(TIMHandle);

}

