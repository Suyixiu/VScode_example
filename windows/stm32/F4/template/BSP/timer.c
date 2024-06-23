#include "timer.h"

void TIMER_init(void)
{
	TIM6_init();
	TIM7_init();
}

void TIM6_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	DBGMCU_APB1PeriphConfig(DBGMCU_TIM6_STOP, ENABLE); // 使能debug时设断点使定时器停

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); // 使能TIM6时钟

	TIM_TimeBaseInitStructure.TIM_Period = 250 - 1;					// 自动重装载值	即CNT加到500就置零
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8400 - 1;				// 定时器分频		即84M/8400hz使CNT+1	所以这样子计算出来每次进中断的时间为
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式												 250/(84M/8400)S		即0.025s 25ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure); // 初始化TIM6

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); // 允许定时器6更新中断  溢出中断
	TIM_Cmd(TIM6, ENABLE);					   // 使能定时器6

	nvic_config(TIM6_DAC_IRQn, TIM6_DAC_IRQn_pre, TIM6_DAC_IRQn_sub);
}

void TIM7_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	DBGMCU_APB1PeriphConfig(DBGMCU_TIM7_STOP, ENABLE); // 使能debug时设断点使定时器停

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); // 使能TIM7时钟

	TIM_TimeBaseInitStructure.TIM_Period = 500 - 1;					// 自动重装载值	即CNT加到500就置零
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8400 - 1;				// 定时器分频		即84M/8400hz使CNT+1		所以这样子计算出来每次进中断的时间为
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式												  500/(84M/8400)S		即	0.05s 50ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure); // 初始化TIM7

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); // 允许定时器7更新中断  溢出中断
	TIM_Cmd(TIM7, ENABLE);					   // 使能定时器7

	nvic_config(TIM7_IRQn, TIM7_IRQn_pre, TIM7_IRQn_sub);
}

// 以微秒为单位返回系统时间
uint32_t micros(void)
{
	register uint32_t ms, cycle_cnt;
	do
	{
		ms = sysTickUptime;
		cycle_cnt = SysTick->VAL;
	} while (ms != sysTickUptime);
	return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

// 微秒级延时
void delay_us(uint32_t us)
{
	uint32_t now = micros();
	while (micros() - now < us)
		;
}

// 毫秒级延时
void delay_ms(uint32_t ms)
{
	while (ms--)
		delay_us(1000);
}

// 以毫秒为单位返回系统时间
uint32_t millis(void)
{
	return sysTickUptime;
}

void TIM6_DAC_IRQHandler(void) // 定时器6中断服务函数
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET) // CNT溢出中断
	{
		__nop(); // 只是为了设置断点
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update); // 清除中断标志位
}

void TIM7_IRQHandler(void) // 定时器7中断服务函数
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) == SET) // CNT溢出中断
	{
		__nop(); // 只是为了设置断点
	}
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update); // 清除中断标志位
}
