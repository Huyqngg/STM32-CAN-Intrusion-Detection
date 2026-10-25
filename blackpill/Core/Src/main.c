/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "MCP2515.h"
#include "ai_platform.h"     // Lõi AI
#include "network.h"         // Kiến trúc mạng
#include "network_data.h"    // Trọng số
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
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
char msg[100];

// ---- BIẾN CHO AI ----
ai_handle network;
ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];
ai_float in_data[AI_NETWORK_IN_1_SIZE];
ai_float out_data[AI_NETWORK_OUT_1_SIZE];
ai_buffer *ai_input;
ai_buffer *ai_output;

// Đã trích xuất chính xác từ file Dataset của bạn (Thuật toán MinMaxScaler)
const float data_min[10] = {0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f};
const float data_range[10] = {1000.000000f, 255.000000f, 255.000000f, 255.000000f, 255.000000f, 255.000000f, 255.000000f, 255.000000f, 255.000000f, 6743.000000f};

uint32_t last_msg_time = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

      // 1. Khởi tạo SPI và cấu hình MCP2515
      MCP2515_Initialize();
      MCP2515_SetConfigMode();

      // 2. Cấu hình Baudrate 500kbps
      MCP2515_WriteByte(MCP2515_CNF1, 0x00);
      MCP2515_WriteByte(MCP2515_CNF2, 0x90);
      MCP2515_WriteByte(MCP2515_CNF3, 0x02);

      // 3. Tắt màng lọc & Bật ngắt
      MCP2515_WriteByte(MCP2515_RXB0CTRL, 0x60);
      MCP2515_WriteByte(MCP2515_CANINTE, 0x01);

      // 4. Chuyển sang chế độ chạy bình thường
      MCP2515_SetNormalMode();
      HAL_UART_Transmit(&huart1, (uint8_t *)"Node B Ready!\r\n", 15, 100);

      // ---- KHỞI TẠO AI ----
      ai_error err;
      err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
      if (err.type != AI_ERROR_NONE) {
          HAL_UART_Transmit(&huart1, (uint8_t *)"AI Init FAILED!\r\n", 17, 100);
          while(1);
      }

      ai_network_params params = {
    		   {
                    AI_NETWORK_DATA_WEIGHTS(ai_network_data_weights_get()),
                    AI_NETWORK_DATA_ACTIVATIONS(activations)
                }
            };
      ai_network_init(network, &params);
      HAL_UART_Transmit(&huart1, (uint8_t *)"AI Core Started!\r\n", 18, 100);

      last_msg_time = HAL_GetTick(); // Bắt đầu bấm giờ
      // ---------------------------------------

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	      // Kiểm tra chân ngắt PA3
	      if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
	      {
	          uint8_t rx_status = MCP2515_GetRxStatus();

	          if (rx_status & 0x40) // Nếu có tin ở RXB0
	          {
	              uint8_t rx_reg[13];
	              MCP2515_ReadRxSequence(MCP2515_READ_RXB0SIDH, rx_reg, 13);

	              uint32_t can_id = (rx_reg[0] << 3) | (rx_reg[1] >> 5);

	              // 1. Tính Delta_Time (Để cập nhật last_msg_time, tránh sai số cho gói sau)
	                          uint32_t current_time = HAL_GetTick();
	                          last_msg_time = current_time;

	                          // 2. Gom ĐÚNG 9 đặc trưng (ID, Data0 -> Data7)
	                          float raw_input[9] = {
	                              (float)can_id,
	                              (float)rx_reg[5], (float)rx_reg[6], (float)rx_reg[7], (float)rx_reg[8],
	                              (float)rx_reg[9], (float)rx_reg[10], (float)rx_reg[11], (float)rx_reg[12]
	                          };

	                          // 3. Chuẩn hóa 9 phần tử
	                          for(int i = 0; i < 9; i++) {
	                              if (data_range[i] != 0.0f) {
	                                  in_data[i] = (raw_input[i] - data_min[i]) / data_range[i];
	                              } else {
	                                  in_data[i] = 0.0f;
	                              }
	                          }

	                          // 4. CHẠY AI DỰ ĐOÁN (BỔ SUNG 2 DÒNG LẤY BUFFER DƯỚI ĐÂY)
	                          	              ai_input = ai_network_inputs_get(network, NULL);   // <--- THÊM DÒNG NÀY
	                          	              ai_output = ai_network_outputs_get(network, NULL); // <--- THÊM DÒNG NÀY

	                          	              ai_input[0].data = AI_HANDLE_PTR(in_data);
	                          	              ai_output[0].data = AI_HANDLE_PTR(out_data);
	                          	              ai_network_run(network, &ai_input[0], &ai_output[0]);

	                          	              // 5. Tìm nhãn có xác suất cao nhất
	                          	              int ai_predict = 0;
	                          	              float max_prob = out_data[0];
	                          	              for(int i = 1; i < 3; i++) {
	                          	                  if(out_data[i] > max_prob) {
	                          	                      max_prob = out_data[i];
	                          	                      ai_predict = i;
	                          	                  }
	                          	              }

	                          	              // 6. Hiển thị nhãn khớp với nhãn Python mới
	                          	              char *attack_name = "UNKNOWN";
	                          	              if(ai_predict == 0) attack_name = "DoS ATTACK";
	                          	              else if(ai_predict == 1) attack_name = "NORMAL";     // Sửa lại cho đẹp chuỗi in
	                          	              else if(ai_predict == 2) attack_name = "SPOOFING";

	                          	              sprintf(msg, "ID:0x%lX | %s | Prob:%d%%\r\n",
	                          	                      (unsigned long)can_id, attack_name, (int)(max_prob * 100));
	                          	              HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 100);

	                          	              // Xóa cờ ngắt để nhận tin tiếp theo
	                          	              MCP2515_BitModify(MCP2515_CANINTF, 0x01, 0x00);

  /* USER CODE END 3 */
}
	      }
  }
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
