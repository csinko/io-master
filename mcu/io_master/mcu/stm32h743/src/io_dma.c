#include "io_dma.h"
#include "main.h"
#include "mcu_conf.h"
#include "timer.h"
#include "stm32h743xx.h"
#include "stm32h7xx_hal.h"

DMA_HandleTypeDef hdma_dma_generator0 = {0};
uint8_t isSending = 0;
IOM_ERROR InitDMA(void) {
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
  return IOM_OK;
}

void StartDMATransfer(IOM_Output_Buffer* pBuffer) {
//  HAL_DMA_Start(htim8.hdma[TIM_DMA_ID_CC4], (uint32_t)pBuffer->data, (uint32_t)(&((IO_PIN_GPIO_OUTPUT_PORT)->ODR)) + IO_PIN_GPIO_OUTPUT_OFFSET, pBuffer->length);
  HAL_DMA_Start(htim8.hdma[TIM_DMA_ID_CC4], (uint32_t)pBuffer->data, (uint32_t)(&(GPIOD->ODR) + 1), pBuffer->length + 1);
  isSending = 1;
  HAL_GPIO_TogglePin(STATUS_B_GPIO_Port, STATUS_B_Pin);
  __HAL_TIM_ENABLE_DMA(&htim8, TIM_DMA_CC4);
}

void ResetDMA() {
  HAL_DMA_Abort((htim8.hdma[TIM_DMA_ID_CC4]));
  HAL_DMA_DeInit((htim8.hdma[TIM_DMA_ID_CC4]));
  HAL_DMA_Init((htim8.hdma[TIM_DMA_ID_CC4]));
  HAL_GPIO_TogglePin(STATUS_B_GPIO_Port, STATUS_B_Pin);
  isSending = 0;
}

