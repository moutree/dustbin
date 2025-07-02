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
#include "sort_motor.h"
#include "sort_servo.h"
#include "pc_task.h"
#include "belt_motor.h"
#include "laser_distance.h"
#include "usart_screen.h"
#include "compress.h"
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

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
#define SORT_TASK_PRIO						2		// 任务优先级
#define SORT_STK_SIZE						256		// 任务堆栈大小
TaskHandle_t Sort_Task_Handler;						// 任务句柄

#define SERVO_TASK_PRIO						2		// 任务优先级
#define SERVO_STK_SIZE						256		// 任务堆栈大小
TaskHandle_t Servo_Task_Handler;						// 任务句柄

#define BELT_TASK_PRIO						2		// 任务优先级
#define BELT_STK_SIZE						256		// 任务堆栈大小
TaskHandle_t Belt_Task_Handler;						// 任务句柄

#define PC_TASK_PRIO						2		// 任务优先级
#define PC_STK_SIZE						256		// 任务堆栈大小
TaskHandle_t Pc_Task_Handler;						// 任务句柄

#define LASER_TASK_PRIO						1		// 任务优先级
#define PC_STK_SIZE						256		// 任务堆栈大小
TaskHandle_t Pc_Task_Handler;						// 任务句柄

#define COMPRESS_TASK_PRIO						2		// 任务优先级
#define COMPRESS_STK_SIZE						256		// 任务堆栈大小
TaskHandle_t COMPRESS_Task_Handler;						// 任务句柄
///* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	  xTaskCreate((TaskFunction_t		)sort_task,								// 任务函数
							(const char*		)"sort_task",				// 任务名称
							(uint16_t			)SORT_STK_SIZE,				// 任务堆栈大小
							(void*				)NULL,						// 传递给任务函数的参数
							(UBaseType_t		)SORT_TASK_PRIO,			// 任务优先级
							(TaskHandle_t*		)&Sort_Task_Handler);		// 任务句柄
							
	  xTaskCreate((TaskFunction_t		)servo_task,								// 任务函数
							(const char*		)"servo_task",				// 任务名称
							(uint16_t			)SERVO_STK_SIZE,				// 任务堆栈大小
							(void*				)NULL,						// 传递给任务函数的参数
							(UBaseType_t		)SERVO_TASK_PRIO,			// 任务优先级
							(TaskHandle_t*		)&Servo_Task_Handler);		// 任务句柄		

	  xTaskCreate((TaskFunction_t		)belt_task,								// 任务函数
							(const char*		)"belt_task",				// 任务名称
							(uint16_t			)BELT_STK_SIZE,				// 任务堆栈大小
							(void*				)NULL,						// 传递给任务函数的参数
							(UBaseType_t		)BELT_TASK_PRIO,			// 任务优先级
							(TaskHandle_t*		)&Belt_Task_Handler);		// 任务句柄								

	  xTaskCreate((TaskFunction_t		)pc_task,								// 任务函数
							(const char*		)"pc_task",				// 任务名称
							(uint16_t			)PC_STK_SIZE,				// 任务堆栈大小
							(void*				)NULL,						// 传递给任务函数的参数
							(UBaseType_t		)PC_TASK_PRIO,			// 任务优先级
							(TaskHandle_t*		)&Pc_Task_Handler);		// 任务句柄				

	  xTaskCreate((TaskFunction_t		)laser_task,								// 任务函数
							(const char*		)"laser_task",				// 任务名称
							(uint16_t			)PC_STK_SIZE,				// 任务堆栈大小
							(void*				)NULL,						// 传递给任务函数的参数
							(UBaseType_t		)LASER_TASK_PRIO,			// 任务优先级
							(TaskHandle_t*		)&Pc_Task_Handler);		// 任务句柄		

	xTaskCreate((TaskFunction_t		)compress_task,								// 任务函数
							(const char*		)"compress_task",				// 任务名称
							(uint16_t			)COMPRESS_STK_SIZE,				// 任务堆栈大小
							(void*				)NULL,						// 传递给任务函数的参数
							(UBaseType_t		)COMPRESS_TASK_PRIO,			// 任务优先级
							(TaskHandle_t*		)&COMPRESS_Task_Handler);		// 任务句柄								
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
