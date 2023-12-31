/*
 * RCC.h
 *
 *  Created on: 20 May 2023
 *      Author: Burak KARAPINAR
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_
#include "stm32f407xx.h"

#define RCC_GPIOA_CLK_ENABLE()		do{uint32_t tempValue=0;									\
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN);				\
										tempValue = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN);	\
										UNUSED(tempValue);										\
										}while(0)

#define RCC_GPIOB_CLK_ENABLE()		do{uint32_t tempValue=0;									\
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOBEN);				\
										tempValue = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOBEN);	\
										UNUSED(tempValue);										\
										}while(0)


#define RCC_GPIOC_CLK_ENABLE()		do{uint32_t tempValue=0;									\
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN);				\
										tempValue = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN);	\
										UNUSED(tempValue);										\
										}while(0)

#define RCC_GPIOD_CLK_ENABLE()		do{uint32_t tempValue=0;									\
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN);				\
										tempValue = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN);	\
										UNUSED(tempValue);										\
										}while(0)

#define RCC_GPIOG_CLK_ENABLE()		do{uint32_t tempValue=0;									\
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOGEN);				\
										tempValue = READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOGEN);	\
										UNUSED(tempValue);										\
										}while(0)


#define RCC_SYSCFG_CLK_ENABLE()		do{	uint32_t tempValue=0;									\
										SET_BIT(RCC->APB2ENR,RCC_APB2ENR_SYSCFGEN);				\
										tempValue = READ_BIT(RCC->APB2ENR,RCC_APB2ENR_SYSCFGEN);\
										UNUSED(tempValue);										\
										}while(0)



#define RCC_GPIOA_CLK_DISABLE()			CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN)
#define RCC_GPIOB_CLK_DISABLE()			CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOBEN)
#define RCC_GPIOC_CLK_DISABLE()			CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN)
#define RCC_GPIOD_CLK_DISABLE()			CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN)



#define RCC_SPI1_CLK_ENABLE()			do{	uint32_t tempValue = 0;										\
											SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);					\
											tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);	\
											UNUSED(tempValue);											\
											}while(0)

#define RCC_SPI4_CLK_ENABLE()			do{	uint32_t tempValue = 0;										\
											SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);					\
											tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);		\
											UNUSED(tempValue);											\
											}while(0)


#define RCC_SPI2_CLK_ENABLE()			do{	uint32_t tempValue = 0;										\
											SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);					\
											tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);		\
											UNUSED(tempValue);											\
											}while(0)

#define RCC_SPI3_CLK_ENABLE()			do{	uint32_t tempValue = 0;										\
											SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);					\
											tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);		\
											UNUSED(tempValue);											\
											}while(0)

#define RCC_USART2_CLK_ENABLE()			do{	uint32_t tempValue = 0;										\
											SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);				\
											tempValue = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);	\
											UNUSED(tempValue);											\
											}while(0)

uint32_t	RCC_GetSystemClock();
uint32_t	RCC_GetHClock();
uint32_t	RCC_GetPClock1();
uint32_t	RCC_GetPClock2();


#define RCC_USART2_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR,RCC_APB1ENR_USART2EN)
#define RCC_SP1_CLK_DISABLE()			CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_SPI1EN)
#define RCC_SP2_CLK_DISABLE()			CLEAR_BIT(RCC->APB1ENR,RCC_APB1ENR_SPI2EN)
#define RCC_SP3_CLK_DISABLE()			CLEAR_BIT(RCC->APB1ENR,RCC_APB1ENR_SPI3EN)
#define RCC_SP4_CLK_DISABLE()			CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_SPI4EN)

#endif /* INC_RCC_H_ */
