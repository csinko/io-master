#include "iopin.h"

#define CHECK_PIN(pin) if ((pin == 0) || (pin > NUM_IO_PINS)) \
                                  return IOM_ERROR_INVALID

IOM_ERROR SetIOPinIdleState(size_t pinNumber, IOCFG_IDLE_STATE idleState) {
  CHECK_PIN(pinNumber);
  IO_Pins[pinNumber-1].idleState =  idleState;
  return IOM_OK;
}

IOM_ERROR SetIOPinPolarity(size_t pinNumber, IOCFG_POLARITY polarity) {
  CHECK_PIN(pinNumber);
  IO_Pins[pinNumber-1].polarity = polarity;
  return IOM_OK;
}

IOM_ERROR EnableDifferentialMode(size_t pinNumber) {
  CHECK_PIN(pinNumber);
  IO_Pins[pinNumber-1].differential = IOCFG_DIFFERENTIAL_ENABLED;
  return IOM_OK;
}

IOM_ERROR DisableDifferentialMode(size_t pinNumber) {
  CHECK_PIN(pinNumber);
  IO_Pins[pinNumber-1].differential = IOCFG_DIFFERENTIAL_DISABLED;
  return IOM_OK;
}

IOM_ERROR SetIOPinDataState(size_t pinNumber, IOCFG_DATA_STATE dataState) {
  CHECK_PIN(pinNumber);
  IO_Pins[pinNumber-1].dataState = dataState;
  return IOM_OK;
}

uint8_t GetIOPinOutputMask(uint8_t pinNumber) {
  switch(pinNumber) {
    case 1:
      return (IO_PIN_1_OUTPUT + 1) % 8;
    case 2:
      return (IO_PIN_2_OUTPUT + 1) % 8;
    case 3:
      return (IO_PIN_3_OUTPUT + 1) % 8;
    case 4:
      return (IO_PIN_4_OUTPUT + 1) % 8;
    default:
      return 0;
  }
}

uint8_t GetIOPinOutputPos(uint8_t pinNumber) {
  switch(pinNumber) {
    case 1:
      return (1 << IO_PIN_1_OUTPUT);
    case 2:
      return (1 << IO_PIN_2_OUTPUT);
    case 3:
      return (1 << IO_PIN_3_OUTPUT);
    case 4:
      return (1 << IO_PIN_4_OUTPUT);
    default:
      return 0;
  }
}

