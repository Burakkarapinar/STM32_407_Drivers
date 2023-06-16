
#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define SET_BIT(REG,BIT)		((REG) |= 	(BIT))
#define CLEAR_BIT(REG,BIT)		((REG) &=~ 	(BIT))
#define READ_BIT(REG,BIT)		((REG) & 	(BIT))
#define UNUSED(x)				(void)x
/*
 * Memory Base Address
 */

#define FLASH_BASE_ADDR				(0X08000000UL)	/* Flash Base Adress 1MB 	*/
#define SRAM1_BASE_ADDR				(0x20000000UL)	/* SRAM1 Base Adress 112 KB	*/
#define SRAM2_BASE_ADDR				(0x2001C000UL)	/* SRAM2 Base Adress 16 KB	*/

/*
 * Peripheral Base Addresses
 */

#define PERIPH_BASE_ADDR			(0X40000000UL)
#define	APB1_BASE_ADDR				PERIPH_BASE_ADRR
#define	APB2_BASE_ADDR				(PERIPH_BASE_ADRR+0x10000UL)
#define	AHB1_BASE_ADDR				(PERIPH_BASE_ADDR+0x20000UL)
#define	AHB2_BASE_ADDR				(PERIPH_BASE_ADRR+0x10000000UL)


/*
 * APB1 Peripherals Base Addresses
 */
#define	TIM2_BASE_ADDR				(APB1_BASE_ADDR)
#define	TIM3_BASE_ADDR				(APB1_BASE_ADDR+0x0400UL)
#define	TIM4_BASE_ADDR				(APB1_BASE_ADDR+0X0800UL)
#define	TIM5_BASE_ADDR				(APB1_BASE_ADDR+0X0C00UL)
#define	TIM6_BASE_ADDR				(APB1_BASE_ADDR+0X1000UL)
#define	TIM7_BASE_ADDR				(APB1_BASE_ADDR+0X1400UL)

#define	SPI2_BASE_ADDR				(APB1_BASE_ADDR+0X3800UL)
#define	SPI3_BASE_ADDR				(APB1_BASE_ADDR+0X3C00UL)

#define	USART2_BASE_ADDR			(APB1_BASE_ADDR+0X4400UL)
#define	USART3_BASE_ADDR			(APB1_BASE_ADDR+0X4800UL)

#define	I2C1_BASE_ADDR				(APB1_BASE_ADDR+0X5400UL)
#define	I2C2_BASE_ADDR				(APB1_BASE_ADDR+0X5800UL)
#define	I2C3_BASE_ADDR				(APB1_BASE_ADDR+0X5C00UL)


/*
 * APB2 Peripherals Base Addresses
 */

#define TIM1_BASE_ADRR				(APB2_BASE_ADDR)
#define TIM8_BASE_ADRR				(APB2_BASE_ADDR+0x0400UL)


#define USART1_BASE_ADRR			(APB2_BASE_ADDR+0X1000UL)
#define USART6_BASE_ADRR			(APB2_BASE_ADDR+0X1400UL)

#define SPI1_BASE_ADRR				(APB2_BASE_ADDR+0X3000UL)
#define SPI4_BASE_ADRR				(APB2_BASE_ADDR+0X3400UL)

#define SYSCFG_BASE_ADRR			(APB2_BASE_ADDR+0X3800UL)
#define EXT1_BASE_ADRR				(APB2_BASE_ADDR+0X3C00UL)

/*
 * AHB1 Peripherals Base Addresses
 * */
#define GPIOA_BASE_ADDR				(AHB1_BASE_ADDR+0x0000UL)
#define GPIOB_BASE_ADDR				(AHB1_BASE_ADDR+0x0400UL)
#define GPIOC_BASE_ADDR				(AHB1_BASE_ADDR+0x0800UL)
#define GPIOD_BASE_ADDR				(AHB1_BASE_ADDR+0x0C00UL)
#define GPIOE_BASE_ADDR				(AHB1_BASE_ADDR+0x1000UL)
#define GPIOG_BASE_ADRR				(AHB1_BASE_ADDR+0x1800UL)
#define RCC_BASE_ADDR				(AHB1_BASE_ADDR+0x3800UL)


/*
 * Peripheral Structure Definitions
 */

#define __IO volatile
typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFRL[2];
}GPIO_Typedef_t;


#define GPIOA			((GPIO_Typedef_t*)(GPIOA_BASE_ADDR))
#define GPIOB			((GPIO_Typedef_t*)(GPIOB_BASE_ADDR))
#define GPIOC			((GPIO_Typedef_t*)(GPIOC_BASE_ADDR))
#define GPIOD			((GPIO_Typedef_t*)(GPIOD_BASE_ADDR))
#define GPIOE			((GPIO_Typedef_t*)(GPIOE_BASE_ADDR))
#define GPIOG			((GPIO_Typedef_t*)(GPIOG_BASE_ADRR))

/*
 * RCC Register Map
 */
typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t PLLCFGR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t AHB1RSTR;
	__IO uint32_t AHB2RSTR;
	__IO uint32_t AHB3RSTR;
	__IO uint32_t RESERVED0;
	__IO uint32_t APB1RSTR;
	__IO uint32_t APB2RSTR;
	__IO uint32_t RESERVED1[2];
	__IO uint32_t AHB1ENR;
	__IO uint32_t AHB2ENR;
	__IO uint32_t AHB3ENR;
	__IO uint32_t RESERVED2;
	__IO uint32_t APB1ENR;
	__IO uint32_t APB2ENR;
	__IO uint32_t RESERVED3[2];
	__IO uint32_t AHB1LPENR;
	__IO uint32_t AHB2LPENR;
	__IO uint32_t AHB3LPENR;
	__IO uint32_t RESERVED4;
	__IO uint32_t APB1LPENR;
	__IO uint32_t APB2LPENR;
	__IO uint32_t RESERVED5[2];
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
	__IO uint32_t RESERVED6[2];
	__IO uint32_t SSCGR;
	__IO uint32_t PLLI2SCFGR;

}RCC_Typedef_t;

#define RCC					((RCC_Typedef_t*)(RCC_BASE_ADDR))

/*
 * Bit Definitions
 */

#define RCC_AHB1ENR_GPIOAEN_Pos			(0U)
#define RCC_AHB1ENR_GPIOAEN_Msk			(0x1<<RCC_AHB1ENR_GPIOAEN_Pos)
#define RCC_AHB1ENR_GPIOAEN				RCC_AHB1ENR_GPIOAEN_Msk

#define RCC_AHB1ENR_GPIOBEN_Pos			(1U)
#define RCC_AHB1ENR_GPIOBEN_Msk			(0x1<<RCC_AHB1ENR_GPIOBEN_Pos)
#define RCC_AHB1ENR_GPIOBEN				RCC_AHB1ENR_GPIOBEN_Msk

#define RCC_AHB1ENR_GPIOCEN_Pos			(2U)
#define RCC_AHB1ENR_GPIOCEN_Msk			(0x1<<RCC_AHB1ENR_GPIOCEN_Pos)
#define RCC_AHB1ENR_GPIOCEN				RCC_AHB1ENR_GPIOCEN_Msk

#define RCC_AHB1ENR_GPIODEN_Pos			(3U)
#define RCC_AHB1ENR_GPIODEN_Msk			(0x1<<RCC_AHB1ENR_GPIODEN_Pos)
#define RCC_AHB1ENR_GPIODEN				RCC_AHB1ENR_GPIODEN_Msk

#define RCC_AHB1ENR_GPIOGEN_Pos			(6U)
#define RCC_AHB1ENR_GPIOGEN_Msk			(0x1<<RCC_AHB1ENR_GPIOGEN_Pos)
#define RCC_AHB1ENR_GPIOGEN				RCC_AHB1ENR_GPIOGEN_Msk


#include "RCC.h"


#endif /* INC_STM32F407XX_H_ */
