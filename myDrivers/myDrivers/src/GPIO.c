/*
 * GPIO.c
 *
 *  Created on: 20 May 2023
 *      Author: Burak KARAPINAR
 */

#include "GPIO.h"

/*
 * @brief GPIO_Init , init GPIO
 * @param GPIOx = GPIO_Port_Base_Adress
 * @param *GPIO_ConfigStruct = GPIO_Init_Typedef_t
 * @retval void
 */
void GPIO_Init(GPIO_Typedef_t *GPIOx, GPIO_Init_Typedef_t *GPIO_ConfigStruct){

	uint32_t position = 0;
	uint32_t fakePosition = 0;
	uint32_t lastPosition = 0;

	for(;position<16;position++){
		fakePosition = (0x1 << position);
		lastPosition = (uint32_t)(GPIO_ConfigStruct->pinNumber) & fakePosition;

		if(fakePosition ==lastPosition){
			/** Mode Config*/
			uint32_t tempValue = GPIOx->MODER;
			tempValue &= ~(0x3U << (position * 2));
			tempValue |= (GPIO_ConfigStruct->Mode <<(position * 2));
			GPIOx->MODER = tempValue;

			if( GPIO_ConfigStruct->Mode ==GPIO_MODE_INPUT || GPIO_ConfigStruct->Mode==GPIO_MODE_ANALOG){
				//Output Type Config

				tempValue= GPIOx->OTYPER;
				tempValue &=~ (0x1U <<position);
				tempValue |=(GPIO_ConfigStruct->Otype<<position);
				GPIOx->OTYPER=tempValue;

				//Output Speed Config
				tempValue=GPIOx->OSPEEDR;
				tempValue &=~(0X3U<<(position*2));
				tempValue |=(GPIO_ConfigStruct->Speed<<(position*2));

			}
			//Push pull config
			tempValue =GPIOx->PUPDR;
			tempValue &=~(0X3U<<(position*2));
			tempValue |=(GPIO_ConfigStruct->PuPd<<(position*2));
			GPIOx->PUPDR = tempValue;

			if(GPIO_ConfigStruct->Mode ==GPIO_MODE_AF){
				tempValue=GPIOx->AFR[position >>3U];
				tempValue &= ~ (0xFU<<( (position & 0x7U) * 4) );
				tempValue |= (GPIO_ConfigStruct->Alternate << ( (position & 0x7U) * 4 ) );
				GPIOx->AFR[position >>3U] = tempValue;
			}


		}



	}

}






/*
 * @brief GPIO_Write_Pin ,  makes pin high or low
 * @param GPIOx = GPIO_Port_Base_Adress
 * @param pinNumber = GPIO_PİN_Numbers 0-15
 * @param pinState = GPIO_Pin_Set or GPIO_Pin_Reset
 * @retval void
 */
void GPIO_WritePin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber, GPIO_Pin_State_t pinState){

	if (pinState ==GPIO_Pin_Set){
		GPIOx->BSRR = pinNumber;

	}
	else{
		GPIOx->BSRR = (pinNumber <<16U);

	}
}

/*
 * @brief GPIO_ReadPin ,  read pin
 * @param GPIOx = GPIO_Port_Base_Adress
 * @param pinNumber = GPIO_PİN_Numbers 0-15
 * @retval GPIO_Pin_State_t
 */

GPIO_Pin_State_t GPIO_ReadPin(GPIO_Typedef_t *GPIOx,uint16_t pinNumber){

	GPIO_Pin_State_t bitStatus = GPIO_Pin_Reset;

	if((GPIOx->IDR &pinNumber) != GPIO_Pin_Reset){
		bitStatus = GPIO_Pin_Set;
	}
	return bitStatus;

}

/*
 * @brief GPIO_LockPin ,  lock pin
 * @param GPIOx = GPIO_Port_Base_Adress
 * @param pinNumber = GPIO_PİN_Numbers 0-15
 * @retval void
 */

void GPIO_LockPin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber){

	uint32_t tempValue = (0x1U <<16U) | pinNumber;
	GPIOx->LCKR = tempValue;	//LCKR[16] ='1'	LCKR[15:0] = DATA
	GPIOx->LCKR = pinNumber;	//LCKR[16] ='0'	LCKR[15:0] = DATA
	GPIOx->LCKR = tempValue;	//LCKR[16] ='1'	LCKR[15:0] = DATA
	tempValue =GPIOx->LCKR;		//Read Lock Register
}

/*
 * @brief GPIO_TogglePin ,  toggle pin
 * @param GPIOx = GPIO_Port_Base_Adress
 * @param pinNumber = GPIO_PİN_Numbers 0-15
 * @retval void
 */

void GPIO_TogglePin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber){
	uint32_t tempODRegister = GPIOx->ODR;
	GPIOx->BSRR =((tempODRegister &pinNumber)<<16U) | (~tempODRegister & pinNumber);

}




