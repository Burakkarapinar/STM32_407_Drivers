/*
 * USART.c
 *
 *  Created on: 25 Haz 2023
 *      Author: Burak KARAPINAR
 */


#include "USART.h"

void USART_Init(USART_HandleTypedef_t *USART_Handle){
	uint32_t tempReg=0;
	uint32_t periphClock =0;
	uint32_t mantissaPart = 0;
	uint32_t fractionPart = 0;
	uint32_t USART_DIV_Value = 0;
	uint32_t tempValue = 0 ;
	tempReg = USART_Handle->Instance->CR1;

	tempReg |=(USART_Handle->Init.OverSampling) | (USART_Handle->Init.WordLength) | (USART_Handle->Init.Mode) |\
			(USART_Handle->Init.Parity);

	USART_Handle->Instance->CR1 = tempReg ;

	tempReg = USART_Handle->Instance->CR2;

	tempReg &= ~ (0x3U << USART_CR2_STOP);

	tempReg |= (USART_Handle->Init.StopBits);
	USART_Handle->Instance->CR2=tempReg;

	tempReg = USART_Handle->Instance->CR3;

	tempReg |=(USART_Handle->Init.HardWareFlowControl);
	USART_Handle->Instance->CR3 = tempReg;

	if (USART_Handle->Instance==USART1 || USART_Handle->Instance ==USART6 ){
		periphClock =RCC_GetPClock2();

	}
	else{
		periphClock =RCC_GetPClock1();
	}

	if(USART_Handle->Init.OverSampling ==USART_OVERSAMPLE8){
		USART_DIV_Value = __USART_BRR_OVERSAMPLING_8(periphClock,USART_Handle->Init.BaudRate);
		mantissaPart = USART_DIV_Value/100U;
		fractionPart = (USART_DIV_Value) - mantissaPart*100U;
		fractionPart = ( ( ( ( fractionPart * 8U) + 50U )/100U) & 0x07U );
	}
	else{
		USART_DIV_Value = __USART_BRR_OVERSAMPLING_16(periphClock,USART_Handle->Init.BaudRate);
		mantissaPart = USART_DIV_Value/100U;
		fractionPart = (USART_DIV_Value) - mantissaPart*100U;
		fractionPart = ( ( ( ( fractionPart * 16U) + 50U )/100U) & 0x0FU );
	}

	tempValue |=  (mantissaPart << 4U );
	tempValue |=  (fractionPart << 0U);

	USART_Handle->Instance->BRR=tempValue;
}

/*
 * @brief USART_TransmitData , Transmit the data
 * @param pData = address of data
 * @param dataSize = size of data
 * @retval void
 */


void USART_TransmitData(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t dataSize){

	uint16_t *data16Bits;

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity==USART_PARITY_NONE)){
		data16Bits = (uint16_t*)pData;

	}
	else{
		data16Bits = NULL;
	}

	while(dataSize>0){

		while( ! (USART_GetFlagStatus(USART_Handle,USART_TxE_Flag) ) );

		if (data16Bits == NULL){
			USART_Handle->Instance->DR=(uint8_t)(*pData &0xFFU);
			pData++;
			dataSize--;
		}
		else{
			USART_Handle->Instance->DR = (uint16_t)(*data16Bits & (0x1FFU));
			data16Bits++;
			dataSize-=2;

		}

	}
	while( ! (USART_GetFlagStatus(USART_Handle, USART_TC_Flag)));

}

/*
 * @brief USART_ReceiveData , Receive the data
 * @param pBuffer = Buffer address of data to store
 * @param dataSize = size of data, in bytes
 * @retval void
 */
void USART_ReceiveData(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t dataSize){
	uint16_t *p16BitsBuffer = NULL;
	uint8_t *p8BitsBuffer = NULL;

	if( (USART_Handle->Init.WordLength ==USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE) ){
		p16BitsBuffer = (uint16_t*)pBuffer;

	}
	else{
		p8BitsBuffer = (uint8_t*)pBuffer;
	}

	while(dataSize> 0 ){

		while( ! (USART_GetFlagStatus(USART_Handle, USART_RxNE_FLAG) ) );

		if (p8BitsBuffer==NULL){
			*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->DR & 0x01FFU);
			p16BitsBuffer++;
			dataSize-=2;
		}
		else{

			if((USART_Handle->Init.WordLength ==USART_WORDLENGTH_9BITS) && (USART_Handle->Init.Parity != USART_PARITY_NONE)){
				*p8BitsBuffer= (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
				p16BitsBuffer++;
				dataSize-=1;
			}
			else if ( (USART_Handle->Init.WordLength ==USART_WORDLENGTH_8BITS) && (USART_Handle->Init.Parity == USART_PARITY_NONE)){
				*p8BitsBuffer= (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
				p16BitsBuffer++;
				dataSize-=1;
			}
			else{
				*p8BitsBuffer= (uint8_t)(USART_Handle->Instance->DR & 0x007FU);
				p16BitsBuffer++;
				dataSize-=1;
			}
		}
	}


}


/*
 * @brief USART_GetFlagStatus , return the flag of SR register
 * @param USART_Handle = User Config Structer
 * @param flagName = flag name of SR register
 * @retval USART_FlagStatus
 */

USART_FlagStatus USART_GetFlagStatus(USART_HandleTypedef_t *USART_Handle,uint16_t flagName){

return ( ( USART_Handle->Instance->SR & flagName) ? USART_FLAG_SET : USART_FLAG_RESET ) ;
}


/*
 * @brief USART_PeriphCmd , Enable or Disable USART Perpheral
 * @param USART_Handle = User Config Structer
 * @param stateofUSART = ENABLE or DISABLE
 * @retval void
 */

void USART_PeriphCmd(USART_HandleTypedef_t *USART_Handle, FunctionalState_t stateofUSART){
if(stateofUSART ==ENABLE){
	USART_Handle->Instance->CR1 |=(0x1U << USART_CR1_UE);
}
else{
	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_UE);
}
}

static void closeUSART_ISR(USART_HandleTypedef_t *USART_Handle){
	USART_Handle->TxBufferSize = 0;
	USART_Handle->pTxBuffer = NULL;
	USART_Handle->TxStatus =USART_BUS_FREE;

	USART_Handle->Instance->CR1 &= ~(0x1U<<USART_CR1_TXEIE);

}


static USART_SendWith_IT(USART_HandleTypedef_t *USART_Handle){
 if ( (USART_Handle->Init.WordLength ==USART_WORDLENGTH_8BITS) && (USART_Handle->Init.Parity ==USART_PARITY_NONE) ){
	 uint16_t * p16BitsData  = (uint16_t*)(USART_Handle->pTxBuffer);
	 USART_Handle->Instance->DR = (uint16_t)(*p16BitsData & (uint16_t)0x01FF);
	 USART_Handle->pTxBuffer+=sizeof(uint16_t);
	 USART_Handle->TxBufferSize-=2;
 }
 else{
		USART_Handle->Instance->DR = (uint8_t)( * ( USART_Handle->pTxBuffer) & (uint8_t)0x00FF);
		USART_Handle->pTxBuffer++;
		USART_Handle->TxBufferSize--;
	 }

 if ( USART_Handle->TxBufferSize ==0){
	 closeUSART_ISR(USART_Handle);
 }

}


void USART_TransmitData_IT(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t dataSize){

	USAT_BustState_t usart_BusState= USART_Handle->TxStatus;


	if(usart_BusState !=USART_BUS_Tx){
		USART_Handle->pTxBuffer= (uint8_t*)pData;
		USART_Handle->TxBufferSize=(uint16_t)dataSize;
		USART_Handle->TxStatus=USART_BUS_Tx;
		USART_Handle->TxISR_Function = USART_SendWith_IT;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_TXEIE);

	}

}


static void closeUSART_ISR_RX(USART_HandleTypedef_t *USART_Handle){
	USART_Handle->RxBufferSize=0;
	USART_Handle->pRxBuffer = NULL;
	USART_Handle->RxStatus = USART_BUS_FREE;

	USART_Handle->Instance->CR1 &= ~(0X1 << USART_CR1_RxNEIE);

}

static void USART_ReceiveWith_IT(USART_HandleTypedef_t *USART_Handle){
uint16_t *p16BitsBuffer;
uint8_t *p8BitsBuffer;

	if( (USART_Handle->Init.WordLength == USART_WORDLENGTH_9BITS  ) &&  USART_Handle->Init.Parity == USART_PARITY_NONE){

		p16BitsBuffer= (uint16_t*)(USART_Handle->pRxBuffer);
		p8BitsBuffer = NULL;
	}
	else{
		p8BitsBuffer = (uint8_t*)USART_Handle->pRxBuffer;
		p16BitsBuffer = NULL;
	}
	if ( p8BitsBuffer == NULL){
	*p16BitsBuffer =(uint16_t)(USART_Handle->Instance->DR & 0x01FFU);
	USART_Handle->pRxBuffer+=sizeof(uint16_t);
	USART_Handle->RxBufferSize-=2;

	}
	else{
		if ( (USART_Handle->Init.WordLength ==USART_WORDLENGTH_9BITS ) && (USART_Handle->Init.Parity!=USART_PARITY_NONE) ){
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR& 0x00FFU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;
		}
		else if ((USART_Handle->Init.WordLength ==USART_WORDLENGTH_8BITS ) && (USART_Handle->Init.Parity!=USART_PARITY_NONE) ) {
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR& 0x00FFU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;
		}
		else {
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR& 0x007FU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;
		}
	}

	if(USART_Handle->RxBufferSize ==0){
		closeUSART_ISR_RX(&USART_Handle);
	}

	}

void USART_ReceiveData_IT(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t dataSize){
	USAT_BustState_t usart_BusState= USART_Handle->RxStatus;
	if (usart_BusState!= USART_BUS_Rx){
		USART_Handle->pRxBuffer= (uint8_t*)pBuffer;
		USART_Handle->RxBufferSize = (uint16_t)dataSize;
		USART_Handle->RxStatus = USART_BUS_Rx;
		USART_Handle->RxISR_Function = USART_ReceiveWith_IT;
		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_RxNEIE);
	}

}


void USART_InterruptHandle(USART_HandleTypedef_t *USART_Handle){
	uint8_t flagValue = 0;
	uint8_t interruptValue = 0;
	flagValue = (uint8_t*)( (USART_Handle->Instance->SR >> 7U ) & 0x1U );
	interruptValue = (uint8_t*)( (USART_Handle->Instance->CR1 >> 7U ) & 0x1U );
	if (flagValue && interruptValue){
		USART_Handle->TxISR_Function(USART_Handle);
	}
	flagValue =(uint8_t)( (USART_Handle->Instance->SR >>5U) & 0x1U ) ;
	interruptValue = (uint8_t)((USART_Handle->Instance->CR1 >> 5U) && 0x1U );

	if(flagValue && interruptValue){
		USART_Handle->RxISR_Function(USART_Handle);
	}

}

