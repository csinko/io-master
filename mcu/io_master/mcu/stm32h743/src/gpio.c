#include "gpio.h"
#include <stdint.h>
#include <unistd.h>
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_rcc.h"
#include "stm32h743xx.h"
#include "mcu_conf.h"

IOM_ERROR InitGPIO(void) {

  GPIO_InitTypeDef GPIO_InitStruct = {0};


  //Enable GPIO Port Clocks
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  //Determine what pins should be set to High (Active Low).
  //All other pins will be set to Low (Active High)
  const uint16_t GPIOA_SET_PINS = 0
  ;

  const uint16_t GPIOB_SET_PINS = 0
  | IO_1_PD_N_Pin
  #ifdef IOM_8_IO_PINS
  | IO_6_PD_N_Pin
  #endif
  | nRESET_Pin
  ;

  const uint16_t GPIOC_SET_PINS = 0
  | IO_3_4_TERM_N_Pin
  | IO_4_PD_N_Pin
  #ifdef IOM_8_IO_PINS
  | IO_5_6_TERM_N_Pin
  | IO_7_8_TERM_N_Pin
  | IO_7_PD_N_Pin
  | IO_8_PD_N_Pin
  #endif
  ;

  const uint16_t GPIOD_SET_PINS = 0
  | IO_1_TRIS_N_Pin
  | IO_2_TRIS_N_Pin
  | IO_3_TRIS_N_Pin
  | IO_4_TRIS_N_Pin
  #ifdef IOM_8_IO_PINS
  | IO_5_TRIS_N_Pin
  | IO_6_TRIS_N_Pin
  | IO_7_TRIS_N_Pin
  | IO_8_TRIS_N_Pin
  #endif
  ;

  const uint16_t GPIOE_SET_PINS = 0
  ;

  const uint16_t GPIOF_SET_PINS = 0
  ;

  const uint16_t GPIOG_SET_PINS = 0
  | IO_2_PD_N_Pin
  | IO_3_PD_N_Pin
  | IO_1_2_TERM_N_Pin
  #ifdef IOM_8_IO_PINS
  | IO_5_PD_N_Pin
  #endif
  ;

  const uint16_t GPIOH_SET_PINS = 0
  ;

  //Write all of the pin states
  HAL_GPIO_WritePin(GPIOA, GPIOA_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ~GPIOA_SET_PINS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB, GPIOB_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, ~GPIOB_SET_PINS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOC, GPIOC_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, ~GPIOC_SET_PINS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOD, GPIOD_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD, ~GPIOD_SET_PINS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOE, GPIOE_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOE, ~GPIOE_SET_PINS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOF, GPIOF_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOF, ~GPIOF_SET_PINS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOG, GPIOG_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOG, ~GPIOG_SET_PINS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOH, GPIOH_SET_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOH, ~GPIOH_SET_PINS, GPIO_PIN_RESET);

  //Default input pin configuration (Clock and I/O In/Out Pins)
  const uint16_t GPIOA_INPUT_PINS = 0
  | IO_1_CLK_Pin
  | IO_2_CLK_Pin
  | IO_3_CLK_Pin
  #ifdef IOM_8_IO_PINS
  | IO_8_CLK_Pin
  #endif
  ;

  const uint16_t GPIOB_INPUT_PINS = 0
  #ifdef IOM_8_IO_PINS
  | IO_5_CLK_Pin
  | IO_6_CLK_Pin
  | IO_7_CLK_Pin
  #endif
  ;

  const uint16_t GPIOC_INPUT_PINS = 0
  | IO_4_CLK_Pin
  ;

  const uint16_t GPIOD_INPUT_PINS = 0
  | IO_1_OUT_Pin
  | IO_2_OUT_Pin
  | IO_3_OUT_Pin
  | IO_4_OUT_Pin
  #ifdef IOM_8_IO_PINS
  | IO_5_OUT_Pin
  | IO_6_OUT_Pin
  | IO_7_OUT_Pin
  | IO_8_OUT_Pin
  #endif
  ;

  const uint16_t GPIOE_INPUT_PINS = 0
  | IO_1_IN_Pin
  | IO_2_IN_Pin
  | IO_3_IN_Pin
  | IO_4_IN_Pin
  #ifdef IOM_8_IO_PINS
  | IO_5_IN_Pin
  | IO_6_IN_Pin
  | IO_7_IN_Pin
  | IO_8_IN_Pin
  #endif
  ;

  const uint16_t GPIOF_INPUT_PINS = 0
  //Must Configure Inputs
  ;
  
  const uint16_t GPIOG_INPUT_PINS = 0
  //Must Configure Inputs
  ;

  const uint16_t GPIOH_INPUT_PINS = 0
  //Must Configure Inputs
  ;

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  GPIO_InitStruct.Pin = GPIOA_INPUT_PINS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIOB_INPUT_PINS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIOC_INPUT_PINS;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIOD_INPUT_PINS;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIOE_INPUT_PINS;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  //Must Configure GPIOF Inputs
  //Must Configure GPIOG Inputs
  //Must Configure GPIOH Inputs



  //Special Pin Configurations

  //ULPI Interface pin configuration
  GPIO_InitStruct.Pin = 0
  | ULPI_D0_Pin
  | ULPI_CK_Pin
  ;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = 0
  | ULPI_D1_Pin
  | ULPI_D2_Pin
  | ULPI_D3_Pin
  | ULPI_D4_Pin 
  | ULPI_D5_Pin
  | ULPI_D6_Pin
  | ULPI_D7_Pin
  ;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = 0
  | ULPI_STP_Pin
  | ULPI_DIR_Pin
  | ULPI_NXT_Pin
  ;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


  //I2C Interface pin configuration
  GPIO_InitStruct.Pin = I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C_SDA_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = I2C_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C_SCL_GPIO_Port, &GPIO_InitStruct);

  //UART Interface pin configuration
  GPIO_InitStruct.Pin = 0
  | UART_TXO_Pin
  | UART_RXI_Pin
  ;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  //USB Interface pin configuration
  GPIO_InitStruct.Pin = 0
  | USB_FS_DM_Pin
  | USB_FS_DP_Pin
  ;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  const uint16_t GPIOA_AF_PINS = 0
  | ULPI_D0_Pin
  | ULPI_CK_Pin
  | I2C_SCL_Pin
  | UART_TXO_Pin
  | UART_RXI_Pin
  | USB_FS_DM_Pin
  | USB_FS_DP_Pin
  ;

  const uint16_t GPIOB_AF_PINS = 0
  | ULPI_D1_Pin
  | ULPI_D2_Pin
  | ULPI_D3_Pin
  | ULPI_D4_Pin
  | ULPI_D5_Pin
  | ULPI_D6_Pin
  | ULPI_D7_Pin
  ;

  const uint16_t GPIOC_AF_PINS = 0
  | ULPI_STP_Pin
  | ULPI_DIR_Pin
  | ULPI_NXT_Pin
  | I2C_SDA_Pin
  ;

  const uint16_t GPIOD_AF_PINS = 0
  ;

  const uint16_t GPIOE_AF_PINS = 0
  ;

  const uint16_t GPIOF_AF_PINS = 0
  ;

  const uint16_t GPIOG_AF_PINS = 0
  ;
  
  const uint16_t GPIOH_AF_PINS = 0
  ;

  //Configure everything else as a low speed output pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_InitStruct.Pin = ~(GPIOA_INPUT_PINS | GPIOA_AF_PINS);
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ~(GPIOB_INPUT_PINS | GPIOB_AF_PINS);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ~(GPIOC_INPUT_PINS | GPIOC_AF_PINS);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ~(GPIOD_INPUT_PINS | GPIOD_AF_PINS);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ~(GPIOE_INPUT_PINS | GPIOE_AF_PINS);
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ~(GPIOF_INPUT_PINS | GPIOF_AF_PINS);
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ~(GPIOG_INPUT_PINS | GPIOG_AF_PINS);
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ~(GPIOH_INPUT_PINS | GPIOH_AF_PINS);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  return IOM_OK;
}