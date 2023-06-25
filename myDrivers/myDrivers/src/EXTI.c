/*
 * EXTI.c
 *
 *  Created on: 18 Haz 2023
 *      Author: Burak KARAPINAR
 */


#include "EXTI.h"
#include <stdint.h>
#include "stm32f407xx.h"


/*
 * @brief EXTI_Init for valid GPIO port and Line number
 * @param EXTI_InitTypedef_t = User Config Structure
 * @retval void
 */

void EXTI_Init(EXTI_InitTypedef_t *EXTI_InitStruct){

	uint32_t tempValue = 0;
	tempValue = (uint32_t)(EXTI_BASE_ADRR);

	EXTI->IMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

	if(EXTI_InitStruct->EXTI_LineCmd != DISABLE ){
		tempValue += EXTI_InitStruct->EXTI_Mode;
		*((__IO uint32_t*)tempValue) |= (0x1U <<EXTI_InitStruct->EXTI_LineNumber);
		tempValue = (uint32_t)(EXTI_BASE_ADRR);

		EXTI->RTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber );
		EXTI->FTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber );

		if(EXTI_InitStruct->TriggerSelection==EXTI_Trigger_RF){

			EXTI->RTSR |= (0x1U <<EXTI_InitStruct-> EXTI_LineNumber);
			EXTI->FTSR |= (0x1U <<EXTI_InitStruct-> EXTI_LineNumber);

		}
		else{

			tempValue +=EXTI_InitStruct->TriggerSelection;
			*((__IO uint32_t*)tempValue) |= (0x1U<< EXTI_InitStruct->EXTI_LineNumber);
		}

	}
	else{
		tempValue = (uint32_t)(EXTI_BASE_ADRR);

		tempValue += EXTI_InitStruct->EXTI_Mode;

		*((__IO uint32_t*)tempValue) &= ~(0x1U <<EXTI_InitStruct->EXTI_LineNumber);

	}

}


/*
 * @brief GPIO_LineConfig , Configures the port and pin for SYSCFG
 * @param PortSource = Port Value A-I ,  @def_group Port_Values
 * @param *EXTI_LineSource = Line Value 0-15  @def_group Line_Values
 * @retval void
 */

void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource){

uint32_t tempValue;
tempValue = SYSCFG->EXTI_CR[EXTI_LineSource >> 2U];
tempValue &= ~(0xFU << (EXTI_LineSource & 0x3U) * 4);
tempValue= (PortSource << (EXTI_LineSource & 0x3U) * 4);
SYSCFG->EXTI_CR[EXTI_LineSource >> 2U] = tempValue;

}

/*
 * @brief NVIC_EnableInterrupt
 * @param IRQNumber = IRQ Number of Line
 * @retval void
 */
void NVIC_EnableInterrupt(IRQNumber_Typedef_t IRQNumber){
	uint32_t tempValue = 0;

	tempValue = *((IRQNumber >>5U) + NVIC_ISER0);
	tempValue &= ~(0x1U << (IRQNumber & 0x1FU));
	tempValue |= (0x1U << (IRQNumber & 0x1FU));
	*((IRQNumber >>5U) + NVIC_ISER0)=tempValue;


}



