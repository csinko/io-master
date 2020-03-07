#include "iopin.h"
#include "stm32h7xx_hal.h"
#include "stm32h743xx.h"
#include "timer.h"

#define CHECK_PIN(pin) if ((pin == 0) || (pin > NUM_IO_PINS)) \
                                  return IOM_ERROR_INVALID

IOCFG IO_Pins[NUM_IO_PINS] = {0};
uint8_t IOPinsInitialized = 0;

IOM_ERROR InitIOPins() {
  if (IOPinsInitialized != 0) {
    return IOM_ERROR_NOT_ALLOWED;
  }
  for (int i = 0; i < NUM_IO_PINS; i++) {
    IO_Pins[i].dataState = IOCFG_DATA_STATE_DISABLED;
    IO_Pins[i].polarity = IOCFG_POLARITY_FALSE;
    IO_Pins[i].idleState = IOCFG_IDLE_STATE_LOW;
    IO_Pins[i].differential = IOCFG_DIFFERENTIAL_DISABLED;
  }
  return IOM_OK;
}

IOM_ERROR SetIOPinIdleState(size_t pinNumber, IOCFG_IDLE_STATE idleState) {
  CHECK_PIN(pinNumber);
  if (idleState == IO_Pins[pinNumber-1].idleState) {
    //Nothing to do, Idle state already set
    return IOM_OK;
  }
  uint16_t ioPin = 0;
  switch(pinNumber) {
    case 1:
      ioPin = IO_1_OUT_Pin;
      break;
    case 2:
      ioPin = IO_2_OUT_Pin;
      break;
    case 3:
      ioPin = IO_3_OUT_Pin;
      break;
    case 4:
      ioPin = IO_4_OUT_Pin;
      break;
  }
  switch(idleState) {
    case IOCFG_IDLE_STATE_HIGH:
      IO_PIN_GPIO_OUTPUT_PORT->ODR |= (ioPin << 1);
      break;
    case IOCFG_IDLE_STATE_LOW:
      IO_PIN_GPIO_OUTPUT_PORT->ODR &= ~((ioPin << 1));
      break;
    case IOCFG_IDLE_STATE_TRISTATE:
      break;
  }
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
  //If the pin already was configured for this, return IOM_OK
  if (IO_Pins[pinNumber-1].dataState == dataState) {
    return IOM_OK;
  }
  IOCFG_DATA_STATE lastState = IO_Pins[pinNumber-1].dataState;
  IO_Pins[pinNumber-1].dataState = dataState;
  switch(dataState) {
    case IOCFG_DATA_STATE_OUTPUT:
    case IOCFG_DATA_STATE_CS:
      if (lastState == IOCFG_DATA_STATE_CLOCK) {
        DisableClockPin(pinNumber);
      }
      EnableOutputPin(pinNumber);
      break;

    case IOCFG_DATA_STATE_CLOCK:
      if (lastState == IOCFG_DATA_STATE_OUTPUT ||
          lastState == IOCFG_DATA_STATE_CS) {
            DisableOutputPin(pinNumber);
      }
      EnableClockPin(pinNumber);
      break;
    case IOCFG_DATA_STATE_INPUT:
    case IOCFG_DATA_STATE_DISABLED:
      if (lastState == IOCFG_DATA_STATE_CLOCK) {
        DisableClockPin(pinNumber);
      } else {
        DisableOutputPin(pinNumber);
      }
      break;
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

//TODO, this won't work if it is past GPIO7
uint8_t GetIOPinOutputMask(uint8_t pinNumber) {
  switch(pinNumber) {
    case 1:
      return IO_1_OUT_Pin;
    case 2:
      return IO_2_OUT_Pin;
    case 3:
      return IO_3_OUT_Pin;
    case 4:
      return IO_4_OUT_Pin;
    default:
      return 0;
  }
}

uint8_t GetIOPinOutputPos(uint8_t pinNumber) {
  switch(pinNumber) {
    case 1:
      return IO_PIN_1_OUTPUT;
    case 2:
      return IO_PIN_2_OUTPUT;
    case 3:
      return IO_PIN_3_OUTPUT;
    case 4:
      return IO_PIN_4_OUTPUT;
    default:
      return 0;
  }
}

IOM_ERROR EnableOutputPin(uint8_t pinNumber) {
  CHECK_PIN(pinNumber);
  GPIO_TypeDef* outPort = 0;
  uint16_t outPin = 0;
  switch(pinNumber) {
    case 1:
      outPort = IO_1_OUT_GPIO_Port;
      outPin = IO_1_OUT_Pin;
      break;
    case 2:
      outPort = IO_2_OUT_GPIO_Port;
      outPin = IO_2_OUT_Pin;
      break;
    case 3:
      outPort = IO_3_OUT_GPIO_Port;
      outPin = IO_3_OUT_Pin;
      break;
    case 4:
      outPort = IO_4_OUT_GPIO_Port;
      outPin = IO_4_OUT_Pin;
  }
  HAL_GPIO_DeInit(outPort, outPin);
  switch(IO_Pins[pinNumber].idleState) {
    case IOCFG_IDLE_STATE_HIGH:
      IO_PIN_GPIO_OUTPUT_PORT->ODR |= (outPin << 1);
      break;
    case IOCFG_IDLE_STATE_LOW:
      IO_PIN_GPIO_OUTPUT_PORT->ODR &= ~((outPin << 1));
      break;
    case IOCFG_IDLE_STATE_TRISTATE:
      break;
  }
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = outPin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(outPort, &GPIO_InitStruct);
  return IOM_OK;

}

IOM_ERROR DisableOutputPin(uint8_t pinNumber) {
  CHECK_PIN(pinNumber);
  GPIO_TypeDef* outPort = 0;
  uint16_t outPin = 0;
  switch(pinNumber) {
    case 1:
      outPort = IO_1_OUT_GPIO_Port;
      outPin = IO_1_OUT_Pin;
      break;
    case 2:
      outPort = IO_2_OUT_GPIO_Port;
      outPin = IO_2_OUT_Pin;
      break;
    case 3:
      outPort = IO_3_OUT_GPIO_Port;
      outPin = IO_3_OUT_Pin;
      break;
    case 4:
      outPort = IO_4_OUT_GPIO_Port;
      outPin = IO_4_OUT_Pin;
  }
  HAL_GPIO_DeInit(outPort, outPin);
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = outPin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(outPort, &GPIO_InitStruct);
  return IOM_OK;

}

IOM_ERROR EnableClockPin(uint8_t pinNumber) {
  CHECK_PIN(pinNumber);
  GPIO_TypeDef* clkPort = 0;
  uint16_t clkPin = 0;
  uint32_t alternate = 0;
  TIM_TypeDef* pTimer = 0;
  uint32_t channel = 0;
  switch(pinNumber) {
    case 1:
      clkPort = IO_1_CLK_GPIO_Port;
      clkPin = IO_1_CLK_Pin;
      alternate = GPIO_AF1_TIM2;
      pTimer = TIM2;
      channel = TIM_CCER_CC1E;
      break;
    case 2:
      clkPort = IO_2_CLK_GPIO_Port;
      clkPin = IO_2_CLK_Pin;
      alternate = GPIO_AF2_TIM5;
      pTimer = TIM5;
      channel = TIM_CCER_CC2E;

      break;
    case 3:
      clkPort = IO_3_CLK_GPIO_Port;
      clkPin = IO_3_CLK_Pin;
      alternate = GPIO_AF4_TIM15;
      pTimer = TIM15;
      channel = TIM_CCER_CC1E;
      break;
    case 4:
      clkPort = IO_4_CLK_GPIO_Port;
      clkPin = IO_4_CLK_Pin;
      alternate = GPIO_AF2_TIM3;
      pTimer = TIM3;
      channel = TIM_CCER_CC1E;
      break;
  }

  pTimer->CCER |= channel;
  pTimer->BDTR |= TIM_BDTR_MOE;
  pTimer->CNT = timerPeriod; //TODO, dynamically change this so it is always correct
  pTimer->CR1 |= TIM_CR1_CEN;
  HAL_GPIO_DeInit(clkPort, clkPin);
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = clkPin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = alternate;
  HAL_GPIO_Init(clkPort, &GPIO_InitStruct);

  return IOM_OK;
}

IOM_ERROR DisableClockPin(uint8_t pinNumber) {
  CHECK_PIN(pinNumber);
  GPIO_TypeDef* clkPort = 0;
  uint16_t clkPin = 0;
  switch(pinNumber) {
    case 1:
      clkPort = IO_1_CLK_GPIO_Port;
      clkPin = IO_1_CLK_Pin;
      break;
    case 2:
      clkPort = IO_2_CLK_GPIO_Port;
      clkPin = IO_2_CLK_Pin;
      break;
    case 3:
      clkPort = IO_3_CLK_GPIO_Port;
      clkPin = IO_3_CLK_Pin;
      break;
    case 4:
      clkPort = IO_4_CLK_GPIO_Port;
      clkPin = IO_4_CLK_Pin;
      break;
  }
  HAL_GPIO_DeInit(clkPort, clkPin);
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = clkPin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(clkPort, &GPIO_InitStruct);

  return IOM_OK;

}

