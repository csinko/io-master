#ifndef __IOM_DAC_H
#define __IOM_DAC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "core.h"
#include "stm32h7xx_hal.h"

#define IO_DAC_CH_1_2_ADDR      (uint8_t) 0b11000000 
#define IO_DAC_CH_1_2_DIFF_ADDR (uint8_t) 0b11000010
#define IO_DAC_CH_3_4_ADDR      (uint8_t) 0b11000100
#define IO_DAC_CH_3_4_DIFF_ADDR (uint8_t) 0b11000110
#define IO_DAC_UPDATE_ADDR      (uint8_t) 0x00 //General Call Commands address for MCP4728 DAC

uint8_t IO_DAC_UPDATE_BUF; //General Call Software Update
uint8_t IO_DAC_VREF_BUF; //Select VRef Bit

DAC_HandleTypeDef hdac1;
I2C_HandleTypeDef hi2c3;    

IOM_ERROR InitDAC(void);

IOM_ERROR InitI2CDAC(void);

void ErrorLight(HAL_StatusTypeDef HalStatus);

IOM_ERROR WriteExtDAC(IOM_REGISTER register, uint8_t channel, float Vout);

IOM_ERROR WriteRegExtDAC(IOM_REGISTER register, uint8_t channel, uint16_t Vout);

//returns the value most recently set for VH/VL on a given channel
//register: VH or VL
//channel: channel number (1-4)
uint16_t ReadExtDAC(IOM_REGISTER register, uint8_t channel);

IOM_ERROR WriteMcuDAC(uint8_t channel, float Vout);

IOM_ERROR WriteRawMcuDAC(uint8_t channel, uint16_t dacVal);

#ifdef __cplusplus
}
#endif
#endif