/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

DAC_HandleTypeDef hdac1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DAC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

  uint8_t buf[8];// Buffer for Fast Write Command
  static const uint8_t EXT_DAC_ADDR = 0b1100000 << 1; // Default address for MCP4728 DAC
  static const uint8_t EXT_DAC_ADDR_UPDATE = 0x00; // General Call Commands address for MCP4728 DAC
  static const uint8_t bufUpdate = 0x08;//General Call Software Update
  static const uint8_t bufVRef = 0x80;//Select VRef Bit
  void errorLight(HAL_StatusTypeDef HalStatus)
  {
    if (HalStatus != HAL_OK ) 
    {
      HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);// Set LD1 HI
      while(1){}
    }
  }
  void writeAllExtDac(float Vout)
  {
    HAL_StatusTypeDef ret;
    uint16_t DAC_VALUE = round(85.3125 * (24 - Vout));//((2^12 - 1) / 48) * (24 - Vout)

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
  void writeExtDac(uint8_t channel, float Vout)
  {
    HAL_StatusTypeDef ret;

    uint16_t DAC_VALUE = round(85.3125 * (24 - Vout));//((2^12 - 1) / 48) * (24 - Vout)
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


  void setClkFreq(uint freq)
  {
    float VDac = .585-((freq-100000)*.585)/900000;
    writeMcuDac(2, VDac);
  }

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


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC1_Init();
  /* USER CODE BEGIN 2 */
  //writeAllExtDac(0);
  HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1);
  HAL_DAC_Start(&hdac1, DAC1_CHANNEL_2);
  unsigned int num1 = 0, num2 = 2048;
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    //HAL_GPIO_TogglePin(GPIOA, PA4_Pin);
    //HAL_GPIO_TogglePin(GPIOA, PA5_Pin);

    //hdac1.Instance->DHR12R1 = num1;
    //hdac1.Instance->DHR12R2 = num2;
    
    
    HAL_GPIO_TogglePin(GPIOB, LD1_Pin);//Toggle LD1
    HAL_GPIO_TogglePin(GPIOG, PG2_Pin);
    HAL_GPIO_TogglePin(GPIOG, PG3_Pin);
    HAL_GPIO_TogglePin(GPIOD, PD2_Pin);
    HAL_GPIO_TogglePin(GPIOC, PC12_Pin);
    HAL_Delay(3);
    /*
    HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
    HAL_GPIO_TogglePin(GPIOG, PG2_Pin);
    HAL_GPIO_TogglePin(GPIOG, PG3_Pin);
    HAL_GPIO_TogglePin(GPIOD, PD2_Pin);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
    HAL_GPIO_TogglePin(GPIOG, PG2_Pin);
    HAL_GPIO_TogglePin(GPIOG, PG3_Pin);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
    HAL_GPIO_TogglePin(GPIOG, PG2_Pin);
    HAL_Delay(100); */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable 
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 5;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */
  /** DAC Initialization 
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
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
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, IO_7_8_DIFF_Pin|IO_5_6_TERM_N_Pin|IO_7_PU_Pin|IO_8_PU_Pin 
                          |IO_7_8_TERM_N_Pin|IO_4_PD_N_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, IO_5_6_DIFF_Pin|IO_7_PD_N_Pin|IO_8_PD_N_Pin|IO_3_4_TERM_N_Pin 
                          |IO_3_4_DIFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, STATUS_R_Pin|STATUS_G_Pin|STATUS_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(IO_6_PU_GPIO_Port, IO_6_PU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, IO_6_PD_N_Pin|IO_1_PU_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, IO_5_PU_Pin|IO_1_2_DIFF_Pin|IO_2_PD_N_Pin|IO_3_PU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, IO_5_PD_N_Pin|IO_1_2_TERM_N_Pin|IO_2_PU_Pin|IO_3_PD_N_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, IO_1_PD_N_Pin|IO_4_PU_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, IO_1_TRIS_N_Pin|IO_2_TRIS_N_Pin|IO_3_TRIS_N_Pin|IO_4_TRIS_N_Pin 
                          |IO_5_TRIS_N_Pin|IO_6_TRIS_N_Pin|IO_7_TRIS_N_Pin|IO_8_TRIS_N_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, IO_1_OUTD0_Pin|IO_2_OUTD1_Pin|IO_3_OUTD2_Pin|IO_4_OUTD3_Pin 
                          |IO_5_OUT_Pin|IO_6_OUT_Pin|IO_7_OUT_Pin|IO_8_OUTD7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : IO_7_8_DIFF_Pin IO_5_6_DIFF_Pin IO_5_6_TERM_N_Pin IO_7_PU_Pin 
                           IO_7_PD_N_Pin IO_8_PU_Pin IO_8_PD_N_Pin IO_7_8_TERM_N_Pin 
                           IO_3_4_TERM_N_Pin IO_3_4_DIFF_Pin IO_4_PD_N_Pin */
  GPIO_InitStruct.Pin = IO_7_8_DIFF_Pin|IO_5_6_DIFF_Pin|IO_5_6_TERM_N_Pin|IO_7_PU_Pin 
                          |IO_7_PD_N_Pin|IO_8_PU_Pin|IO_8_PD_N_Pin|IO_7_8_TERM_N_Pin 
                          |IO_3_4_TERM_N_Pin|IO_3_4_DIFF_Pin|IO_4_PD_N_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : STATUS_R_Pin STATUS_G_Pin STATUS_B_Pin */
  GPIO_InitStruct.Pin = STATUS_R_Pin|STATUS_G_Pin|STATUS_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_STP_Pin ULPI_DIR_Pin ULPI_NXT_Pin */
  GPIO_InitStruct.Pin = ULPI_STP_Pin|ULPI_DIR_Pin|ULPI_NXT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_1_OUT_Pin */
  GPIO_InitStruct.Pin = IO_1_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(IO_1_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_2_OUT_Pin */
  GPIO_InitStruct.Pin = IO_2_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
  HAL_GPIO_Init(IO_2_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_3_OUT_Pin */
  GPIO_InitStruct.Pin = IO_3_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_TIM15;
  HAL_GPIO_Init(IO_3_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_D0_Pin ULPI_CK_Pin */
  GPIO_InitStruct.Pin = ULPI_D0_Pin|ULPI_CK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_6_PU_Pin */
  GPIO_InitStruct.Pin = IO_6_PU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IO_6_PU_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_8_OUT_Pin */
  GPIO_InitStruct.Pin = IO_8_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_TIM14;
  HAL_GPIO_Init(IO_8_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ULPI_D1_Pin ULPI_D2_Pin ULPI_D3_Pin ULPI_D4_Pin 
                           ULPI_D5_Pin ULPI_D6_Pin ULPI_D7_Pin */
  GPIO_InitStruct.Pin = ULPI_D1_Pin|ULPI_D2_Pin|ULPI_D3_Pin|ULPI_D4_Pin 
                          |ULPI_D5_Pin|ULPI_D6_Pin|ULPI_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG2_HS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_6_PD_N_Pin IO_1_PU_Pin IO_1_PD_N_Pin IO_4_PU_Pin */
  GPIO_InitStruct.Pin = IO_6_PD_N_Pin|IO_1_PU_Pin|IO_1_PD_N_Pin|IO_4_PU_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_5_PU_Pin IO_5_PD_N_Pin IO_1_2_DIFF_Pin IO_1_2_TERM_N_Pin 
                           IO_2_PD_N_Pin IO_2_PU_Pin IO_3_PU_Pin IO_3_PD_N_Pin */
  GPIO_InitStruct.Pin = IO_5_PU_Pin|IO_5_PD_N_Pin|IO_1_2_DIFF_Pin|IO_1_2_TERM_N_Pin 
                          |IO_2_PD_N_Pin|IO_2_PU_Pin|IO_3_PU_Pin|IO_3_PD_N_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_1_IN_Pin IO_2_IN_Pin IO_3_IN_Pin IO_4_IN_Pin 
                           IO_5_IN_Pin IO_6_IN_Pin IO_7_IN_Pin IO_8_IN_Pin */
  GPIO_InitStruct.Pin = IO_1_IN_Pin|IO_2_IN_Pin|IO_3_IN_Pin|IO_4_IN_Pin 
                          |IO_5_IN_Pin|IO_6_IN_Pin|IO_7_IN_Pin|IO_8_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : IO_1_TRIS_N_Pin IO_2_TRIS_N_Pin IO_3_TRIS_N_Pin IO_4_TRIS_N_Pin 
                           IO_5_TRIS_N_Pin IO_6_TRIS_N_Pin IO_7_TRIS_N_Pin IO_8_TRIS_N_Pin 
                           IO_1_OUTD0_Pin IO_2_OUTD1_Pin IO_3_OUTD2_Pin IO_4_OUTD3_Pin 
                           IO_5_OUT_Pin IO_6_OUT_Pin IO_7_OUT_Pin IO_8_OUTD7_Pin */
  GPIO_InitStruct.Pin = IO_1_TRIS_N_Pin|IO_2_TRIS_N_Pin|IO_3_TRIS_N_Pin|IO_4_TRIS_N_Pin 
                          |IO_5_TRIS_N_Pin|IO_6_TRIS_N_Pin|IO_7_TRIS_N_Pin|IO_8_TRIS_N_Pin 
                          |IO_1_OUTD0_Pin|IO_2_OUTD1_Pin|IO_3_OUTD2_Pin|IO_4_OUTD3_Pin 
                          |IO_5_OUT_Pin|IO_6_OUT_Pin|IO_7_OUT_Pin|IO_8_OUTD7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_4_OUT_Pin */
  GPIO_InitStruct.Pin = IO_4_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  HAL_GPIO_Init(IO_4_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2C_SDA_Pin */
  GPIO_InitStruct.Pin = I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C_SDA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2C_SCL_Pin */
  GPIO_InitStruct.Pin = I2C_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(I2C_SCL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : UART_TXO_Pin UART_RXI_Pin */
  GPIO_InitStruct.Pin = UART_TXO_Pin|UART_RXI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_FS_DM_Pin USB_FS_DP_Pin */
  GPIO_InitStruct.Pin = USB_FS_DM_Pin|USB_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_5_OUTB7_Pin */
  GPIO_InitStruct.Pin = IO_5_OUTB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(IO_5_OUTB7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IO_6_OUTB8_Pin */
  GPIO_InitStruct.Pin = IO_6_OUTB8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
  HAL_GPIO_Init(IO_6_OUTB8_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
