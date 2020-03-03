#ifndef __IO_MASTER_MCU_CONF_H
#define __IO_MASTER_MCU_CONF_H
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h743xx.h"
//DMA Buffer Size Definitions
#define DMA_OUTPUT_BUF_MAX_SIZE 1024 ///< A max size so the buffer memory domain doesn't fill up
#define DMA_WRITE_BUF_MIN_ADDR ((void*) 0x30000000) ///< The starting address of the DMA write buffer
#define DMA_WRITE_BUF_MAX_ADDR ((void*) DMA_WRITE_BUF_MIN_ADDR + DMA_OUTPUT_BUF_MAX_SIZE) ///< The ending address of the DMA Write buffer
#define OUTPUT_BUF_QUEUE_MAX_SIZE 10 ///< The size of the DMA output buffer queue

//UART Buffer Size Definitions
#define UART_TX_BUF_QUEUE_MAX_SIZE 10 ///< The size of the UART output buffer queue
#define UART_RX_BUF_QUEUE_MAX_SIZE 10 ///< The size of the UART input buffer queue

//IO Software Pin Definitions
#define IO_PIN_GPIO_INPUT_PORT GPIOE
#define IO_PIN_GPIO_INPUT_OFFSET 2
#define IO_PIN_1_INPUT 8
#define IO_PIN_2_INPUT 9
#define IO_PIN_3_INPUT 10
#define IO_PIN_4_INPUT 11

#define IO_PIN_GPIO_OUTPUT_PORT GPIOD
#define IO_PIN_GPIO_OUTPUT_OFFSET 3
#define IO_PIN_1_OUTPUT 0
#define IO_PIN_2_OUTPUT 1
#define IO_PIN_3_OUTPUT 2
#define IO_PIN_4_OUTPUT 3

//IO Input
#define IO_1_IN_GPIO_Port GPIOE
#define IO_1_IN_Pin GPIO_PIN_8

#define IO_2_IN_GPIO_Port GPIOE
#define IO_2_IN_Pin GPIO_PIN_9

#define IO_3_IN_GPIO_Port GPIOE
#define IO_3_IN_Pin GPIO_PIN_10

#define IO_4_IN_GPIO_Port GPIOE
#define IO_4_IN_Pin GPIO_PIN_11

#ifdef IOM_8_IO_PINS
#define IO_5_IN_GPIO_Port GPIOE
#define IO_5_IN_Pin GPIO_PIN_12

#define IO_6_IN_GPIO_Port GPIOE
#define IO_6_IN_Pin GPIO_PIN_13

#define IO_7_IN_GPIO_Port GPIOE
#define IO_7_IN_Pin GPIO_PIN_14

#define IO_8_IN_GPIO_Port GPIOE
#define IO_8_IN_Pin GPIO_PIN_15
#endif

//IO Timer OUT
#define IO_1_CLK_GPIO_Port GPIOA
#define IO_1_CLK_Pin GPIO_PIN_0

#define IO_2_CLK_GPIO_Port GPIOA
#define IO_2_CLK_Pin GPIO_PIN_1

#define IO_3_CLK_GPIO_Port GPIOA
#define IO_3_CLK_Pin GPIO_PIN_2

#define IO_4_CLK_GPIO_Port GPIOC
#define IO_4_CLK_Pin GPIO_PIN_6

#ifdef IOM_8_IO_PINS
#define IO_5_CLK_GPIO_Port GPIOB
#define IO_5_CLK_Pin GPIO_PIN_7

#define IO_6_CLK_GPIO_Port GPIOB
#define IO_6_CLK_Pin GPIO_PIN_8

#define IO_7_CLK_GPIO_Port GPIOB
#define IO_7_CLK_Pin GPIO_PIN_9

#define IO_8_CLK_GPIO_Port GPIOA
#define IO_8_CLK_Pin GPIO_PIN_7
#endif

//IO Digital OUT
#define IO_1_OUT_GPIO_Port GPIOD
#define IO_1_OUT_Pin GPIO_PIN_0

#define IO_2_OUT_GPIO_Port GPIOD
#define IO_2_OUT_Pin GPIO_PIN_1

#define IO_3_OUT_GPIO_Port GPIOD
#define IO_3_OUT_Pin GPIO_PIN_2

#define IO_4_OUT_GPIO_Port GPIOD
#define IO_4_OUT_Pin GPIO_PIN_3

#ifdef IOM_8_IO_PINS
#define IO_5_OUT_GPIO_Port GPIOD
#define IO_5_OUT_Pin GPIO_PIN_4

#define IO_6_OUT_GPIO_Port GPIOD
#define IO_6_OUT_Pin GPIO_PIN_5

#define IO_7_OUT_GPIO_Port GPIOD
#define IO_7_OUT_Pin GPIO_PIN_6

#define IO_8_OUT_GPIO_Port GPIOD
#define IO_8_OUT_Pin GPIO_PIN_7
#endif


// Differential Enable Pins
#define IO_1_2_DIFF_GPIO_Port GPIOG
#define IO_1_2_DIFF_Pin GPIO_PIN_2

#define IO_3_4_DIFF_GPIO_Port GPIOC
#define IO_3_4_DIFF_Pin GPIO_PIN_11

#ifdef IOM_8_IO_PINS
#define IO_5_6_DIFF_GPIO_Port GPIOC
#define IO_5_6_DIFF_Pin GPIO_PIN_14

#define IO_7_8_DIFF_GPIO_Port GPIOC
#define IO_7_8_DIFF_Pin GPIO_PIN_13
#endif

// Termination Pins (Active Low)
#define IO_1_2_TERM_N_GPIO_Port GPIOG
#define IO_1_2_TERM_N_Pin GPIO_PIN_3

#define IO_3_4_TERM_N_GPIO_Port GPIOC
#define IO_3_4_TERM_N_Pin GPIO_PIN_10

#ifdef IOM_8_IO_PINS
#define IO_5_6_TERM_N_GPIO_Port GPIOC
#define IO_5_6_TERM_N_Pin GPIO_PIN_15

#define IO_7_8_TERM_N_GPIO_Port GPIOC
#define IO_7_8_TERM_N_Pin GPIO_PIN_8
#endif

// Pullup Pins
#define IO_1_PU_GPIO_Port GPIOB
#define IO_1_PU_Pin GPIO_PIN_14

#define IO_2_PU_GPIO_Port GPIOG
#define IO_2_PU_Pin GPIO_PIN_5

#define IO_3_PU_GPIO_Port GPIOG
#define IO_3_PU_Pin GPIO_PIN_6

#define IO_4_PU_GPIO_Port GPIOB
#define IO_4_PU_Pin GPIO_PIN_6

#ifdef IOM_8_IO_PINS
#define IO_5_PU_GPIO_Port GPIOG
#define IO_5_PU_Pin GPIO_PIN_0

#define IO_6_PU_GPIO_Port GPIOA
#define IO_6_PU_Pin GPIO_PIN_6

#define IO_7_PU_GPIO_Port GPIOC
#define IO_7_PU_Pin GPIO_PIN_1

#define IO_8_PU_GPIO_Port GPIOC
#define IO_8_PU_Pin GPIO_PIN_5
#endif

//Pulldown Pins (Active Low)
#define IO_1_PD_N_GPIO_Port GPIOB
#define IO_1_PD_N_Pin GPIO_PIN_15

#define IO_2_PD_N_GPIO_Port GPIOG
#define IO_2_PD_N_Pin GPIO_PIN_4

#define IO_3_PD_N_GPIO_Port GPIOG
#define IO_3_PD_N_Pin GPIO_PIN_7

#define IO_4_PD_N_GPIO_Port GPIOC
#define IO_4_PD_N_Pin GPIO_PIN_12

#ifdef IOM_8_IO_PINS
#define IO_5_PD_N_GPIO_Port GPIOG
#define IO_5_PD_N_Pin GPIO_PIN_1

#define IO_6_PD_N_GPIO_Port GPIOB
#define IO_6_PD_N_Pin GPIO_PIN_2

#define IO_7_PD_N_GPIO_Port GPIOC
#define IO_7_PD_N_Pin GPIO_PIN_4

#define IO_8_PD_N_GPIO_Port GPIOC
#define IO_8_PD_N_Pin GPIO_PIN_7
#endif

//Tristate Pin (Active Low)
#define IO_1_TRIS_N_GPIO_Port GPIOD
#define IO_1_TRIS_N_Pin GPIO_PIN_8

#define IO_2_TRIS_N_GPIO_Port GPIOD
#define IO_2_TRIS_N_Pin GPIO_PIN_9

#define IO_3_TRIS_N_GPIO_Port GPIOD
#define IO_3_TRIS_N_Pin GPIO_PIN_10

#define IO_4_TRIS_N_GPIO_Port GPIOD
#define IO_4_TRIS_N_Pin GPIO_PIN_11

#ifdef IOM_8_IO_PINS
#define IO_5_TRIS_N_GPIO_Port GPIOD
#define IO_5_TRIS_N_Pin GPIO_PIN_12

#define IO_6_TRIS_N_GPIO_Port GPIOD
#define IO_6_TRIS_N_Pin GPIO_PIN_13

#define IO_7_TRIS_N_GPIO_Port GPIOD
#define IO_7_TRIS_N_Pin GPIO_PIN_14

#define IO_8_TRIS_N_GPIO_Port GPIOD
#define IO_8_TRIS_N_Pin GPIO_PIN_15
#endif

//Status LEDs
#define STATUS_R_GPIO_Port GPIOF
#define STATUS_R_Pin GPIO_PIN_1

#define STATUS_G_GPIO_Port GPIOF
#define STATUS_G_Pin GPIO_PIN_2

#define STATUS_B_GPIO_Port GPIOF
#define STATUS_B_Pin GPIO_PIN_0

//External Crystal Input
#define OSC_IN_GPIO_Port GPIOH
#define OSC_IN_Pin GPIO_PIN_0

//ULPI USB Interface
#define ULPI_STP_GPIO_Port GPIOC
#define ULPI_STP_Pin GPIO_PIN_0

#define ULPI_DIR_GPIO_Port GPIOC
#define ULPI_DIR_Pin GPIO_PIN_2

#define ULPI_NXT_GPIO_Port GPIOC
#define ULPI_NXT_Pin GPIO_PIN_3

#define ULPI_CK_GPIO_Port GPIOA
#define ULPI_CK_Pin GPIO_PIN_5

#define ULPI_D0_GPIO_Port GPIOA
#define ULPI_D0_Pin GPIO_PIN_3

#define ULPI_D1_GPIO_Port GPIOB
#define ULPI_D1_Pin GPIO_PIN_0

#define ULPI_D2_GPIO_Port GPIOB
#define ULPI_D2_Pin GPIO_PIN_1

#define ULPI_D3_GPIO_Port GPIOB
#define ULPI_D3_Pin GPIO_PIN_10

#define ULPI_D4_GPIO_Port GPIOB
#define ULPI_D4_Pin GPIO_PIN_11

#define ULPI_D5_GPIO_Port GPIOB
#define ULPI_D5_Pin GPIO_PIN_12

#define ULPI_D6_GPIO_Port GPIOB
#define ULPI_D6_Pin GPIO_PIN_13

#define ULPI_D7_GPIO_Port GPIOB
#define ULPI_D7_Pin GPIO_PIN_5

//DAC Output To Regulator
#define Vout_SETPOINT_GPIO_Port GPIOA
#define Vout_SETPOINT_Pin GPIO_PIN_4

//I2C (DAC?)
#define I2C_SDA_GPIO_Port GPIOC
#define I2C_SDA_Pin GPIO_PIN_9

#define I2C_SCL_GPIO_Port GPIOA
#define I2C_SCL_Pin GPIO_PIN_8

//Debug UART
#define UART_TXO_GPIO_Port GPIOA
#define UART_TXO_Pin GPIO_PIN_9

#define UART_RXI_GPIO_Port GPIOA
#define UART_RXI_Pin GPIO_PIN_10

//USB FS
#define USB_FS_DM_GPIO_Port GPIOA
#define USB_FS_DM_Pin GPIO_PIN_11

#define USB_FS_DP_GPIO_Port GPIOA
#define USB_FS_DP_Pin GPIO_PIN_12

//SWD (Unused)
#define TMS_SWDIO_GPIO_Port GPIOA
#define TMS_SWDIO_Pin GPIO_PIN_13

#define TCK_SWDCLK_GPIO_Port GPIOA
#define TCK_SWDCLK_Pin GPIO_PIN_14

#define TDI_GPIO_Port GPIOA
#define TDI_Pin GPIO_PIN_15

#define TDO_SWO_GPIO_Port GPIOB
#define TDO_SWO_Pin GPIO_PIN_3

#define nRESET_GPIO_Port GPIOB
#define nRESET_Pin GPIO_PIN_4

#ifdef __cplusplus
}
#endif
#endif
