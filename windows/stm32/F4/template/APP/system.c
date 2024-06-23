#include "system.h"

void Parameter_Init(void)
{
}

void systemInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置系统中断优先级分组2
	SysTick_Config(SystemCoreClock / 1000);			// 滴答定时器配置，1ms触发一次中断
	usart_init();
	PWM_init();
	delay_ms(2000);
	LED_init();
}

void Loop(void)
{
	static uint32_t currentTime = 0;
	static uint32_t loopTime_1ms = 0;
	static uint32_t loopTime_2ms = 0;
	static uint32_t loopTime_5ms = 0;
	static uint32_t loopTime_20ms = 0;
	static uint32_t loopTime_250ms = 0;

	currentTime = micros(); // 获取当前系统时间，单位微秒

	if ((int32_t)(currentTime - loopTime_1ms) >= 0)
	{
		loopTime_1ms = currentTime + 1000; // 1ms控制周期
	}

	if ((int32_t)(currentTime - loopTime_2ms) >= 0)
	{
		loopTime_2ms = currentTime + 2000; // 2ms控制周期
	}

	if ((int32_t)(currentTime - loopTime_5ms) >= 0)
	{
		loopTime_5ms = currentTime + 5000; // 5ms控制周期
	}

	if ((int32_t)(currentTime - loopTime_20ms) >= 0)
	{
		loopTime_20ms = currentTime + 20000; // 20ms毫秒控制周期
	}

	if ((int32_t)(currentTime - loopTime_250ms) >= 0)
	{
		loopTime_250ms = currentTime + 250000; // 250ms控制周期
		DEBUG_PRINTF("just for test %d\n", loopTime_250ms);
		LED_GREEN_TOGGLE();
		LED_RED_TOGGLE();
	}
}
