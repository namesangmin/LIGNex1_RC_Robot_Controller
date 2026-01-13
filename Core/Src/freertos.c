/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for InputTask */
osThreadId_t InputTaskHandle;
uint32_t InputTaskBuffer[ 128 ];
osStaticThreadDef_t InputTaskControlBlock;
const osThreadAttr_t InputTask_attributes = {
  .name = "InputTask",
  .cb_mem = &InputTaskControlBlock,
  .cb_size = sizeof(InputTaskControlBlock),
  .stack_mem = &InputTaskBuffer[0],
  .stack_size = sizeof(InputTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for BlueToothTxTask */
osThreadId_t BlueToothTxTaskHandle;
uint32_t BlueToothTxHandlerBuffer[ 128 ];
osStaticThreadDef_t BlueToothTxHandlerControlBlock;
const osThreadAttr_t BlueToothTxTask_attributes = {
  .name = "BlueToothTxTask",
  .cb_mem = &BlueToothTxHandlerControlBlock,
  .cb_size = sizeof(BlueToothTxHandlerControlBlock),
  .stack_mem = &BlueToothTxHandlerBuffer[0],
  .stack_size = sizeof(BlueToothTxHandlerBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for BluetoothRxTask */
osThreadId_t BluetoothRxTaskHandle;
uint32_t BluetoothRxTaskBuffer[ 128 ];
osStaticThreadDef_t BluetoothRxTaskControlBlock;
const osThreadAttr_t BluetoothRxTask_attributes = {
  .name = "BluetoothRxTask",
  .cb_mem = &BluetoothRxTaskControlBlock,
  .cb_size = sizeof(BluetoothRxTaskControlBlock),
  .stack_mem = &BluetoothRxTaskBuffer[0],
  .stack_size = sizeof(BluetoothRxTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void InputTaskHandler(void *argument);
extern void BlueToothTxTaskHandler(void *argument);
extern void BluetoothRxTaskHandler(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of InputTask */
  InputTaskHandle = osThreadNew(InputTaskHandler, NULL, &InputTask_attributes);

  /* creation of BlueToothTxTask */
  BlueToothTxTaskHandle = osThreadNew(BlueToothTxTaskHandler, NULL, &BlueToothTxTask_attributes);

  /* creation of BluetoothRxTask */
  BluetoothRxTaskHandle = osThreadNew(BluetoothRxTaskHandler, NULL, &BluetoothRxTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_InputTaskHandler */
/**
  * @brief  Function implementing the InputTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_InputTaskHandler */
__weak void InputTaskHandler(void *argument)
{
  /* USER CODE BEGIN InputTaskHandler */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END InputTaskHandler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

