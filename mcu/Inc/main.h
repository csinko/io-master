/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void writeAllExtDac(float Vout);
void writeExtDac(uint8_t channel, float Vout);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IO_7_8_DIFF_Pin GPIO_PIN_13
#define IO_7_8_DIFF_GPIO_Port GPIOC
#define IO_5_6_DIFF_Pin GPIO_PIN_14
#define IO_5_6_DIFF_GPIO_Port GPIOC
#define IO_5_6_TERM_N_Pin GPIO_PIN_15
#define IO_5_6_TERM_N_GPIO_Port GPIOC
#define STATUS_R_Pin GPIO_PIN_0
#define STATUS_R_GPIO_Port GPIOF
#define STATUS_G_Pin GPIO_PIN_1
#define STATUS_G_GPIO_Port GPIOF
#define STATUS_B_Pin GPIO_PIN_2
#define STATUS_B_GPIO_Port GPIOF
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH
#define ULPI_STP_Pin GPIO_PIN_0
#define ULPI_STP_GPIO_Port GPIOC
#define IO_7_PU_Pin GPIO_PIN_1
#define IO_7_PU_GPIO_Port GPIOC
#define ULPI_DIR_Pin GPIO_PIN_2
#define ULPI_DIR_GPIO_Port GPIOC
#define ULPI_NXT_Pin GPIO_PIN_3
#define ULPI_NXT_GPIO_Port GPIOC
#define IO_1_OUT_Pin GPIO_PIN_0
#define IO_1_OUT_GPIO_Port GPIOA
#define IO_2_OUT_Pin GPIO_PIN_1
#define IO_2_OUT_GPIO_Port GPIOA
#define IO_3_OUT_Pin GPIO_PIN_2
#define IO_3_OUT_GPIO_Port GPIOA
#define ULPI_D0_Pin GPIO_PIN_3
#define ULPI_D0_GPIO_Port GPIOA
#define Vout_SETPOINT_Pin GPIO_PIN_4
#define Vout_SETPOINT_GPIO_Port GPIOA
#define ULPI_CK_Pin GPIO_PIN_5
#define ULPI_CK_GPIO_Port GPIOA
#define IO_6_PU_Pin GPIO_PIN_6
#define IO_6_PU_GPIO_Port GPIOA
#define IO_8_OUT_Pin GPIO_PIN_7
#define IO_8_OUT_GPIO_Port GPIOA
#define IO_7_PD_N_Pin GPIO_PIN_4
#define IO_7_PD_N_GPIO_Port GPIOC
#define IO_8_PU_Pin GPIO_PIN_5
#define IO_8_PU_GPIO_Port GPIOC
#define ULPI_D1_Pin GPIO_PIN_0
#define ULPI_D1_GPIO_Port GPIOB
#define ULPI_D2_Pin GPIO_PIN_1
#define ULPI_D2_GPIO_Port GPIOB
#define IO_6_PD_N_Pin GPIO_PIN_2
#define IO_6_PD_N_GPIO_Port GPIOB
#define IO_5_PU_Pin GPIO_PIN_0
#define IO_5_PU_GPIO_Port GPIOG
#define IO_5_PD_N_Pin GPIO_PIN_1
#define IO_5_PD_N_GPIO_Port GPIOG
#define IO_1_IN_Pin GPIO_PIN_8
#define IO_1_IN_GPIO_Port GPIOE
#define IO_2_IN_Pin GPIO_PIN_9
#define IO_2_IN_GPIO_Port GPIOE
#define IO_3_IN_Pin GPIO_PIN_10
#define IO_3_IN_GPIO_Port GPIOE
#define IO_4_IN_Pin GPIO_PIN_11
#define IO_4_IN_GPIO_Port GPIOE
#define IO_5_IN_Pin GPIO_PIN_12
#define IO_5_IN_GPIO_Port GPIOE
#define IO_6_IN_Pin GPIO_PIN_13
#define IO_6_IN_GPIO_Port GPIOE
#define IO_7_IN_Pin GPIO_PIN_14
#define IO_7_IN_GPIO_Port GPIOE
#define IO_8_IN_Pin GPIO_PIN_15
#define IO_8_IN_GPIO_Port GPIOE
#define ULPI_D3_Pin GPIO_PIN_10
#define ULPI_D3_GPIO_Port GPIOB
#define ULPI_D4_Pin GPIO_PIN_11
#define ULPI_D4_GPIO_Port GPIOB
#define ULPI_D5_Pin GPIO_PIN_12
#define ULPI_D5_GPIO_Port GPIOB
#define ULPI_D6_Pin GPIO_PIN_13
#define ULPI_D6_GPIO_Port GPIOB
#define IO_1_PU_Pin GPIO_PIN_14
#define IO_1_PU_GPIO_Port GPIOB
#define IO_1_PD_N_Pin GPIO_PIN_15
#define IO_1_PD_N_GPIO_Port GPIOB
#define IO_1_TRIS_N_Pin GPIO_PIN_8
#define IO_1_TRIS_N_GPIO_Port GPIOD
#define IO_2_TRIS_N_Pin GPIO_PIN_9
#define IO_2_TRIS_N_GPIO_Port GPIOD
#define IO_3_TRIS_N_Pin GPIO_PIN_10
#define IO_3_TRIS_N_GPIO_Port GPIOD
#define IO_4_TRIS_N_Pin GPIO_PIN_11
#define IO_4_TRIS_N_GPIO_Port GPIOD
#define IO_5_TRIS_N_Pin GPIO_PIN_12
#define IO_5_TRIS_N_GPIO_Port GPIOD
#define IO_6_TRIS_N_Pin GPIO_PIN_13
#define IO_6_TRIS_N_GPIO_Port GPIOD
#define IO_7_TRIS_N_Pin GPIO_PIN_14
#define IO_7_TRIS_N_GPIO_Port GPIOD
#define IO_8_TRIS_N_Pin GPIO_PIN_15
#define IO_8_TRIS_N_GPIO_Port GPIOD
#define IO_1_2_DIFF_Pin GPIO_PIN_2
#define IO_1_2_DIFF_GPIO_Port GPIOG
#define IO_1_2_TERM_N_Pin GPIO_PIN_3
#define IO_1_2_TERM_N_GPIO_Port GPIOG
#define IO_2_PD_N_Pin GPIO_PIN_4
#define IO_2_PD_N_GPIO_Port GPIOG
#define IO_2_PU_Pin GPIO_PIN_5
#define IO_2_PU_GPIO_Port GPIOG
#define IO_3_PU_Pin GPIO_PIN_6
#define IO_3_PU_GPIO_Port GPIOG
#define IO_3_PD_N_Pin GPIO_PIN_7
#define IO_3_PD_N_GPIO_Port GPIOG
#define IO_4_OUT_Pin GPIO_PIN_6
#define IO_4_OUT_GPIO_Port GPIOC
#define IO_8_PD_N_Pin GPIO_PIN_7
#define IO_8_PD_N_GPIO_Port GPIOC
#define IO_7_8_TERM_N_Pin GPIO_PIN_8
#define IO_7_8_TERM_N_GPIO_Port GPIOC
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOC
#define I2C_SCL_Pin GPIO_PIN_8
#define I2C_SCL_GPIO_Port GPIOA
#define UART_TXO_Pin GPIO_PIN_9
#define UART_TXO_GPIO_Port GPIOA
#define UART_RXI_Pin GPIO_PIN_10
#define UART_RXI_GPIO_Port GPIOA
#define USB_FS_DM_Pin GPIO_PIN_11
#define USB_FS_DM_GPIO_Port GPIOA
#define USB_FS_DP_Pin GPIO_PIN_12
#define USB_FS_DP_GPIO_Port GPIOA
#define TMS_SWDIO_Pin GPIO_PIN_13
#define TMS_SWDIO_GPIO_Port GPIOA
#define TCK_SWDCLK_Pin GPIO_PIN_14
#define TCK_SWDCLK_GPIO_Port GPIOA
#define TDI_Pin GPIO_PIN_15
#define TDI_GPIO_Port GPIOA
#define IO_3_4_TERM_N_Pin GPIO_PIN_10
#define IO_3_4_TERM_N_GPIO_Port GPIOC
#define IO_3_4_DIFF_Pin GPIO_PIN_11
#define IO_3_4_DIFF_GPIO_Port GPIOC
#define IO_4_PD_N_Pin GPIO_PIN_12
#define IO_4_PD_N_GPIO_Port GPIOC
#define IO_1_OUTD0_Pin GPIO_PIN_0
#define IO_1_OUTD0_GPIO_Port GPIOD
#define IO_2_OUTD1_Pin GPIO_PIN_1
#define IO_2_OUTD1_GPIO_Port GPIOD
#define IO_3_OUTD2_Pin GPIO_PIN_2
#define IO_3_OUTD2_GPIO_Port GPIOD
#define IO_4_OUTD3_Pin GPIO_PIN_3
#define IO_4_OUTD3_GPIO_Port GPIOD
#define IO_5_OUT_Pin GPIO_PIN_4
#define IO_5_OUT_GPIO_Port GPIOD
#define IO_6_OUT_Pin GPIO_PIN_5
#define IO_6_OUT_GPIO_Port GPIOD
#define IO_7_OUT_Pin GPIO_PIN_6
#define IO_7_OUT_GPIO_Port GPIOD
#define IO_8_OUTD7_Pin GPIO_PIN_7
#define IO_8_OUTD7_GPIO_Port GPIOD
#define TDO_SWO_Pin GPIO_PIN_3
#define TDO_SWO_GPIO_Port GPIOB
#define nRESET_Pin GPIO_PIN_4
#define nRESET_GPIO_Port GPIOB
#define ULPI_D7_Pin GPIO_PIN_5
#define ULPI_D7_GPIO_Port GPIOB
#define IO_4_PU_Pin GPIO_PIN_6
#define IO_4_PU_GPIO_Port GPIOB
#define IO_5_OUTB7_Pin GPIO_PIN_7
#define IO_5_OUTB7_GPIO_Port GPIOB
#define IO_6_OUTB8_Pin GPIO_PIN_8
#define IO_6_OUTB8_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
