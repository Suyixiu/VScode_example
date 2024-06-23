#include "system.h"
#include "FreeRTOS.h"
#include "task.h"

#define START_TASK_PRIO		1
#define START_STK_SIZE 		128  
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

#define LED0_TASK_PRIO		2
#define LED0_STK_SIZE 		50  
TaskHandle_t LED0Task_Handler;
void led0_task(void *pvParameters);

#define LED1_TASK_PRIO		3
#define LED1_STK_SIZE 		50  
TaskHandle_t LED1Task_Handler;
void led1_task(void *pvParameters);

#define FLOAT_TASK_PRIO		4
#define FLOAT_STK_SIZE 		128
TaskHandle_t FLOATTask_Handler;
void float_task(void *pvParameters);

void systemInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置系统中断优先级分组2
	SysTick_Config(SystemCoreClock / 1000);			// 滴答定时器配置，1ms触发一次中断
	usart_init();
	PWM_init();
	delay_ms(2000);
	LED_init();

	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //创建LED1任务
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler);        
    //浮点测试任务
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//LED0任务函数 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED_GREEN_OFF();
        vTaskDelay(200);
        LED_GREEN_ON();
        vTaskDelay(800);
    }
}   

//LED1任务函数
void led1_task(void *pvParameters)
{
    while(1)
    {
        LED_RED_OFF();
        vTaskDelay(200);
        LED_RED_ON();
        vTaskDelay(800);
    }
}

//浮点测试任务
void float_task(void *pvParameters)
{
	static float float_num=0.00;
	while(1)
	{
		float_num+=0.01f;
		DEBUG_PRINTF("float_num is: %.4f\r\n",float_num);
        vTaskDelay(1000);
	}
}


// void Loop(void)
// {
// 	static uint32_t currentTime = 0;
// 	static uint32_t loopTime_1ms = 0;
// 	static uint32_t loopTime_2ms = 0;
// 	static uint32_t loopTime_5ms = 0;
// 	static uint32_t loopTime_20ms = 0;
// 	static uint32_t loopTime_250ms = 0;

// 	currentTime = micros(); // 获取当前系统时间，单位微秒

// 	if ((int32_t)(currentTime - loopTime_1ms) >= 0)
// 	{
// 		loopTime_1ms = currentTime + 1000; // 1ms控制周期
// 	}

// 	if ((int32_t)(currentTime - loopTime_2ms) >= 0)
// 	{
// 		loopTime_2ms = currentTime + 2000; // 2ms控制周期
// 	}

// 	if ((int32_t)(currentTime - loopTime_5ms) >= 0)
// 	{
// 		loopTime_5ms = currentTime + 5000; // 5ms控制周期
// 	}

// 	if ((int32_t)(currentTime - loopTime_20ms) >= 0)
// 	{
// 		loopTime_20ms = currentTime + 20000; // 20ms毫秒控制周期
// 	}

// 	if ((int32_t)(currentTime - loopTime_250ms) >= 0)
// 	{
// 		loopTime_250ms = currentTime + 250000; // 250ms控制周期
// 		DEBUG_PRINTF("just for test %d\n", loopTime_250ms);
// 		LED_GREEN_TOGGLE();
// 		LED_RED_TOGGLE();
// 	}
// }
