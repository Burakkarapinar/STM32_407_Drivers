/*
 * EXTI.c
 *
 *  Created on: 18 Haz 2023
 *      Author: Burak KARAPINAR
 */


#include "EXTI.h"


/*
 * @brief GPIO_LineConfig , Configures the port and pin for SYSCFG
 * @param PortSource = Port Value A-I ,  @def_group Port_Values
 * @param *EXTI_LineSource = Line Value 0-15  @def_group Line_Values
 * @retval void
 */

void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource){

uint32_t tempValue;
tempValue = SYSCFG->EXTI_CR[EXTI_LineSource>>2U];
tempValue &= ~(0xFU<<(EXTI_LineSource &0X3U) *4);
tempValue = (PortSource<< (EXTI_LineSource & 0x3U) *4 );
SYSCFG->EXTI_CR[PortSource>>2U]=tempValue;



}
