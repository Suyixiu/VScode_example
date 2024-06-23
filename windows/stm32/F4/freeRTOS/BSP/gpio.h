#ifndef __GPIO_H
#define __GPIO_H

#include "system.h"

#define LED_GREEN_ON() GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define LED_RED_ON() GPIO_ResetBits(GPIOC, GPIO_Pin_14)

#define LED_GREEN_OFF() GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define LED_RED_OFF() GPIO_SetBits(GPIOC, GPIO_Pin_14)

#define LED_GREEN_TOGGLE() GPIO_ToggleBits(GPIOC, GPIO_Pin_13)
#define LED_RED_TOGGLE() GPIO_ToggleBits(GPIOC, GPIO_Pin_14)

void gpio_config(GPIO_TypeDef *GPIOx, u32 Pin, GPIOMode_TypeDef Mode, GPIOOType_TypeDef OType, GPIOPuPd_TypeDef PuPd);
void gpio_AFconfig(GPIO_TypeDef *GPIOx, u32 Pin, GPIOOType_TypeDef OType, GPIOPuPd_TypeDef PuPd, u8 AFto);

void LED_init(void);

#endif
