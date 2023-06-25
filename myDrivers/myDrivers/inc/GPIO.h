/*
 * GPIO.h
 *
 *  Created on: 20 May 2023
 *      Author: Burak KARAPINAR
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_
#include "stm32f407xx.h"

/*
 * @def_group GPIO_Pins
 */

#define GPIO_PIN_0			(uint16_t)(0x0001)
#define GPIO_PIN_1			(uint16_t)(0x0002)
#define GPIO_PIN_2			(uint16_t)(0x0004)
#define GPIO_PIN_3			(uint16_t)(0x0008)
#define GPIO_PIN_4			(uint16_t)(0x0010)
#define GPIO_PIN_5			(uint16_t)(0x0020)
#define GPIO_PIN_6			(uint16_t)(0x0040)
#define GPIO_PIN_7			(uint16_t)(0x0080)
#define GPIO_PIN_8			(uint16_t)(0x0100)
#define GPIO_PIN_9			(uint16_t)(0x0200)
#define GPIO_PIN_10			(uint16_t)(0x0400)
#define GPIO_PIN_11			(uint16_t)(0x0800)
#define GPIO_PIN_12			(uint16_t)(0x1000)
#define GPIO_PIN_13			(uint16_t)(0x2000)
#define GPIO_PIN_14			(uint16_t)(0x4000)
#define GPIO_PIN_15			(uint16_t)(0x8000)
#define GPIO_PIN_All		(uint16_t)(0xFFFF)

/*
 * @def_group GPIO_Pin_Modes
 */
#define GPIO_MODE_INPUT 		(0x0U)
#define GPIO_MODE_OUTPUT 		(0x1U)
#define GPIO_MODE_AF 			(0x2U)
#define GPIO_MODE_ANALOG 		(0x3U)

/*
 * @def_group GPIO_OTYPE_Modes
 */
#define GPIO_OTYPE_PP			(0x0U)
#define GPIO_TYPE_OD			(0x1U)

/*
 * @def_group GPIO_PUPD_Modes
 */
#define GPIO_PUPD_NOPULL 	(0x0U)
#define GPIO_PUPD_PULLUP 	(0x1U)
#define GPIO_PUPD_PULLDOWN 	(0x2U)

/*
 * @def_group GPIO_SPEED_Modes
 */
#define GPIO_SPEED_LOW				(0X0U)
#define GPIO_SPEED_MEDIUM			(0X1U)
#define GPIO_SPEED_HIGH				(0X2U)
#define GPIO_SPEED_VERY				(0X3U)

/*
 * @def_group GPIO_AF_Modes
 */

#define GPIO_AF0			(0x0U)
#define GPIO_AF1			(0x1U)
#define GPIO_AF2			(0x2U)
#define GPIO_AF3			(0x3U)
#define GPIO_AF4			(0x4U)
#define GPIO_AF5			(0x5U)
#define GPIO_AF6			(0x6U)
#define GPIO_AF7			(0x7U)
#define GPIO_AF8			(0x8U)
#define GPIO_AF9			(0x9U)
#define GPIO_AF10			(0xAU)
#define GPIO_AF11			(0xBU)
#define GPIO_AF12			(0xCU)
#define GPIO_AF13			(0xDU)
#define GPIO_AF14			(0xEU)
#define GPIO_AF15			(0xFU)

typedef struct{

	uint32_t pinNumber; 	/*!>GPIO Pin Numbers @def_group GPIO_Pins */
	uint32_t Mode;			/*!>GPIO Pin Numbers @def_group GPIO_Pin_Modes */
	uint32_t Otype;			/*!>GPIO Pin Numbers @def_group GPIO_OTYPE_Modes */
	uint32_t PuPd;			/*!>GPIO Pin Numbers @def_group GPIO_PUPD_Modes */
	uint32_t Speed;			/*!>GPIO Pin Numbers @def_group GPIO_SPEED_Modes */
	uint32_t Alternate;		/*!>GPIO Pin Numbers @def_group GPIO_AF_Modes */


}GPIO_Init_Typedef_t;



typedef enum{
	GPIO_Pin_Reset = 0x0U,
	GPIO_Pin_Set= !GPIO_Pin_Reset
} GPIO_Pin_State_t;


void GPIO_Init(GPIO_Typedef_t *GPIOx, GPIO_Init_Typedef_t *GPIO_ConfigStruct);
void GPIO_WritePin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber, GPIO_Pin_State_t pinstate);
GPIO_Pin_State_t GPIO_ReadPin(GPIO_Typedef_t *GPIOx,uint16_t pinNumber);
void GPIO_LockPin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber);
void GPIO_TogglePin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber);




#endif /* INC_GPIO_H_ */
