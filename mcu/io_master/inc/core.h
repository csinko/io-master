#ifndef __IO_MASTER_CORE_H
#define __IO_MASTER_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <stdint.h>

typedef enum {
  IOM_OK, ///< No errors
  IOM_ERROR_BUFFER_FULL, ///< The buffer was full
  IOM_ERROR_BUFFER_EMPTY, ///< THe buffer was empty
  IOM_ERROR_QUEUE_FULL, ///< The queue was full
  IOM_ERROR_NULL_POINTER, ///< Unallocated memory
  IOM_ERROR_QUEUE_EMPTY, ///< The queue was empty
  IOM_ERROR_INVALID, ///< Invalid input
  IOM_ERROR_NOT_READY, ///< Not ready
  IOM_ERROR_INTERFACE, ///< Something went wrong with the interface
} IOM_ERROR;

typedef struct {
  uint8_t* data; ///< The location of data in the buffer
  size_t length; ///< The length of the data (in bytes)
} IOM_Output_Buffer;

typedef enum {
  IOM_QS_RTS, ///< Data is ready to send
  IOM_QS_BSY, ///< Data is being sent
  IOM_QS_RDY, ///< Waiting for data to send
} IOM_Queue_State;

typedef enum {
  IOM_REGISTER_HIGH, ///< The High Register
  IOM_REGISTER_LOW, ///< THe Low Register 
} IOM_REGISTER;

typedef enum {
IOM_STATE_READY, ///< Ready to send or receive data
IOM_STATE_INIT, ///< Device Initialization
IOM_STATE_CONF, ///< Device Configuration
IOM_STATE_BUSY, ///< Actively sending or receiving data
IOM_STATE_ERROR, ///< There was an error
} IOM_STATE;

IOM_STATE IOMState;

#ifdef __cplusplus
}
#endif
#endif
