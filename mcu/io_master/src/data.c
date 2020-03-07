#include "data.h"
#include "iopin.h"
#include "core.h"
#include "io_dma.h"

uint8_t* output_buf_in_ptr = (uint8_t*) DMA_WRITE_BUF_MIN_ADDR;
uint8_t* output_buf_out_ptr = (uint8_t*) DMA_WRITE_BUF_MIN_ADDR;

uint8_t output_buf_queue_in_ptr = 0;
uint8_t output_buf_queue_out_ptr = 0;
uint8_t output_buf_queue_size = 0;

uint8_t dataToReceive = 0;
uint8_t bytesToSend = 0;


IOM_ERROR QueueOutputDataToSend(uint8_t* pData, size_t length, uint8_t pinNum) {
  ///Check if the data to send cannot fit in the end of the buffer
  if ((void*)(output_buf_in_ptr + (length * 8)) > DMA_WRITE_BUF_MAX_ADDR) {
    /// If it cannot, see if it can fit in the beginning
    if (((void*)output_buf_out_ptr) - DMA_WRITE_BUF_MIN_ADDR >= length * 8) {
      output_buf_in_ptr = DMA_WRITE_BUF_MIN_ADDR;
    } else {
      return IOM_ERROR_BUFFER_FULL;
    }
  } 
  //Make sure the output buffer queue has space available
  if (output_buf_queue_size >= OUTPUT_BUF_QUEUE_MAX_SIZE) {
    return IOM_ERROR_QUEUE_FULL;
  }

  //Add the data to be output to the queue
  output_buf_queue[output_buf_queue_in_ptr].data = output_buf_in_ptr;
  output_buf_queue[output_buf_queue_in_ptr].length = length * 8;

 *(output_buf_in_ptr) = idle_pin_output;
 //Iterate through each byte
 for (size_t i = 0; i < length; i++) {
   //Check if the bits need flipped
   if (IO_Pins[pinNum-1].polarity == IOCFG_POLARITY_TRUE) {
     *(pData + i) = ~*(pData + 1);
   }
   //Iterate through each bit
  for (size_t j = 0; j < 8; j++) {
    //Set the byte in the output buffer to the current bit of data
    if (IO_Pins[pinNum-1].idleState == IOCFG_IDLE_STATE_HIGH) {
      //Idle high, set bits to low
      *(output_buf_in_ptr) &= (((*(pData+i) >> (7 - j))& 0x01) == 0) ? ~((GetIOPinOutputMask(pinNum) + 1)) : 0xFF;
    } else {
      //Idle low, set bits to high
      *(output_buf_in_ptr) |= ((*(pData+i) >> (7 - j)) << (GetIOPinOutputPos(pinNum))) & GetIOPinOutputMask(pinNum);
    }
    output_buf_in_ptr++;
    *(output_buf_in_ptr) = idle_pin_output;
  }
 }

 output_buf_queue_in_ptr = (output_buf_queue_in_ptr + 1) % OUTPUT_BUF_QUEUE_MAX_SIZE;
 output_buf_queue_size ++;
 return IOM_OK;
}

IOM_ERROR SendOutputData(void) {
  if (output_buf_queue_size == 0) {
    return IOM_ERROR_QUEUE_EMPTY;
  }

  IOM_Output_Buffer* bufferData = &(output_buf_queue[output_buf_queue_out_ptr]);
  output_buf_queue_out_ptr = (output_buf_queue_out_ptr + 1) % OUTPUT_BUF_QUEUE_MAX_SIZE;
  output_buf_queue_size--;

  StartDMATransfer(bufferData);
  return IOM_OK;
}
