/*
 * RCC.c
 *
 *  Created on: 20 May 2023
 *      Author: Burak KARAPINAR
 */
#include "RCC.h"

const uint8_t AHB_Prescaler[] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};
const uint8_t APB_Prescaler[] = {0,0,0,0,1,2,3,4};

uint32_t	RCC_GetSystemClock(){
	uint32_t SystemCoreClock = 0;
	uint8_t ClkSource = 0;

	ClkSource= (RCC->CFGR>>2U) & (0x3U);
	switch(ClkSource){
	case 0: SystemCoreClock = 16000000;break;
	case 1: SystemCoreClock =  8000000;break;
	default : SystemCoreClock =16000000;
	}

	return SystemCoreClock;
}

uint32_t	RCC_GetHClock(){
	uint32_t AHBPeriphClock = 0;
	uint32_t SystemCoreClock = 0;
	uint8_t tempVal;
	SystemCoreClock = RCC_GetSystemClock();

	uint8_t HPRE_Value = 0;

	HPRE_Value = (RCC->CFGR >> 4U) & 0xFU;
	tempVal = AHB_Prescaler[HPRE_Value];

	AHBPeriphClock = (SystemCoreClock >> tempVal);
	return AHBPeriphClock;
}


uint32_t	RCC_GetPClock1(){
	uint32_t APB1PeriphClock = 0;
	uint32_t HClock = 0;
	uint8_t HPRE1_Value = 0;
	uint8_t tempValue;
	HClock = RCC_GetHClock();
	HPRE1_Value = (RCC->CFGR>>10U) & 0x7U;

	tempValue = APB_Prescaler[HPRE1_Value];
	APB1PeriphClock = HClock>>tempValue;
	return APB1PeriphClock;


}

uint32_t	RCC_GetPClock2(){
	uint32_t APB2PeriphClock = 0;
	uint32_t HClock = 0;
	uint8_t HPRE2_Value = 0;
	uint8_t tempValue;
	HClock = RCC_GetHClock();

	HPRE2_Value = (RCC->CFGR >> 13U ) & 0x7U;
	tempValue = APB_Prescaler[HPRE2_Value];
	APB2PeriphClock = HClock>>tempValue;
	return APB2PeriphClock;
}
