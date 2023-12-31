
#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>
#include <string.h>

/*
 * Microprocessor Defines
 */

#define NVIC_ISER0			((uint32_t*)(0xE000E100))



/*
 * IRQ Numbers of MCU ==Vector Table
 */
typedef enum{
	EXTI0_IRQNumber = 6,
	EXTI1_IRQNumber = 7,
	EXTI2_IRQNumber = 8,
	EXTI3_IRQNumber = 9,
	SPI1_IRQNumber = 35,
	USART2_IRQNumber = 38

}IRQNumber_Typedef_t;

#define SET_BIT(REG,BIT)		((REG) |= 	(BIT))
#define CLEAR_BIT(REG,BIT)		((REG) &=~ 	(BIT))
#define READ_BIT(REG,BIT)		((REG) & 	(BIT))
#define UNUSED(x)				(void)x
/*
 * Memory Base Address
 */

typedef enum{
	DISABLE = 0x0U,
	ENABLE =!DISABLE
}FunctionalState_t;


#define FLASH_BASE_ADDR				(0X08000000UL)	/* Flash Base Adress 1MB 	*/
#define SRAM1_BASE_ADDR				(0x20000000UL)	/* SRAM1 Base Adress 112 KB	*/
#define SRAM2_BASE_ADDR				(0x2001C000UL)	/* SRAM2 Base Adress 16 KB	*/

/*
 * Peripheral Base Addresses
 */

#define PERIPH_BASE_ADDR			(0X40000000UL)
#define	APB1_BASE_ADDR				PERIPH_BASE_ADDR
#define	APB2_BASE_ADDR				(PERIPH_BASE_ADDR+0x10000UL)
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
#define UART4_BASE_ADDR				(APB1_BASE_ADDR+0X4C00UL)
#define UART5_BASE_ADDR				(APB1_BASE_ADDR+0X5000UL)

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
#define EXTI_BASE_ADRR				(APB2_BASE_ADDR+0X3C00UL)


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
	__IO uint32_t SR;		/* USART Status register 							Address Offset = 0x00			*/
	__IO uint32_t DR;		/* USART Data register 								Address Offset = 0x04			*/
	__IO uint32_t BRR;		/* USART Baud rate register							Address Offset = 0x08			 */
	__IO uint32_t CR1;		/* USART Control register 1 						Address Offset = 0x0C			*/
	__IO uint32_t CR2;		/* USART Control register 2 						Address Offset = 0x10			*/
	__IO uint32_t CR3;		/* USART Control register 3 						Address Offset = 0x14			*/
	__IO uint32_t GTPR;		/* USART Guard time and prescaler register			Address Offset = 0x18			 */


}USART_Typedef_t;

#define 	USART2		((USART_Typedef_t*)(USART2_BASE_ADDR))
#define 	USART3		((USART_Typedef_t*)(USART3_BASE_ADDR))
#define 	UART4		((USART_Typedef_t*)(UART4_BASE_ADDR))
#define 	UART5		((USART_Typedef_t*)(UART5_BASE_ADDR))

#define 	USART1		((USART_Typedef_t*)(USART1_BASE_ADRR))
#define 	USART6		((USART_Typedef_t*)(USART6_BASE_ADRR))

#define USART_CR2_STOP	(12U)

typedef struct{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];
}GPIO_Typedef_t;


typedef struct{

	__IO uint32_t MEMRMP;			//SYSCFG memory remap register (SYSCFG_MEMRMP					Address Offset = 0x00
	__IO uint32_t PMC;				//SYSCFG peripheral mode configuration register (SYSCFG_PMC		Address Offset = 0x04
	__IO uint32_t EXTI_CR[4];		//SYSCFG external interrupt configuration register				Address Offset = 0x08
	__IO uint32_t CMPCR;			//Compensation cell control register (SYSCFG_CMPCR				Address Offset = 0x20

}SYSCFG_Typedef_t;

typedef enum{
	SPI_BUS_FREE = 0x0U,
	SPI_BUS_BUSY_TX = 0x1U,
	SPI_BUS_BUSY_RX = 0x2U
}SPI_BusStatus_t;

typedef struct{
	__IO uint32_t IMR;				//Interrupt mask register (EXTI_IMR								Address Offset = 0x00
	__IO uint32_t EMR;				//Event mask register (EXTI_EMR)								Address Offset = 0x04
	__IO uint32_t RTSR;				//Rising trigger selection register (EXTI_RTSR					Address Offset = 0x08
	__IO uint32_t FTSR;				//Falling trigger selection register (EXTI_FTSR					Address Offset = 0x0C
	__IO uint32_t SWIER;			//Software interrupt event register (EXTI_SWIER					Address Offset = 0x10
	__IO uint32_t PR;				//Pending register (EXTI_PR										Address Offset = 0x14

}EXTI_Typedef_t;

typedef struct{
	__IO uint32_t CR1;				//SPI control register 1 				Address offset: 0x00
	__IO uint32_t CR2;				//SPI control register 1 				Address offset: 0x04
	__IO uint32_t SR;				//SPI status register					Address offset: 0x08
	__IO uint32_t DR;				//SPI data register						Address offset: 0x0C
	__IO uint32_t CRCPR;			//SPI CRC polynomial register			Address offset: 0x10
	__IO uint32_t RXCRCR;			//SPI RX CRC register					Address offset: 0x14
	__IO uint32_t TXCRCR;			//SPI TX CRC register					Address offset: 0x18
	__IO uint32_t I2SCFGR;			//SPI_I2S configuration register 		Address offset: 0x1C
	__IO uint32_t I2SPR;			//SPI_I2S prescaler register			Address offset: 0x20

}SPI_Typedef_t;


#define SPI1			((SPI_Typedef_t*)(SPI1_BASE_ADRR))
#define SPI2			((SPI_Typedef_t*)(SPI1_BASE_ADRR))
#define SPI3			((SPI_Typedef_t*)(SPI1_BASE_ADRR))
#define SPI4 			((SPI_Typedef_t*)(SPI1_BASE_ADRR))

#define EXTI			((EXTI_Typedef_t*)(EXTI_BASE_ADRR))
#define SYSCFG			((SYSCFG_Typedef_t*)SYSCFG_BASE_ADRR)



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

#define RCC_APB2ENR_SYSCFGEN_Pos		(14U)
#define RCC_APB2ENR_SYSCFGEN_Msk		(0x1U<<RCC_APB2ENR_SYSCFGEN_Pos)
#define RCC_APB2ENR_SYSCFGEN			RCC_APB2ENR_SYSCFGEN_Msk

#define RCC_APB2ENR_SPI1EN_Pos			(12U)
#define RCC_APB2ENR_SPI1EN_Msk			(0x1U<<RCC_APB2ENR_SPI1EN_Pos)
#define RCC_APB2ENR_SPI1EN				RCC_APB2ENR_SPI1EN_Msk

#define RCC_APB2ENR_SPI4EN_Pos			(13U)
#define RCC_APB2ENR_SPI4EN_Msk			(0x1U<<RCC_APB2ENR_SPI4EN_Pos)
#define RCC_APB2ENR_SPI4EN				RCC_APB2ENR_SPI4EN_Msk


#define RCC_APB1ENR_SPI2EN_Pos			(14U)
#define RCC_APB1ENR_SPI2EN_Msk			(0x1U<<RCC_APB1ENR_SPI2EN_Pos)
#define RCC_APB1ENR_SPI2EN				RCC_APB1ENR_SPI2EN_Msk


#define RCC_APB1ENR_SPI3EN_Pos			(15U)
#define RCC_APB1ENR_SPI3EN_Msk			(0x1U<<RCC_APB1ENR_SPI3EN_Pos)
#define RCC_APB1ENR_SPI3EN				RCC_APB1ENR_SPI3EN_Msk

#define RCC_APB1ENR_USART2_Pos			(17U)
#define RCC_APB1ENR_USART2_Msk			(0x1U << RCC_APB1ENR_USART2_Pos)
#define RCC_APB1ENR_USART2EN			RCC_APB1ENR_USART2_Msk



#define SPI_CR1_SPE						(6U)
#define SPI_CR1_DFF						(11U)
#define SPI_SR_TxE						(1U)
#define SPI_SR_Busy						(7U)
#define SPI_SR_RxNE						(0U)
#define SPI_CR2_TXEIE					(7U)
#define USART_SR_TxE					(7U)
#define USART_SR_TC						(6U)
#define	USART_SR_RxNe					(5U)

#define USART_CR1_UE					(13U)
#define UART_CR2_STOP					(12U)
#define USART_CR1_RxNEIE				(5U)
#define USART_CR1_TXEIE					(7U)


/*
 * Flag Definitions
 */

#define SPI_TxE_FLAG					((0x1) << SPI_SR_TxE)
#define SPI_Busy_FLAG					((0x1) << SPI_SR_Busy)
#define SPI_RxNE_FLAG					((0x1) << SPI_SR_RxNE)

#define USART_TxE_Flag					((0x1) << USART_SR_TxE)
#define USART_TC_Flag					((0x1) << USART_SR_TC)
#define USART_RxNE_FLAG					((0x1) << USART_SR_RxNe)


#include "RCC.h"
#include "GPIO.h"
#include "EXTI.h"
#include "SPI.h"
#include "USART.h"
#endif /* INC_STM32F407XX_H_ */
