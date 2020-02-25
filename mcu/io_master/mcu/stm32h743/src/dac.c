  #include "dac.h"
  #include "mcu_conf.h"
  #include "core.h"
  #include "stm32h743xx.h"
  #include "stm32h7xx_hal.h"

  DAC_HandleTypeDef hdac1;

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
      return IOM_ERROR_INVALID; //TODO put a better error here
    }
    return IOM_OK;
  }


  static const uint8_t EXT_DAC_ADDR = 0b1100000 << 1; // Default address for MCP4728 DAC
  //TODO: Implement multiple Dac Addresses for VH Dac and VL Dac

  static const uint8_t EXT_DAC_ADDR_UPDATE = 0x00; // General Call Commands address for MCP4728 DAC
  static const uint8_t bufUpdate = 0x08;//General Call Software Update
  static const uint8_t bufVRef = 0x80;//Select VRef Bit
  
  uint8_t Hbuf[8];//Buffer for Fast Write Command to VH DAC  
  uint8_t Lbuf[8];//Buffer for Fast Write Command to VL DAC
  uint8_t buf[8];//Buffer //todo Rename this

  void ErrorLight(HAL_StatusTypeDef HalStatus)
  {
    if (HalStatus != HAL_OK ) 
    {
      HAL_GPIO_WritePin(STATUS_R_GPIO_Port, STATUS_R_Pin, GPIO_PIN_SET);// Set LD1 HI
      while(1){}
    }
  }
  //TESTING
  IOM_ERROR WriteAllExtDAC(float Vout)
  {
//    HAL_StatusTypeDef ret;
    uint16_t DAC_VALUE = round(136.5 * (15 - Vout));//((2^12 - 1) / 30) * (15 - Vout)

    //Write DAC_Value into all 4 channels
    for(uint8_t i = 0;i < 8; i+=2)
    {
          buf[i] = (DAC_VALUE>>8) & 0x0F;
          buf[i+1] = DAC_VALUE;
    }
    //Set VRef
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &bufVRef, 1, HAL_MAX_DELAY);
    //errorLight(ret);

    //Write Channel Registers
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &buf[0], 8, HAL_MAX_DELAY);
    //errorLight(ret);

    //Update Voltages
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR_UPDATE, &bufUpdate, 1, HAL_MAX_DELAY);
    //errorLight(ret);
    return IOM_OK;
  }
  //TESTING
  IOM_ERROR WriteExtDAC(uint8_t channel, float Vout)
  {
    //HAL_StatusTypeDef ret;

    //uint16_t DAC_VALUE = round(136.5 * (15 - Vout));//((2^12 - 1) / 30) * (15 - Vout)
    //buf[2*channel-2] = (DAC_VALUE>>8) & 0x0F;
    //buf[2*channel-1] = DAC_VALUE;
        
    //Set VRef
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &bufVRef, 1, HAL_MAX_DELAY);
    //errorLight(ret);

    //Write Channel Registers
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &buf[0], 8, HAL_MAX_DELAY);
    //errorLight(ret);

    //Update Voltages
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR_UPDATE, &bufUpdate, 1, HAL_MAX_DELAY);
    //errorLight(ret);
    return IOM_OK;
  }

  IOM_ERROR WriteRegExtDAC(IOM_REGISTER reg, uint8_t channel, uint16_t Vout)
  {
    HAL_StatusTypeDef ret;
    uint8_t *buf;
    switch(reg) {
      case IOM_REGISTER_HIGH:
        buf = (uint8_t*) &Hbuf;
        break;
      case IOM_REGISTER_LOW:
        buf = (uint8_t*) &Lbuf;
        break;
      default:
        return IOM_ERROR_INVALID;
    }

    buf[2*channel-2] = (Vout>>8) & 0x0F;
    buf[2*channel-1] = Vout;
        
    //Set VRef //needs moved to startup
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, &bufVRef, 1, HAL_MAX_DELAY);
    //errorLight(ret);

    //Write Channel Registers
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR, buf, 8, HAL_MAX_DELAY);
    //errorLight(ret);

    //Update Voltages
    //ret = HAL_I2C_Master_Transmit(&hi2c2, EXT_DAC_ADDR_UPDATE, &bufUpdate, 1, HAL_MAX_DELAY);
    //errorLight(ret);
    return IOM_OK;
  }
  
  uint8_t ReadExtDac(IOM_REGISTER reg, IOM_REGISTER level, uint8_t channel)
  {
    uint8_t *buf;
    switch(reg) {
      case IOM_REGISTER_HIGH:
        buf = (uint8_t*) &Hbuf;
        break;
      case IOM_REGISTER_LOW:
        buf = (uint8_t*) &Lbuf;
        break;
      default:
        return 0;
    }

    switch(level) {
      case IOM_REGISTER_HIGH:
        return buf[2*channel-1];
      case IOM_REGISTER_LOW:
        return buf[2*channel-2];
      default:
        return 0;
    }
  }

  //TESTING
  IOM_ERROR WriteMcuDAC(uint8_t channel, float Vout)
  {
    if(channel == 1)
    {
      channel = DAC1_CHANNEL_1;
    }
    else if(channel == 2)
    {
      channel = DAC1_CHANNEL_2;
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
  

