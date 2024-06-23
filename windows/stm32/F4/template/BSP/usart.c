#include "usart.h"

u8 USART1_TX_buf[U1_TXMAX_len] = {0};
u8 USART2_TX_buf[U2_TXMAX_len] = {0};
u8 USART3_TX_buf[U3_TXMAX_len] = {0};
u8 UART4_TX_buf[U4_TXMAX_len] = {0};
u8 UART5_TX_buf[U5_TXMAX_len] = {0};

u8 USART1_RX_buf[U1_RXMAX_len] = {0};
u8 USART2_RX_buf[U2_RXMAX_len] = {0};
u8 USART3_RX_buf[U3_RXMAX_len] = {0};
u8 UART4_RX_buf[U4_RXMAX_len] = {0};
u8 UART5_RX_buf[U5_RXMAX_len] = {0};

u8 USART1_RX_updated = 0, USART1_RX_buf_LENTH = 0;
u8 USART2_RX_updated = 0, USART2_RX_buf_LENTH = 0;
u8 USART3_RX_updated = 0, USART3_RX_buf_LENTH = 0;
u8 UART4_RX_updated = 0, UART4_RX_buf_LENTH = 0;
u8 UART5_RX_updated = 0, UART5_RX_buf_LENTH = 0;

void USATR_config(USART_TypeDef *USARTx, u32 BaudRate, GPIO_TypeDef *GPIOx, u32 Pin)
{
	USART_InitTypeDef USART_InitStructure;

	if (USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		gpio_AFconfig(GPIOx, Pin, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_USART1);
		//		nvic_config(USART1_IRQn,USART1_IRQn_pre,USART1_IRQn_sub);
	}
	if (USARTx == USART2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		gpio_AFconfig(GPIOx, Pin, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_USART2);
		//		nvic_config(USART2_IRQn,USART2_IRQn_pre,USART2_IRQn_sub);
	}
	if (USARTx == USART3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		gpio_AFconfig(GPIOx, Pin, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_USART3);
		nvic_config(USART3_IRQn, USART3_IRQn_pre, USART3_IRQn_sub);
	}
	if (USARTx == UART4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
		gpio_AFconfig(GPIOx, Pin, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_UART4);
		nvic_config(UART4_IRQn, UART4_IRQn_pre, UART4_IRQn_sub);
	}
	if (USARTx == UART5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
		gpio_AFconfig(GPIOC, GPIO_Pin_12, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_UART5);
		gpio_AFconfig(GPIOD, GPIO_Pin_2, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_UART5);
		nvic_config(UART5_IRQn, UART5_IRQn_pre, UART5_IRQn_sub);
	}

	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USARTx, &USART_InitStructure);

	USART_Cmd(USARTx, ENABLE);
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) != SET)
		;
}

void USART3_Configuration(void)
{
	USATR_config(USART3, 115200, GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE); // 开启空闲中断

	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);

	DMA_Config(USART3_RX_DMA_Stream, USART_DMA_Channel, (u32) & (USART3->DR), (u32)USART3_RX_buf, U3_RXMAX_len, DMA_DIR_PeripheralToMemory);
	DMA_Cmd(DMA1_Stream1, ENABLE); // 使能接收

	DMA_Config(USART3_TX_DMA_Stream, USART_DMA_Channel, (u32) & (USART3->DR), (u32)USART3_TX_buf, U3_TXMAX_len, DMA_DIR_MemoryToPeripheral);
	//	DMA_Cmd(DMA1_Stream3,ENABLE);												//使能发送
}

void UART4_Configuration(void)
{
	USATR_config(UART4, 115200, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);

	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE); // 开启空闲中断

	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);

	DMA_Config(UART4_RX_DMA_Stream, USART_DMA_Channel, (u32) & (UART4->DR), (u32)UART4_RX_buf, U4_RXMAX_len, DMA_DIR_PeripheralToMemory);
	DMA_Cmd(DMA1_Stream2, ENABLE); // 使能接收

	DMA_Config(UART4_TX_DMA_Stream, USART_DMA_Channel, (u32) & (UART4->DR), (u32)UART4_TX_buf, U4_TXMAX_len, DMA_DIR_MemoryToPeripheral);
	//	DMA_Cmd(DMA1_Stream4,ENABLE);												//使能发送
}

void UART5_Configuration(void)
{
	USATR_config(UART5, 115200, GPIOC, GPIO_Pin_12 | GPIO_Pin_2);
	USART_ITConfig(UART5, USART_IT_IDLE, ENABLE); // 开启空闲中断

	USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);
	DMA_Config(UART5_RX_DMA_Stream, USART_DMA_Channel, (u32) & (UART5->DR), (u32)UART5_RX_buf, U5_RXMAX_len, DMA_DIR_PeripheralToMemory);
	DMA_Cmd(DMA1_Stream0, ENABLE); // 使能接收
}

void UART4_printf(const char *format, ...)
{
	va_list args;
	int n;
	DMA_Cmd(DMA1_Stream4, DISABLE); // 关闭DMA传输
	va_start(args, format);
	n = vsprintf((char *)UART4_TX_buf, format, args);
	va_end(args);

	while (DMA_GetCmdStatus(DMA1_Stream4) != DISABLE)
	{
	}										 // 确保DMA可以被配置
	DMA_SetCurrDataCounter(DMA1_Stream4, n); // 数据传输量
	DMA_Cmd(DMA1_Stream4, ENABLE);
}

void usart_init(void)
{
	USART3_Configuration();
	UART4_Configuration();
	UART5_Configuration();
}

/* 判断数组以何字符开始 */
bool bufStartsWith(char *str, char *buf)
{
	char i;
	for (i = 0;; i++)
	{
		if (str[i] == 0)
			return true;
		if (buf[i] == 0)
			return false;
		if (buf[i] != str[i])
			return false;
		;
	}
}

char mode = 0;
/* 根据不同的开始字符选择不同的mode */
void exeCmd(void)
{
	if (bufStartsWith("P ", (char*)USART3_RX_buf))
		mode = 1;
	if (bufStartsWith("I ", (char*)USART3_RX_buf))
		mode = 2;
	if (bufStartsWith("D ", (char*)USART3_RX_buf))
		mode = 3;
	if (bufStartsWith("t+5", (char*)USART3_RX_buf))
		mode = 4;
	if (bufStartsWith("t-5", (char*)USART3_RX_buf))
		mode = 5;
	if (bufStartsWith("target ", (char*)USART3_RX_buf))
		mode = 6;
}

/* 传送数据给匿名地面站 */
void niming_report(short aacx, short aacy, short aacz, short gyrox, short gyroy, short gyroz, short roll, short pitch, short yaw)
{
	u8 i;
	DMA_Cmd(DMA1_Stream3, DISABLE); // 关闭DMA传输
	//	memset(USART3_TX_buf,0,23);
	USART3_TX_buf[0] = 0XAA; // 帧头
	USART3_TX_buf[1] = 0XAA; // 帧头
	USART3_TX_buf[2] = 0XF1; // 功能字
	USART3_TX_buf[3] = 18;	 // 数据长度

	USART3_TX_buf[4] = (aacx >> 8) & 0XFF;
	USART3_TX_buf[5] = aacx & 0XFF;
	USART3_TX_buf[6] = (aacy >> 8) & 0XFF;
	USART3_TX_buf[7] = aacy & 0XFF;
	USART3_TX_buf[8] = (aacz >> 8) & 0XFF;
	USART3_TX_buf[9] = aacz & 0XFF;
	USART3_TX_buf[10] = (gyrox >> 8) & 0XFF;
	USART3_TX_buf[11] = gyrox & 0XFF;
	USART3_TX_buf[12] = (gyroy >> 8) & 0XFF;
	USART3_TX_buf[13] = gyroy & 0XFF;
	USART3_TX_buf[14] = (gyroz >> 8) & 0XFF;
	USART3_TX_buf[15] = gyroz & 0XFF;
	USART3_TX_buf[16] = (roll >> 8) & 0XFF;
	USART3_TX_buf[17] = roll & 0XFF;
	USART3_TX_buf[18] = (pitch >> 8) & 0XFF;
	USART3_TX_buf[19] = pitch & 0XFF;
	USART3_TX_buf[20] = (yaw >> 8) & 0XFF;
	USART3_TX_buf[21] = yaw & 0XFF;
	USART3_TX_buf[22] = 0; // 校验数置零
	for (i = 0; i < 22; i++)
		USART3_TX_buf[22] += USART3_TX_buf[i]; // 计算校验和

	while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE)
	{
	}										  // 确保DMA可以被设置
	DMA_SetCurrDataCounter(DMA1_Stream3, 23); // 数据传输量
	DMA_Cmd(DMA1_Stream3, ENABLE);			  // 开启DMA传输
}

void DEBUG_PRINTF(const char *format, ...)
{
	va_list args;
	int n;
	DMA_Cmd(DMA1_Stream3, DISABLE); // 关闭DMA传输
	va_start(args, format);
	n = vsprintf((char *)USART3_TX_buf, format, args);
	va_end(args);

	while (DMA_GetCmdStatus(DMA1_Stream3) != DISABLE)
	{
	}										 // 确保DMA可以被设置
	DMA_SetCurrDataCounter(DMA1_Stream3, n); // 数据传输量
	DMA_Cmd(DMA1_Stream3, ENABLE);
}

/* 调参函数 */
void tuning(float *Kp, float *Ki, float *Kd, float *target)
{
	if (USART3_RX_updated)
	{
		USART3_RX_updated = 0;
		exeCmd();
	}
	switch (mode) // 根据mode的不同调节不同的参数
	{
	case 1:
		mode = 0;
		*Kp = atof((char *)USART3_RX_buf + 2);
		DEBUG_PRINTF("P_SET P set to %.2f\n", *Kp);
		break;

	case 2:
		mode = 0;
		*Ki = atof((char *)USART3_RX_buf + 2);
		DEBUG_PRINTF("I_SET I set to %.2f\n", *Ki);
		break;

	case 3:
		mode = 0;
		*Kd = atof((char *)USART3_RX_buf + 2);
		DEBUG_PRINTF("D_SET D set to %.2f\n", *Kd);
		break;

	case 4:
		mode = 0;
		*target = *target + atof((char *)USART3_RX_buf + 2);
		DEBUG_PRINTF("target_SET target set to %.2f\n", *target);
		break;

	case 5:
		mode = 0;
		*target = *target - atof((char *)USART3_RX_buf + 2);
		DEBUG_PRINTF("target_SET target set to %.2f\n", *target);
		break;

	case 6:
		mode = 0;
		*target = atof((char *)USART3_RX_buf + 7);
		DEBUG_PRINTF("target_SET target set to %.2f\n", *target);
		break;

	default:
		break;
	}
}

void set_parameter(char *str, float *parameter)
{
	if (USART3_RX_updated)
	{
		if (bufStartsWith(str, (char*)USART3_RX_buf))
		{
			USART3_RX_updated = 0;
			*parameter = atof((char *)USART3_RX_buf + sizeof(str) - 2);
		}
	}
}

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3, USART_IT_IDLE) != RESET) // 利用空闲中断判断数据是否通过串口传输完成
	{
		DMA_Cmd(DMA1_Stream1, DISABLE); // 关闭DMA，防止处理期间有数据
		USART3_RX_updated = 1;			// 置1表示一次接收数据完成
		USART3->SR;
		USART3->DR;															// 先取SR再取DR以清除IDLE
		USART3_RX_buf_LENTH = U3_RXMAX_len - DMA1_Stream1->NDTR;			// 获得串口发送过来的字符的长度
		memset(USART3_RX_buf + USART3_RX_buf_LENTH, 0, DMA1_Stream1->NDTR); // 这样做是为了可以重新覆盖接收数组

		DMA_ClearFlag(DMA1_Stream1, DMA_IT_TCIF1);
		DMA1_Stream1->NDTR = U3_RXMAX_len; // 重新写入传输量
		DMA_Cmd(DMA1_Stream1, ENABLE);	   // 重新打开
	}
}

void UART4_IRQHandler(void)
{
	if (USART_GetITStatus(UART4, USART_IT_IDLE) != RESET) // 利用空闲中断判断数据是否通过串口传输完成
	{
		DMA_Cmd(DMA1_Stream2, DISABLE); // 关闭DMA，防止处理数据期间有数据
		UART4_RX_updated = 1;			// 置1表示一次接收数据完成
		UART4->SR;
		UART4->DR;														  // 先取SR再取DR以清除IDLE
		UART4_RX_buf_LENTH = U4_RXMAX_len - DMA1_Stream2->NDTR;			  // 获得串口发送过来的字符的长度
		memset(UART4_RX_buf + UART4_RX_buf_LENTH, 0, DMA1_Stream2->NDTR); // 这样做是为了可以重新覆盖接收数组

		DMA_ClearFlag(DMA1_Stream2, DMA_IT_TCIF2);
		DMA1_Stream2->NDTR = U4_RXMAX_len; // 重新写入传输量
		DMA_Cmd(DMA1_Stream2, ENABLE);	   // 重新打开
	}
}

void UART5_IRQHandler(void)
{
	if (USART_GetITStatus(UART5, USART_IT_IDLE) != RESET) // 利用空闲中断判断数据是否通过串口传输完成
	{
		DMA_Cmd(DMA1_Stream0, DISABLE); // 关闭DMA，防止处理数据期间有数据
		UART5_RX_updated = 1;			// 置1表示一次接收数据完成
		UART5->SR;
		UART5->DR;														  // 先取SR再取DR以清除IDLE
		UART5_RX_buf_LENTH = U5_RXMAX_len - DMA1_Stream0->NDTR;			  // 获得串口发送过来的字符的长度
		memset(UART5_RX_buf + UART5_RX_buf_LENTH, 0, DMA1_Stream0->NDTR); // 这样做是为了可以重新覆盖接收数组

		DMA_ClearFlag(DMA1_Stream0, DMA_IT_TCIF0);
		DMA1_Stream0->NDTR = U5_RXMAX_len; // 重新写入传输量
		DMA_Cmd(DMA1_Stream0, ENABLE);	   // 重新打开
	}
}

void DMA1_Stream4_IRQHandler(void) // 用于UART4发送的DMA中断
{
	if (DMA_GetITStatus(DMA1_Stream4, DMA_IT_TCIF4))
	{
		DMA_ClearFlag(DMA1_Stream4, DMA_IT_TCIF4);
		DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_TCIF4);
	}
}

void DMA1_Stream1_IRQHandler(void) // 用于USART3接收的DMA
{
	if (DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1))
	{
		DMA_ClearFlag(DMA1_Stream1, DMA_IT_TCIF1);
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);
	}
}

void DMA1_Stream3_IRQHandler(void) // 用于USART3发送的DMA
{
	if (DMA_GetITStatus(DMA1_Stream3, DMA_IT_TCIF3))
	{
		DMA_ClearFlag(DMA1_Stream3, DMA_IT_TCIF3);
		DMA_ClearITPendingBit(DMA1_Stream3, DMA_IT_TCIF3);
	}
}
