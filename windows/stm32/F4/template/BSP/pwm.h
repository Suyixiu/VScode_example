#ifndef __PWM_H__
#define __PWM_H__

#include "system.h"

#define IMU_PWM_PULSE TIM3->CCR2
#define FRIC_RWHEEL_PWM_PULSE TIM4->CCR3
#define FRIC_LWHEEL_PWM_PULSE TIM4->CCR4

void fric_wheel_pwm_Configuration(void); // TIM4_CH3(PB8)  && TIM4_CH4(PB9)		普通定时器PWM输出
void heat_pwm_init(void);                // TIM3_CH2(PB5)		普通定时器PWM输出
void PWM_init(void);

#endif
