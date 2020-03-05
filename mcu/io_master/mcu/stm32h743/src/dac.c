  #include "dac.h"
  #include "mcu_conf.h"
  #include "core.h"
  #include "stm32h743xx.h"
  #include "stm32h7xx_hal.h"

  DAC_HandleTypeDef hdac1 = {0};
  I2C_HandleTypeDef hi2c3 = {0};
  
  uint8_t IO_DAC_UPDATE_BUF = 0x08; //General Call Software Update
  uint8_t IO_DAC_VREF_BUF = 0x80; //Select VRef Bit
  
  //CH1 VH, CH1 VL, CH2 VH, CH2 VL ...
  uint8_t io_dac_buf[16] = {0}; //Buffer for all VH/VL values

  IOM_ERROR InitDAC(void)
  {
    DAC_ChannelConfTypeDef sConfig = {0};

    /** DAC Initialization 
    */
    hdac1.Instance = DAC1;
    if (HAL_DAC_Init(&hdac1) != HAL_OK)
    {
      return IOM_ERROR_INVALID; //TODO put a better error here
    }
    /** DAC channel OUT1 config 
    */
    sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
    sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
    sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
    sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
    if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }
    return IOM_OK;
  }

  IOM_ERROR InitI2CDAC(void) {
    __HAL_RCC_I2C3_CLK_ENABLE();
    //TODO confirm this configuration is correct
    hi2c3.Instance              = I2C3;
    hi2c3.Init.Timing           = 0x10707EBE;
    hi2c3.Init.OwnAddress1      = 0; //TODO populate me with the correct value
    hi2c3.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2      = 0;
    hi2c3.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;  
    
    if(HAL_I2C_Init(&hi2c3) != HAL_OK)
    {
      return IOM_ERROR_INTERFACE;
    }

    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_DISABLE) != HAL_OK) {
      return IOM_ERROR_INTERFACE;
    }

    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK) {
      return IOM_ERROR_INTERFACE;
    }

    if(HAL_I2C_Master_Transmit(&hi2c3, IO_DAC_CH_1_2_ADDR, &IO_DAC_VREF_BUF, 1, HAL_MAX_DELAY) != HAL_OK) {
      return IOM_ERROR_INTERFACE;
    }

    if(HAL_I2C_Master_Transmit(&hi2c3, IO_DAC_CH_3_4_ADDR, &IO_DAC_VREF_BUF, 1, HAL_MAX_DELAY) != HAL_OK) {
      return IOM_ERROR_INTERFACE;
    }

    return IOM_OK; 
  }

  void ErrorLight(HAL_StatusTypeDef HalStatus)
  {
    if (HalStatus != HAL_OK ) 
    {
      HAL_GPIO_WritePin(STATUS_R_GPIO_Port, STATUS_R_Pin, GPIO_PIN_SET);// Set LD1 HI
      while(1){}
    }
  }

  //TESTING
  IOM_ERROR WriteExtDAC(IOM_REGISTER reg, uint8_t channel, float Vout)
  {
    //HAL_StatusTypeDef ret;
    uint16_t dacVal = round(136.5 * (15 - Vout));//((2^12 - 1) / 30) * (15 - Vout)
    io_dac_buf[(channel - 1) * 4 + 2*reg] = (dacVal >> 8) & 0x00FF;
    io_dac_buf[(channel - 1) * 4 + 2*reg + 1] = dacVal & 0x00FF;

    uint8_t *buf;
    uint16_t addr;
    switch(channel) {
      case 1:
      case 2:
        buf = io_dac_buf;
        addr = IO_DAC_CH_1_2_ADDR;
        break;
      case 3:
      case 4:
        buf = io_dac_buf + 8; //+8 because 2 channels at same time
        addr = IO_DAC_CH_3_4_ADDR;
        break;
      default:
        return IOM_ERROR_INVALID;
    }
        

    //Write Channel Registers
    HAL_I2C_Master_Transmit(&hi2c3, addr, buf, 8, HAL_MAX_DELAY);

    //Update Voltages
    HAL_I2C_Master_Transmit(&hi2c3, IO_DAC_UPDATE_ADDR, &IO_DAC_UPDATE_BUF, 1, HAL_MAX_DELAY);
    return IOM_OK;
  }

  IOM_ERROR WriteRegExtDAC(IOM_REGISTER reg, uint8_t channel, uint16_t Vout)
  {
    //HAL_StatusTypeDef ret;
    io_dac_buf[(channel - 1) * 4 + 2*reg] = (Vout >> 8) & 0x00FF;
    io_dac_buf[(channel - 1) * 4 + 2*reg + 1] = (Vout) & 0x00FF;

    uint8_t *buf;
    uint16_t addr;
    switch(channel) {
      case 1:
      case 2:
        buf = io_dac_buf;
        addr = IO_DAC_CH_1_2_ADDR;
        break;
      case 3:
      case 4:
        buf = io_dac_buf + 8; //+8 because 2channels at same time
        addr = IO_DAC_CH_3_4_ADDR;
        break;
      default:
        return IOM_ERROR_INVALID;
    }
        

    //Write Channel Registers
    HAL_I2C_Master_Transmit(&hi2c3, addr, buf, 8, HAL_MAX_DELAY);
    //errorLight(ret);

    //Update Voltages
    HAL_I2C_Master_Transmit(&hi2c3, IO_DAC_UPDATE_ADDR, &IO_DAC_UPDATE_BUF, 1, HAL_MAX_DELAY);
    //errorLight(ret);
    return IOM_OK;
  }
  
  uint16_t ReadExtDAC(IOM_REGISTER reg, uint8_t channel)
  {
    return io_dac_buf[(channel - 1) * 2 + reg];
  }

  //TESTING
  //TODO make this work
  IOM_ERROR WriteMCUDAC(uint8_t channel, float Vout)
  {
    if(channel == 1)
    {
      channel = DAC1_CHANNEL_1;
    }
    else if(channel == 2)
    {
      channel = DAC1_CHANNEL_2;
    }
    else {
      return IOM_ERROR_INVALID; //Channel is invalid
    }

    uint16_t DAC_VALUE = round(Vout*4095/3.3);

    //Write Channel Register
    HAL_DAC_SetValue(&hdac1, channel, DAC_ALIGN_12B_R, DAC_VALUE);

    return IOM_OK;
  }

  //channel: expects 1 or 2
  //dacVal: expects the 12-bit bitpattern scaled for 3.3V Max
  IOM_ERROR WriteRawMcuDac(uint8_t channel, uint16_t dacVal)
  {
    if(channel == 1)
    {
      channel = DAC1_CHANNEL_1;
    }
    else if(channel == 2) 
    {
      //currently only using channel 1
      channel = DAC1_CHANNEL_2;
    }

    //Write Channel Register
    HAL_DAC_SetValue(&hdac1, channel, DAC_ALIGN_12B_R, dacVal);

    return IOM_OK;
  }
  

