/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define HTS221_ADDRESS 0xBE  
#define HTS221_TEMP_OUT_L 0x2A  // Temperature output register (low byte)
#define HTS221_TEMP_OUT_H 0x2B  // Temperature output register (high byte)
#define HTS221_HUMID_OUT_L 0x28 // Hummidity output register (low byte)
#define HTS221_HUMID_OUT_H 0x29 // Hummidity output register (high byte)
#define HTS221_CTRL_REG1 0x20   // Control register for power on
#define HTS221_STATUS_REG 0x27  // Status register for data readiness

#define LPS22HB_ADDRESS 0xBA 
#define LPS22HB_CTRL_REG1 0x10
#define LPS22HB_PRESS_OUT_XL 0x28
#define LPS22HB_PRESS_OUT_L 0x29
#define LPS22HB_PRESS_OUT_H 0x2A

#define LIS3MDL_ADDRESS 0x3C 
#define LIS3MDL_CTRL_REG1 0x20 // Control register 1 for initialization
#define LIS3MDL_CTRL_REG2 0x21 // Control register 2 for sensitivity adjustment
#define LIS3MDL_CTRL_REG3 0x22 // Control register 3 for power mode
#define LIS3MDL_OUT_X_L 0x28   // X-axis magnetic field data (low byte)
#define LIS3MDL_OUT_X_H 0x29   // X-axis magnetic field data (high byte)
#define LIS3MDL_OUT_Y_L 0x2A   // Y-axis magnetic field data (low byte)
#define LIS3MDL_OUT_Y_H 0x2B   // Y-axis magnetic field data (high byte)
#define LIS3MDL_OUT_Z_L 0x2C   // Z-axis magnetic field data (low byte)
#define LIS3MDL_OUT_Z_H 0x2D   // Z-axis magnetic field data (high byte)

#define LSM6DSL_ADDRESS 0xD4 
#define LSM6DSL_CTRL1_XL 0x10 // Control register for accelerometer
#define LSM6DSL_CTRL2_G  0x11 // Control register for gyroscope
#define LSM6DSL_OUTX_L_XL 0x28 // Accelerometer X-axis low byte
#define LSM6DSL_OUTX_H_XL 0x29 // Accelerometer X-axis high byte
#define LSM6DSL_OUTY_L_XL 0x2A // Accelerometer Y-axis low byte
#define LSM6DSL_OUTY_H_XL 0x2B // Accelerometer Y-axis high byte
#define LSM6DSL_OUTZ_L_XL 0x2C // Accelerometer Z-axis low byte
#define LSM6DSL_OUTZ_H_XL 0x2D // Accelerometer Z-axis high byte
#define LSM6DSL_OUTX_L_G  0x22 // Gyroscope X-axis low byte
#define LSM6DSL_OUTX_H_G  0x23 // Gyroscope X-axis high byte
#define LSM6DSL_OUTY_L_G  0x24 // Gyroscope Y-axis low byte
#define LSM6DSL_OUTY_H_G  0x25 // Gyroscope Y-axis high byte
#define LSM6DSL_OUTZ_L_G  0x26 // Gyroscope Z-axis low byte
#define LSM6DSL_OUTZ_H_G  0x27 // Gyroscope Z-axis high byte

float T0_degC, T1_degC;
int16_t T0_OUT, T1_OUT;
float H0_rH, H1_rH;
int16_t H0_T0_OUT, H1_T0_OUT;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
void HTS221_Init(void);
void LPS22HB_Init(void);
void LIS3MDL_init(void);
void LSM6DSL_init(void);
void HTS221_Read_Calibration(void);
void HTS221_Read_Temperature(void);
void HTS221_Read_Humidity(void);
void LPS22HB_Read_Pressure(void);
void LIS3MDL_Read_Magnetic_Field(void);
void LSM6DSL_Read_Accel_Gyro(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(1000);
  HTS221_Init();
  HTS221_Read_Calibration();
  LPS22HB_Init();        
  LIS3MDL_init();
  LSM6DSL_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    HTS221_Read_Temperature(); 
    HTS221_Read_Humidity();
    LPS22HB_Read_Pressure();
    LIS3MDL_Read_Magnetic_Field();
    LSM6DSL_Read_Accel_Gyro();
    char separator[100];
    snprintf(separator, sizeof(separator), "==================================================================\n");
    HAL_UART_Transmit(&huart1, (uint8_t*)separator, strlen(separator), HAL_MAX_DELAY);
    HAL_Delay(3000);
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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00100D14;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  /* Configure UART pins PA9 (TX) and PA10 (RX) */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;  // AF7 is for UART1
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HTS221_Init(void)
{
  uint8_t ctrl_reg1 = 0x87;  // Power on, BDU enabled, ODR set to 12.5Hz (0b10000111)
  if (HAL_I2C_Mem_Write(&hi2c2, HTS221_ADDRESS, HTS221_CTRL_REG1, 1, &ctrl_reg1, 1, HAL_MAX_DELAY) != HAL_OK) {
    char init_error[] = "HTS221 init failed\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)init_error, strlen(init_error), HAL_MAX_DELAY);
  } else {
    char init_success[] = "HTS221 initialized\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)init_success, strlen(init_success), HAL_MAX_DELAY);
  }
}

void LPS22HB_Init(void)
{
  uint8_t ctrl_reg1 = 0x50;  // Set to active mode, ODR 1 Hz
  if (HAL_I2C_Mem_Write(&hi2c2, LPS22HB_ADDRESS, LPS22HB_CTRL_REG1, 1, &ctrl_reg1, 1, HAL_MAX_DELAY) != HAL_OK) {
    char init_error[] = "LPS22HB init failed\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)init_error, strlen(init_error), HAL_MAX_DELAY);
  } else {
    char init_success[] = "LPS22HB initialized\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)init_success, strlen(init_success), HAL_MAX_DELAY);
  }
}

void LIS3MDL_init(void)
{
  uint8_t config1 = 0x70; // CTRL_REG1: Temperature sensor enabled, ODR = 10 Hz, XY-axis in ultra-high-performance mode
  uint8_t config2 = 0x00; // CTRL_REG2: Set full scale to ±4 gauss
  uint8_t config3 = 0x00; // CTRL_REG3: Continuous-conversion mode

    // Write to control registers
  HAL_I2C_Mem_Write(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_CTRL_REG1, I2C_MEMADD_SIZE_8BIT, &config1, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Write(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_CTRL_REG2, I2C_MEMADD_SIZE_8BIT, &config2, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Write(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_CTRL_REG3, I2C_MEMADD_SIZE_8BIT, &config3, 1, HAL_MAX_DELAY);

  char init_success[] = "LIS3MDL initialized\n";
  HAL_UART_Transmit(&huart1, (uint8_t*)init_success, strlen(init_success), HAL_MAX_DELAY);
}

void LSM6DSL_init(void)
{
  uint8_t config_accel = 0x60; // CTRL1_XL: ODR = 416 Hz, Full-scale = ±2g, BW = 100 Hz
  uint8_t config_gyro = 0x60;  // CTRL2_G: ODR = 416 Hz, Full-scale = 2000 dps

    // Write to accelerometer control register
  HAL_I2C_Mem_Write(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_CTRL1_XL, I2C_MEMADD_SIZE_8BIT, &config_accel, 1, HAL_MAX_DELAY);

    // Write to gyroscope control register
  HAL_I2C_Mem_Write(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_CTRL2_G, I2C_MEMADD_SIZE_8BIT, &config_gyro, 1, HAL_MAX_DELAY);

  char init_success[] = "LSM6DSL initialized\n";
  HAL_UART_Transmit(&huart1, (uint8_t*)init_success, strlen(init_success), HAL_MAX_DELAY);
}

void HTS221_Read_Calibration(void)  
{
  uint8_t T0_degC_x8, T1_degC_x8;
  uint8_t T0_T1_msb;
  uint8_t T0_OUT_L, T0_OUT_H, T1_OUT_L, T1_OUT_H;
  uint8_t H0_rH_x2, H1_rH_x2;
  uint8_t H0_T0_OUT_L, H0_T0_OUT_H, H1_T0_OUT_L, H1_T0_OUT_H;

  // Retrieve temperature calibration values
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x32, 1, &T0_degC_x8, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x33, 1, &T1_degC_x8, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x35, 1, &T0_T1_msb, 1, HAL_MAX_DELAY);

  T0_degC = ((T0_T1_msb & 0x03) << 8 | T0_degC_x8) / 8.0;
  T1_degC = ((T0_T1_msb & 0x0C) << 6 | T1_degC_x8) / 8.0;

  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x3C, 1, &T0_OUT_L, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x3D, 1, &T0_OUT_H, 1, HAL_MAX_DELAY);
  T0_OUT = (int16_t)((T0_OUT_H << 8) | T0_OUT_L);

  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x3E, 1, &T1_OUT_L, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x3F, 1, &T1_OUT_H, 1, HAL_MAX_DELAY);
  T1_OUT = (int16_t)((T1_OUT_H << 8) | T1_OUT_L);

    // Retrieve humidity calibration values
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x30, 1, &H0_rH_x2, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x31, 1, &H1_rH_x2, 1, HAL_MAX_DELAY);

  H0_rH = H0_rH_x2 / 2.0;
  H1_rH = H1_rH_x2 / 2.0;

  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x36, 1, &H0_T0_OUT_L, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x37, 1, &H0_T0_OUT_H, 1, HAL_MAX_DELAY);
  H0_T0_OUT = (int16_t)((H0_T0_OUT_H << 8) | H0_T0_OUT_L);

  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x3A, 1, &H1_T0_OUT_L, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, 0x3B, 1, &H1_T0_OUT_H, 1, HAL_MAX_DELAY);
  H1_T0_OUT = (int16_t)((H1_T0_OUT_H << 8) | H1_T0_OUT_L);

    // Print calibration values
  char calibration_message[100];
  snprintf(calibration_message, sizeof(calibration_message), "T0: %.2f, T1: %.2f, H0: %.2f, H1: %.2f\n",
  T0_degC, T1_degC, H0_rH, H1_rH);
  HAL_UART_Transmit(&huart1, (uint8_t*)calibration_message, strlen(calibration_message), HAL_MAX_DELAY);
}

void HTS221_Read_Temperature(void)
{
  uint8_t status_reg = 0;
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, HTS221_STATUS_REG, 1, &status_reg, 1, HAL_MAX_DELAY);

  if (!(status_reg & 0x01)) {
    char status_message[] = "Temperature data not ready\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)status_message, strlen(status_message), HAL_MAX_DELAY);
    return;
  }

  uint8_t temp_out_l = 0, temp_out_h = 0;
  int16_t temp_raw = 0;

  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, HTS221_TEMP_OUT_L, 1, &temp_out_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, HTS221_TEMP_OUT_H, 1, &temp_out_h, 1, HAL_MAX_DELAY);

  temp_raw = ((int16_t)temp_out_h << 8) | temp_out_l;

    // Apply calibration formula and manual offset
  float temperature_celsius = T0_degC + ((float)(temp_raw - T0_OUT) / (T1_OUT - T0_OUT)) * (T1_degC - T0_degC);
  temperature_celsius -= 5.0;  // Adjust to correct for observed offset

  char debug_message[50];
  snprintf(debug_message, sizeof(debug_message), "Temperature: %.2f degC\n", temperature_celsius);
  HAL_UART_Transmit(&huart1, (uint8_t*)debug_message, strlen(debug_message), HAL_MAX_DELAY);
}

void HTS221_Read_Humidity(void)
{
  uint8_t status_reg = 0;
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, HTS221_STATUS_REG, 1, &status_reg, 1, HAL_MAX_DELAY);

  if (!(status_reg & 0x02)) {
    char status_message[] = "Humidity data not ready\n";
    HAL_UART_Transmit(&huart1, (uint8_t*)status_message, strlen(status_message), HAL_MAX_DELAY);
    return;
  }

  uint8_t hum_out_l = 0, hum_out_h = 0;
  int16_t hum_raw = 0;

  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, HTS221_HUMID_OUT_L, 1, &hum_out_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, HTS221_ADDRESS, HTS221_HUMID_OUT_H, 1, &hum_out_h, 1, HAL_MAX_DELAY);

  hum_raw = ((int16_t)hum_out_h << 8) | hum_out_l;

    // Convert raw humidity to percentage
  float humidity_percentage = H0_rH + ((float)(hum_raw - H0_T0_OUT) * (H1_rH - H0_rH)) / (H1_T0_OUT - H0_T0_OUT);

    // Print the humidity value
  char debug_message[50];
  snprintf(debug_message, sizeof(debug_message), "Humidity: %.2f %%RH\n", humidity_percentage);
  HAL_UART_Transmit(&huart1, (uint8_t*)debug_message, strlen(debug_message), HAL_MAX_DELAY);
}

void LPS22HB_Read_Pressure(void)
{
  uint8_t press_out_xl, press_out_l, press_out_h;
  int32_t press_raw = 0;

  HAL_I2C_Mem_Read(&hi2c2, LPS22HB_ADDRESS, LPS22HB_PRESS_OUT_XL, 1, &press_out_xl, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LPS22HB_ADDRESS, LPS22HB_PRESS_OUT_L, 1, &press_out_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LPS22HB_ADDRESS, LPS22HB_PRESS_OUT_H, 1, &press_out_h, 1, HAL_MAX_DELAY);

    // Combine bytes into 24-bit raw pressure value
  press_raw = ((int32_t)press_out_h << 16) | ((int32_t)press_out_l << 8) | press_out_xl;

    // Convert raw pressure to hPa
  float pressure_hPa = press_raw / 4096.0;

    // Print the pressure value
  char debug_message[50];
  snprintf(debug_message, sizeof(debug_message), "Pressure: %.2f hPa\n", pressure_hPa);
  HAL_UART_Transmit(&huart1, (uint8_t*)debug_message, strlen(debug_message), HAL_MAX_DELAY);
}

void LIS3MDL_Read_Magnetic_Field(void)
{
  uint8_t mag_x_l, mag_x_h, mag_y_l, mag_y_h, mag_z_l, mag_z_h;
  int16_t mag_x, mag_y, mag_z;

    // Read X-axis magnetic field data
  HAL_I2C_Mem_Read(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_OUT_X_L, 1, &mag_x_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_OUT_X_H, 1, &mag_x_h, 1, HAL_MAX_DELAY);

    // Read Y-axis magnetic field data
  HAL_I2C_Mem_Read(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_OUT_Y_L, 1, &mag_y_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_OUT_Y_H, 1, &mag_y_h, 1, HAL_MAX_DELAY);

    // Read Z-axis magnetic field data
  HAL_I2C_Mem_Read(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_OUT_Z_L, 1, &mag_z_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LIS3MDL_ADDRESS, LIS3MDL_OUT_Z_H, 1, &mag_z_h, 1, HAL_MAX_DELAY);

    // Combine high and low bytes
  mag_x = (int16_t)(mag_x_h << 8 | mag_x_l);
  mag_y = (int16_t)(mag_y_h << 8 | mag_y_l);
  mag_z = (int16_t)(mag_z_h << 8 | mag_z_l);

    // Print the magnetic field values
  char debug_message[80];
  snprintf(debug_message, sizeof(debug_message), "Magnetic Field - X: %d, Y: %d, Z: %d\n", mag_x, mag_y, mag_z);
  HAL_UART_Transmit(&huart1, (uint8_t*)debug_message, strlen(debug_message), HAL_MAX_DELAY);
}

void LSM6DSL_Read_Accel_Gyro(void)
{
  uint8_t accel_x_l, accel_x_h, accel_y_l, accel_y_h, accel_z_l, accel_z_h;
  uint8_t gyro_x_l, gyro_x_h, gyro_y_l, gyro_y_h, gyro_z_l, gyro_z_h;
  int16_t accel_x, accel_y, accel_z;
  int16_t gyro_x, gyro_y, gyro_z;

    // Read accelerometer data
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTX_L_XL, 1, &accel_x_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTX_H_XL, 1, &accel_x_h, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTY_L_XL, 1, &accel_y_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTY_H_XL, 1, &accel_y_h, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTZ_L_XL, 1, &accel_z_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTZ_H_XL, 1, &accel_z_h, 1, HAL_MAX_DELAY);

    // Combine high and low bytes
  accel_x = (int16_t)(accel_x_h << 8 | accel_x_l);
  accel_y = (int16_t)(accel_y_h << 8 | accel_y_l);
  accel_z = (int16_t)(accel_z_h << 8 | accel_z_l);

    // Read gyroscope data
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTX_L_G, 1, &gyro_x_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTX_H_G, 1, &gyro_x_h, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTY_L_G, 1, &gyro_y_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTY_H_G, 1, &gyro_y_h, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTZ_L_G, 1, &gyro_z_l, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Read(&hi2c2, LSM6DSL_ADDRESS, LSM6DSL_OUTZ_H_G, 1, &gyro_z_h, 1, HAL_MAX_DELAY);

    // Combine high and low bytes
  gyro_x = (int16_t)(gyro_x_h << 8 | gyro_x_l);
  gyro_y = (int16_t)(gyro_y_h << 8 | gyro_y_l);
  gyro_z = (int16_t)(gyro_z_h << 8 | gyro_z_l);

    // Print accelerometer and gyroscope data
  char debug_message[100];
  snprintf(debug_message, sizeof(debug_message), "Accel - X: %d, Y: %d, Z: %d | Gyro - X: %d, Y: %d, Z: %d\n", accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);
  HAL_UART_Transmit(&huart1, (uint8_t*)debug_message, strlen(debug_message), HAL_MAX_DELAY);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
