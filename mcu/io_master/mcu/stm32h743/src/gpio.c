#include "gpio.h"
#include "stm32h7xx_hal.h"

IOM_ERROR InitGPIO(void) {

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, IO_7_8_DIFF_Pin|IO_5_6_TERM_N_Pin|IO_7_PU_Pin|IO_8_PU_Pin 
                          |IO_7_8_TERM_N_Pin|IO_4_PD_N_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, IO_5_6_DIFF_Pin|IO_7_PD_N_Pin|IO_8_PD_N_Pin|IO_3_4_TERM_N_Pin 
                          |IO_3_4_DIFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, STATUS_R_Pin|STATUS_G_Pin|STATUS_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(IO_6_PU_GPIO_Port, IO_6_PU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, IO_6_PD_N_Pin|IO_1_PU_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, IO_5_PU_Pin|IO_1_2_DIFF_Pin|IO_2_PD_N_Pin|IO_3_PU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, IO_5_PD_N_Pin|IO_1_2_TERM_N_Pin|IO_2_PU_Pin|IO_3_PD_N_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, IO_1_PD_N_Pin|IO_4_PU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, IO_1_TRIS_N_Pin|IO_2_TRIS_N_Pin|IO_3_TRIS_N_Pin|IO_4_TRIS_N_Pin 
                          |IO_5_TRIS_N_Pin|IO_6_TRIS_N_Pin|IO_7_TRIS_N_Pin|IO_8_TRIS_N_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, IO_1_OUTD0_Pin|IO_2_OUTD1_Pin|IO_3_OUTD2_Pin|IO_4_OUTD3_Pin 
                          |IO_5_OUT_Pin|IO_6_OUT_Pin|IO_7_OUT_Pin|IO_8_OUTD7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : IO_7_8_DIFF_Pin IO_5_6_DIFF_Pin IO_5_6_TERM_N_Pin IO_7_PU_Pin 
                           IO_7_PD_N_Pin IO_8_PU_Pin IO_8_PD_N_Pin IO_7_8_TERM_N_Pin 
                           IO_3_4_TERM_N_Pin IO_3_4_DIFF_Pin IO_4_PD_N_Pin */
  GPIO_InitStruct.Pin = IO_7_8_DIFF_Pin|IO_5_6_DIFF_Pin|IO_5_6_TERM_N_Pin|IO_7_PU_Pin 
                          |IO_7_PD_N_Pin|IO_8_PU_Pin|IO_8_PD_N_Pin|IO_7_8_TERM_N_Pin 
                          |IO_3_4_TERM_N_Pin|IO_3_4_DIFF_Pin|IO_4_PD_N_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : STATUS_R_Pin STATUS_G_Pin STATUS_B_Pin */
  GPIO_InitStruct.Pin = STATUS_R_Pin|STATUS_G_Pin|STATUS_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_STP_Pin ULPI_DIR_Pin ULPI_NXT_Pin */
  GPIO_InitStruct.Pin = ULPI_STP_Pin|ULPI_DIR_Pin|ULPI_NXT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_1_OUT_Pin */
  GPIO_InitStruct.Pin = IO_1_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(IO_1_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_2_OUT_Pin */
  GPIO_InitStruct.Pin = IO_2_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
  HAL_GPIO_Init(IO_2_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_3_OUT_Pin */
  GPIO_InitStruct.Pin = IO_3_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_TIM15;
  HAL_GPIO_Init(IO_3_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_D0_Pin ULPI_CK_Pin */
  GPIO_InitStruct.Pin = ULPI_D0_Pin|ULPI_CK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_6_PU_Pin */
  GPIO_InitStruct.Pin = IO_6_PU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IO_6_PU_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_8_OUT_Pin */
  GPIO_InitStruct.Pin = IO_8_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_TIM14;
  HAL_GPIO_Init(IO_8_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_D1_Pin ULPI_D2_Pin ULPI_D3_Pin ULPI_D4_Pin 
                           ULPI_D5_Pin ULPI_D6_Pin ULPI_D7_Pin */
  GPIO_InitStruct.Pin = ULPI_D1_Pin|ULPI_D2_Pin|ULPI_D3_Pin|ULPI_D4_Pin 
                          |ULPI_D5_Pin|ULPI_D6_Pin|ULPI_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_6_PD_N_Pin IO_1_PU_Pin IO_1_PD_N_Pin IO_4_PU_Pin */
  GPIO_InitStruct.Pin = IO_6_PD_N_Pin|IO_1_PU_Pin|IO_1_PD_N_Pin|IO_4_PU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_5_PU_Pin IO_5_PD_N_Pin IO_1_2_DIFF_Pin IO_1_2_TERM_N_Pin 
                           IO_2_PD_N_Pin IO_2_PU_Pin IO_3_PU_Pin IO_3_PD_N_Pin */
  GPIO_InitStruct.Pin = IO_5_PU_Pin|IO_5_PD_N_Pin|IO_1_2_DIFF_Pin|IO_1_2_TERM_N_Pin 
                          |IO_2_PD_N_Pin|IO_2_PU_Pin|IO_3_PU_Pin|IO_3_PD_N_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_1_IN_Pin IO_2_IN_Pin IO_3_IN_Pin IO_4_IN_Pin 
                           IO_5_IN_Pin IO_6_IN_Pin IO_7_IN_Pin IO_8_IN_Pin */
  GPIO_InitStruct.Pin = IO_1_IN_Pin|IO_2_IN_Pin|IO_3_IN_Pin|IO_4_IN_Pin 
                          |IO_5_IN_Pin|IO_6_IN_Pin|IO_7_IN_Pin|IO_8_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_1_TRIS_N_Pin IO_2_TRIS_N_Pin IO_3_TRIS_N_Pin IO_4_TRIS_N_Pin 
                           IO_5_TRIS_N_Pin IO_6_TRIS_N_Pin IO_7_TRIS_N_Pin IO_8_TRIS_N_Pin 
                           IO_1_OUTD0_Pin IO_2_OUTD1_Pin IO_3_OUTD2_Pin IO_4_OUTD3_Pin 
                           IO_5_OUT_Pin IO_6_OUT_Pin IO_7_OUT_Pin IO_8_OUTD7_Pin */
  GPIO_InitStruct.Pin = IO_1_TRIS_N_Pin|IO_2_TRIS_N_Pin|IO_3_TRIS_N_Pin|IO_4_TRIS_N_Pin 
                          |IO_5_TRIS_N_Pin|IO_6_TRIS_N_Pin|IO_7_TRIS_N_Pin|IO_8_TRIS_N_Pin 
                          |IO_1_OUTD0_Pin|IO_2_OUTD1_Pin|IO_3_OUTD2_Pin|IO_4_OUTD3_Pin 
                          |IO_5_OUT_Pin|IO_6_OUT_Pin|IO_7_OUT_Pin|IO_8_OUTD7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_4_OUT_Pin */
  GPIO_InitStruct.Pin = IO_4_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(IO_4_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2C_SDA_Pin */
  GPIO_InitStruct.Pin = I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C_SDA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2C_SCL_Pin */
  GPIO_InitStruct.Pin = I2C_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C_SCL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : UART_TXO_Pin UART_RXI_Pin */
  GPIO_InitStruct.Pin = UART_TXO_Pin|UART_RXI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_FS_DM_Pin USB_FS_DP_Pin */
  GPIO_InitStruct.Pin = USB_FS_DM_Pin|USB_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_5_OUTB7_Pin */
  GPIO_InitStruct.Pin = IO_5_OUTB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(IO_5_OUTB7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_6_OUTB8_Pin */
  GPIO_InitStruct.Pin = IO_6_OUTB8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
  HAL_GPIO_Init(IO_6_OUTB8_GPIO_Port, &GPIO_InitStruct);
    return IOM_OK;
}