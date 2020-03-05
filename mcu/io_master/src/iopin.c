#include "iopin.h"
#include "stm32h7xx_hal.h"
#include "stm32h743xx.h"

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
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (dataState == IOCFG_DATA_STATE_OUTPUT) {
    switch (pinNumber) {
      case 1:
        HAL_GPIO_DeInit(IO_1_OUT_GPIO_Port, IO_1_OUT_Pin);
        GPIO_InitStruct.Pin = IO_1_OUT_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(IO_1_OUT_GPIO_Port, &GPIO_InitStruct);
        break;
      case 2:
        HAL_GPIO_DeInit(IO_2_OUT_GPIO_Port, IO_2_OUT_Pin);
        GPIO_InitStruct.Pin = IO_2_OUT_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(IO_2_OUT_GPIO_Port, &GPIO_InitStruct);
        break;
      case 3:
        HAL_GPIO_DeInit(IO_3_OUT_GPIO_Port, IO_3_OUT_Pin);
        GPIO_InitStruct.Pin = IO_3_OUT_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(IO_3_OUT_GPIO_Port, &GPIO_InitStruct);
        break;
      case 4:
        HAL_GPIO_DeInit(IO_4_OUT_GPIO_Port, IO_4_OUT_Pin);
        GPIO_InitStruct.Pin = IO_4_OUT_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(IO_4_OUT_GPIO_Port, &GPIO_InitStruct);
        break;
      default:
        return IOM_ERROR_INVALID;
    }
  }
  return IOM_OK;
}

IOM_ERROR GetDataState(uint8_t pinState, IOCFG_DATA_STATE* pDataState) {
  if (pDataState == NULL) {
    return IOM_ERROR_NULL_POINTER;
  }
  switch(pinState) {
    case 0b00:
      *pDataState = IOCFG_DATA_STATE_DISABLED; 
      break;
    case 0b01:
      *pDataState = IOCFG_DATA_STATE_INPUT;
      break;
    case 0b10:
      *pDataState = IOCFG_DATA_STATE_OUTPUT;
      break;
    case 0b11:
      *pDataState = IOCFG_DATA_STATE_CLOCK;
      break;
    default:
      return IOM_ERROR_INVALID;
  }

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

