  

  static const uint8_t EXT_DAC_ADDR = 0b1100000 << 1; // Default address for MCP4728 DAC
  //TODO: Implement multiple Dac Addresses for VH Dac and VL Dac

  static const uint8_t EXT_DAC_ADDR_UPDATE = 0x00; // General Call Commands address for MCP4728 DAC
  static const uint8_t bufUpdate = 0x08;//General Call Software Update
  static const uint8_t bufVRef = 0x80;//Select VRef Bit
  
  uint8_t Hbuf[8];//Buffer for Fast Write Command to VH DAC  
  uint8_t Lbuf[8];//Buffer for Fast Write Command to VL DAC

  void errorLight(HAL_StatusTypeDef HalStatus)
  {
    if (HalStatus != HAL_OK ) 
    {
      HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);// Set LD1 HI
      while(1){}
    }
  }
  //TESTING
  void writeAllExtDac(float Vout)
  {
    HAL_StatusTypeDef ret;
    uint16_t DAC_VALUE = round(136.5 * (15 - Vout));//((2^12 - 1) / 30) * (15 - Vout)

    //Write DAC_Value into all 4 channels
    for(uint8_t i = 0;i < 8; i+=2)
    {
          buf[i] = (DAC_VALUE>>8) & 0x0F;
          buf[i+1] = DAC_VALUE;
    }
    //Set VRef
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &bufVRef, 1, HAL_MAX_DELAY);
    errorLight(ret);

    //Write Channel Registers
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &buf[0], 8, HAL_MAX_DELAY);
    errorLight(ret);

    //Update Voltages
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR_UPDATE, &bufUpdate, 1, HAL_MAX_DELAY);
    errorLight(ret);
  }
  //TESTING
  void writeExtDac(uint8_t channel, float Vout)
  {
    HAL_StatusTypeDef ret;

    uint16_t DAC_VALUE = round(136.5 * (15 - Vout));//((2^12 - 1) / 30) * (15 - Vout)
    buf[2*channel-2] = (DAC_VALUE>>8) & 0x0F;
    buf[2*channel-1] = DAC_VALUE;
        
    //Set VRef
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &bufVRef, 1, HAL_MAX_DELAY);
    errorLight(ret);

    //Write Channel Registers
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &buf[0], 8, HAL_MAX_DELAY);
    errorLight(ret);

    //Update Voltages
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR_UPDATE, &bufUpdate, 1, HAL_MAX_DELAY);
    errorLight(ret);
  }

  void writeExtDac(bool isVH, uint8_t channel, uint16_t Vout)
  {
    HAL_StatusTypeDef ret;
    uint8_t *buf = isVH ? &Hbuf : &Lbuf;

    buf[2*channel-2] = (Vout>>8) & 0x0F;
    buf[2*channel-1] = Vout;
        
    //Set VRef //needs moved to startup
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &bufVRef, 1, HAL_MAX_DELAY);
    errorLight(ret);

    //Write Channel Registers
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, buf, 8, HAL_MAX_DELAY);
    errorLight(ret);

    //Update Voltages
    ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR_UPDATE, &bufUpdate, 1, HAL_MAX_DELAY);
    errorLight(ret);
  }
  
  uint8_t readExtDac(bool isVH, bool isUpper, uint8_t channel)
  {
    uint8_t *buf = isVH ? &Hbuf : &Lbuf;

    if(isUpper)
    {
      return buf[2*channel-1];
    }
    //else not Upper
    return buf[2*channel-2];
  }

  //TESTING
  void writeMcuDac(uint channel, float Vout)
  {
    if(channel == 1)
    {
      channel = DAC1_CHANNEL_1;
    }
    elseif(channel == 2)
    {
      channel = DAC1_CHANNEL_2;
    }

    uint16_t DAC_VALUE = round(Vout*4095/3.3);

    //Write Channel Register
    HAL_DAC_SetValue(&hdac1, channel, DAC_ALIGN_12B_R, DAC_VALUE);
  }

  //channel: expects 1 or 2
  //dacVal: expects the 12-bit bitpattern scaled for 3.3V Max
  void writeMcuDac(uint channel, uint16_t dacVal)
  {
    if(channel == 1)
    {
      channel = DAC1_CHANNEL_1;
    }
    elseif(channel == 2)
    {
      //currently only using channel 1
      channel = DAC1_CHANNEL_2;
    }

    //Write Channel Register
    HAL_DAC_SetValue(&hdac1, channel, DAC_ALIGN_12B_R, dacVal);
  }
  

