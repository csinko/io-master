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
  IOM_ERROR_QUEUE_FULL, ///< The queue was full
  IOM_ERROR_NULL_POINTER, ///< Unallocated memory
  IOM_ERROR_QUEUE_EMPTY, ///< The queue was empty
  IOM_ERROR_INVALID, ///< Invalid input
} IOM_ERROR;

typedef struct {
  uint8_t* data; ///< The location of data in the buffer
  size_t length; ///< The lenght of the data (in bytes)
} IOM_Output_Buffer;

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
