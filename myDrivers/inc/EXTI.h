/*
 * EXTI.h
 *
 *  Created on: 18 Haz 2023
 *      Author: Burak KARAPINAR
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "stm32f407xx.h"
//@def_group Port_Values
#define EXTI_PortSource_GPIOA		((uint8_t)(0x0))
#define EXTI_PortSource_GPIOB		((uint8_t)(0x1))
#define EXTI_PortSource_GPIOC		((uint8_t)(0x2))
#define EXTI_PortSource_GPIOD		((uint8_t)(0x3))
#define EXTI_PortSource_GPIOE		((uint8_t)(0x4))
#define EXTI_PortSource_GPIOF		((uint8_t)(0x5))
#define EXTI_PortSource_GPIOG		((uint8_t)(0x6))
#define EXTI_PortSource_GPIOH		((uint8_t)(0x7))



//@def_group Line_Values
#define EXTI_LineSource_0			((uint8_t)(0x0))
#define EXTI_LineSource_1			((uint8_t)(0x1))
#define EXTI_LineSource_2			((uint8_t)(0x2))
#define EXTI_LineSource_3			((uint8_t)(0x3))
#define EXTI_LineSource_4			((uint8_t)(0x4))
#define EXTI_LineSource_5			((uint8_t)(0x5))
#define EXTI_LineSource_6			((uint8_t)(0x6))
#define EXTI_LineSource_7			((uint8_t)(0x7))
#define EXTI_LineSource_8			((uint8_t)(0x8))
#define EXTI_LineSource_9			((uint8_t)(0x9))
#define EXTI_LineSource_10			((uint8_t)(0xA))
#define EXTI_LineSource_11			((uint8_t)(0xB))
#define EXTI_LineSource_12			((uint8_t)(0xC))
#define EXTI_LineSource_13			((uint8_t)(0xD))
#define EXTI_LineSource_14			((uint8_t)(0xE))
#define EXTI_LineSource_15			((uint8_t)(0xF))

void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource);


/*
 * @defgroup EXTI_Modes
 */
#define EXTI_MODE_Interrupt			(0x00U)
#define EXTI_MODE_Event				(0x04U)

/*
 * @def_group EXTI_Trigger_Modes
 */
#define EXTI_Trigger_Rising			(0x08U)
#define EXTI_Trigger_Falling		(0x0CU)
#define EXTI_Trigger_RF				(0x10U)



typedef struct{

	uint8_t EXTI_LineNumber;			//EXTI Line number for valid GPIO pin @defgroup Line_Values
	uint8_t TriggerSelection;			// EXTI Trigger Selection values @def_group EXTI_Trigger_Modes
	uint8_t EXTI_Mode;					// EXTI Mode Value @defgroup EXTI_Modes
	FunctionalState_t EXTI_LineCmd;		//Mask or Unmask the Line Number
}EXTI_InitTypedef_t;


void EXTI_Init(EXTI_InitTypedef_t *EXTI_InitStruct);
void NVIC_EnableInterrupt(IRQNumber_Typedef_t IRQNumber);









#endif /* INC_EXTI_H_ */
