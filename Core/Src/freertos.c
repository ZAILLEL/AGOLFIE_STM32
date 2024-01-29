/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "AGOLFIE.h"
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
/* USER CODE BEGIN Variables */
extern struct AGOLFIE_SENSORS AGOLFIE_SENSORS;
/* USER CODE END Variables */
/* Definitions for RefreshObstacle */
osThreadId_t RefreshObstacleHandle;
const osThreadAttr_t RefreshObstacle_attributes = {
  .name = "RefreshObstacle",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Front_sm */
osThreadId_t Front_smHandle;
const osThreadAttr_t Front_sm_attributes = {
  .name = "Front_sm",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Back_sm */
osThreadId_t Back_smHandle;
const osThreadAttr_t Back_sm_attributes = {
  .name = "Back_sm",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartRefreshObstacle(void *argument);
void StartFront_sm(void *argument);
void StartBack_sm(void *argument);

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
  /* creation of RefreshObstacle */
  RefreshObstacleHandle = osThreadNew(StartRefreshObstacle, NULL, &RefreshObstacle_attributes);

  /* creation of Front_sm */
  Front_smHandle = osThreadNew(StartFront_sm, NULL, &Front_sm_attributes);

  /* creation of Back_sm */
  Back_smHandle = osThreadNew(StartBack_sm, NULL, &Back_sm_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartRefreshObstacle */
/**
  * @brief  Function implementing the RefreshObstacle thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartRefreshObstacle */
void StartRefreshObstacle(void *argument)
{
  /* USER CODE BEGIN StartRefreshObstacle */
  /* Infinite loop */
  for(;;)
  {

	refresh_obstacle(100);
    osDelay(100);
  }
  /* USER CODE END StartRefreshObstacle */
}

/* USER CODE BEGIN Header_StartFront_sm */
/**
* @brief Function implementing the Front_sm thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFront_sm */
void StartFront_sm(void *argument)
{
  /* USER CODE BEGIN StartFront_sm */
  /* Infinite loop */
  for(;;)
  {
	Agolfie_Forward_dostep(AGOLFIE_SENSORS.ZONE_FRONT);
    osDelay(100);
  }
  /* USER CODE END StartFront_sm */
}

/* USER CODE BEGIN Header_StartBack_sm */
/**
* @brief Function implementing the Back_sm thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBack_sm */
void StartBack_sm(void *argument)
{
  /* USER CODE BEGIN StartBack_sm */
  /* Infinite loop */
  for(;;)
  {
	Agolfie_Backward_dostep(AGOLFIE_SENSORS.ZONE_BACK);
    osDelay(100);
  }
  /* USER CODE END StartBack_sm */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

