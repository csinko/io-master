#include "io_dma.h"
#include "main.h"
#include "mcu_conf.h"

void StartDMATransfer(IOM_Output_Buffer* pBuffer) {
  HAL_DMA_Start(htim8.hdma[TIM_DMA_ID_CC4], (uint32_t)pBuffer->data, (uint32_t)(&((IO_PIN_GPIO_OUTPUT_PORT)->ODR)) + IO_PIN_GPIO_OUTPUT_OFFSET, pBuffer->length);
  __HAL_TIM_ENABLE_DMA(&htim8, TIM_DMA_CC4);
}

