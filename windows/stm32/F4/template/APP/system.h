#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include <stdio.h>
#include "stdbool.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"
#include "math.h"
#include "my_math.h"

#include "usart.h"
#include "timer.h"
#include "pwm.h"
#include "dma.h"
#include "nvic.h"
#include "gpio.h"

#define usTicks 180

void Parameter_Init(void);
void systemInit(void);
void Loop(void);

#endif
