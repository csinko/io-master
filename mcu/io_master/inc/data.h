#ifndef __IO_MASTER_DATA_H
#define __IO_MASTER_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcu_conf.h"
#include "core.h"
#include <unistd.h>
#include <stdint.h>


uint8_t* output_buf_in_ptr; ///< Pointer to add data to the buffer
uint8_t* output_buf_out_ptr; ///< Pointer to remove data from the buffer


IOM_Output_Buffer output_buf_queue[OUTPUT_BUF_QUEUE_MAX_SIZE]; ///< The buffer queue to output data

uint8_t output_buf_queue_in_ptr; ///< Index of queue of where to add data
uint8_t output_buf_queue_out_ptr; ///< Index of queue of where to remove data
uint8_t output_buf_queue_size; ///< The current size of the queue

uint8_t dataToReceive;

///
/// @brief puts a block of data into the output buffer
///
/// @param pData, pointer to the first byte of the data set
///
/// @param length, the length of the data to set, in bytes
///
/// @param pinNum, which pin to set
///
/// @return IOM_OK if OK, IOM_ERROR_BUFFER_FULL if
/// there is no room left in the output buffer, IOM_ERROR_QUEUE_FULL
/// if no room left in the output queue
///
IOM_ERROR QueueOutputDataToSend(uint8_t* pData, size_t length, uint8_t pinNum);
///
/// @brief sends out data from queue to GPIO via the DMA
///
/// @return IOM_OK if OK, IOM_ERROR_QUEUE_EMPTY if the queue has nothing to send
///
IOM_ERROR SendOutputData(void);

#ifdef __cplusplus
}
#endif
#endif
