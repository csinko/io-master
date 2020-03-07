#ifndef __IO_PIN_H
#define __IO_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcu_conf.h"
#include "core.h"
#include <unistd.h>
#include <stdint.h>

#define NUM_IO_PINS 4

uint8_t idle_pin_output;


typedef enum {
  IOCFG_IDLE_STATE_HIGH,
  IOCFG_IDLE_STATE_LOW,
  IOCFG_IDLE_STATE_TRISTATE,
} IOCFG_IDLE_STATE;

typedef enum {
  IOCFG_POLARITY_TRUE,
  IOCFG_POLARITY_FALSE,
} IOCFG_POLARITY;

typedef enum {
  IOCFG_DIFFERENTIAL_ENABLED,
  IOCFG_DIFFERENTIAL_DISABLED,
} IOCFG_DIFFERENTIAL;

typedef enum {
  IOCFG_DATA_STATE_DISABLED,
  IOCFG_DATA_STATE_INPUT,
  IOCFG_DATA_STATE_OUTPUT,
  IOCFG_DATA_STATE_CLOCK,
  IOCFG_DATA_STATE_CS,
} IOCFG_DATA_STATE;

typedef struct {
  IOCFG_IDLE_STATE idleState; ///< Whether the pin is high or low when idling
  IOCFG_POLARITY polarity; ///< Whether the pin output bits are flipped
  IOCFG_DIFFERENTIAL differential; ///< If the differential pair is setup
  IOCFG_DATA_STATE dataState; ///< Whether the pin is an input, output, or clock
} IOCFG;


IOCFG IO_Pins[NUM_IO_PINS];
uint8_t IOPinsInitialized;

IOM_ERROR InitIOPins();

IOM_ERROR SetIOPinIdleState(size_t pinNumber, IOCFG_IDLE_STATE idleState);
IOM_ERROR SetIOPinPolarity(size_t pinNumber, IOCFG_POLARITY polarity);
IOM_ERROR EnableDifferentialMode(size_t pinNumber);
IOM_ERROR DisableDifferentialMode(size_t pinNumber);
IOM_ERROR SetIOPinDataState(size_t pinNumber, IOCFG_DATA_STATE dataState);
IOM_ERROR GetDataState(uint8_t pinState, IOCFG_DATA_STATE* pDataState);

uint8_t GetIOPinOutputMask(uint8_t pinNumber);
uint8_t GetIOPinOutputPos(uint8_t pinNumber);

IOM_ERROR EnableOutputPin(uint8_t pinNumber);
IOM_ERROR DisableOutputPin(uint8_t pinNumber);

IOM_ERROR EnableClockPin(uint8_t pinNumber);
IOM_ERROR DisableClockPin(uint8_t pinNumber);





#ifdef __cplusplus
}
#endif

#endif
