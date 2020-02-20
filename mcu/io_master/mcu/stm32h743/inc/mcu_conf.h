#ifndef __IO_MASTER_MCU_CONF_H
#define __IO_MASTER_MCU_CONF_H
#ifdef __cplusplus
extern "C" {
#endif
//DMA Buffer Size Definitions
#define DMA_OUTPUT_BUF_MAX_SIZE 1024 ///< A max size so the buffer memory domain doesn't fill up
#define DMA_WRITE_BUF_MIN_ADDR ((void*) 0x30000000) ///< The starting address of the DMA write buffer
#define DMA_WRITE_BUF_MAX_ADDR ((void*) DMA_WRITE_BUF_MIN_ADDR + DMA_OUTPUT_BUF_MAX_SIZE) ///< The ending address of the DMA Write buffer
#define OUTPUT_BUF_QUEUE_MAX_SIZE 10 ///< The size of the DMA output buffer queue

//IO Pin Definitions
#define IO_PIN_GPIO_OUTPUT_PORT GPIOD
#define IO_PIN_GPIO_OUTPUT_OFFSET 3
#define IO_PIN_1_OUTPUT 0
#define IO_PIN_2_OUTPUT 1
#define IO_PIN_3_OUTPUT 2
#define IO_PIN_4_OUTPUT 3


#define IO_PIN_GPIO_INPUT_PORT GPIOE
#define IO_PIN_GPIO_INPUT_OFFSET 2
#define IO_PIN_1_INPUT 8
#define IO_PIN_2_INPUT 9
#define IO_PIN_3_INPUT 10
#define IO_PIN_4_INPUT 11


#ifdef __cplusplus
}
#endif
#endif
