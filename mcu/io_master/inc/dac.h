#ifndef __IOM_DAC_H
#define __IOM_DAC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"
#include "stm32h7xx_hal.h"

DAC_HandleTypeDef hdac1;
I2C_HandleTypeDef hi2c3;

IOM_ERROR InitDAC(void);

IOM_ERROR InitI2CDAC(void);

void ErrorLight(HAL_StatusTypeDef HalStatus);

IOM_ERROR WriteAllExtDAC(float Vout);

IOM_ERROR WriteExtDAC(uint8_t channel, float Vout);

IOM_ERROR WriteRegExtDAC(IOM_REGISTER register, uint8_t channel, uint16_t Vout);

uint8_t ReadExtDAC(IOM_REGISTER register, IOM_REGISTER level, uint8_t channel);

IOM_ERROR WriteMcuDAC(uint8_t channel, float Vout);

IOM_ERROR WriteRawMcuDAC(uint8_t channel, uint16_t dacVal);



#ifdef __cplusplus
}
#endif
#endif