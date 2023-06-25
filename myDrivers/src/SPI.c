/*
 * SPI.c
 *
 *  Created on: 22 Haz 2023
 *      Author: Burak KARAPINAR
 */
#include "SPI.h"

static void SPI_CLoseISR_TX(SPI_HandleTypedef_t *SPI_Handle){

	SPI_Handle->Instance->CR2 &= ~(0x1U <<SPI_CR2_TXEIE);
	SPI_Handle->TxDataSize = 0;
	SPI_Handle->ptxDataAddr = NULL;
	SPI_Handle->busStateTx=SPI_BUS_FREE;
}


static void SPI_TransmitHelper_16Bits(SPI_HandleTypedef_t *SPI_Handle){

	SPI_Handle->Instance->DR=*( (uint16_t* )(SPI_Handle->ptxDataAddr) );
	SPI_Handle->ptxDataAddr +=sizeof(uint16_t);
	SPI_Handle->TxDataSize-=2;

}

static void SPI_TransmitHelper_8Bits(SPI_HandleTypedef_t *SPI_Handle){
	SPI_Handle->Instance->DR=*( (uint8_t* )(SPI_Handle->ptxDataAddr) );
	SPI_Handle->ptxDataAddr +=sizeof(uint8_t);
	SPI_Handle->TxDataSize-=2;

	if(SPI_Handle->TxDataSize ==0){
		SPI_CLoseISR_TX(SPI_Handle);
	}
}

void SPI_InterruptHandler(SPI_HandleTypedef_t *SPI_Handle){
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;

	interruptSource = SPI_Handle->Instance->CR2 &(0x1U << SPI_CR2_TXEIE);
	interruptFlag =SPI_Handle->Instance->SR & ( 0x1U << SPI_SR_TxE);

	if((interruptSource != 0) && (interruptFlag!=0)){

		SPI_Handle->TxISRFunction(SPI_Handle);

	}
}


/*
 * @brief SPI_Init , init SPI
 * @param SPI_HandleTypedef_t = User Config Structure
 *
 * @retval void
 */

void SPI_Init(SPI_HandleTypedef_t * SPI_Handle){

	uint32_t tempValue =0;
	tempValue =SPI_Handle->Instance->CR1;
	tempValue |=(SPI_Handle->Init.BaudRate)  | (SPI_Handle->Init.CPHA) | (SPI_Handle->Init.CPOL) | (SPI_Handle->Init.DFF_Format)
				| (SPI_Handle->Init.Mode) | (SPI_Handle->Init.FrameFormat) | (SPI_Handle->Init.BusConfig) | (SPI_Handle->Init.SSM_Cmd);

	SPI_Handle->Instance->CR1 = tempValue;

}


/*
 * @brief SPI_PeriphCmd , Enable or Disable SPI Peripheral
 * @param SPI_HandleTypedef_t = User Config Structure
 * @param FunctionalState_t, stateOfSPI, ENABLE, DISABLE
 * @retval void
 */
void SPI_PeriphCmd(SPI_HandleTypedef_t * SPI_Handle, FunctionalState_t stateOfSPI){

	if(stateOfSPI == ENABLE){
		SPI_Handle->Instance->CR1 | (0x1U <<SPI_CR1_SPE);

	}
	else{
		SPI_Handle->Instance->CR1 &= ~ (0x1U <<SPI_CR1_SPE);
	}

}


/*
 * @brief SPI_TransmitData , Transmits data to the slave
 * @param SPI_HandleTypedef_t = User Config Structure
 * @param pData, Address of data to send
 * @param sizeOfData, size of Data
 * @retval void
 */

void SPI_TransmitData(SPI_HandleTypedef_t * SPI_Handle, uint8_t *pData, uint16_t sizeOfData ){

	if(SPI_Handle->Init.DFF_Format ==SPI_DFF_16BITS){

		while(sizeOfData>0){

			if(SPI_GetFlagStatus(SPI_Handle, SPI_TxE_FLAG)){

				SPI_Handle->Instance->DR = *((uint16_t*)pData );
				pData+=sizeof(uint16_t);
				sizeOfData-=2;

			}

		}

	}
	else{

		while(sizeOfData>0){

			if((SPI_Handle->Instance->SR >> 1U) & 0x1U){
					SPI_Handle->Instance->DR = *pData;
					pData++;
					sizeOfData--;

				}

				}

	}

	while(SPI_GetFlagStatus(SPI_Handle, SPI_Busy_FLAG)); //Wait for busy flag


}

/*
 * @brief SPI_GetFlagStatus , Transmits data to the slave
 * @param SPI_HandleTypedef_t = User Config Structure
 * @param pData, Address of data to send
 * @param sizeOfData, size of Data
 * @retval SPI_FlagSTatus_t
 */

SPI_FlagSTatus_t SPI_GetFlagStatus(SPI_HandleTypedef_t * SPI_Handle, uint16_t SPI_Flag){

	return (SPI_Handle->Instance->SR & SPI_Flag) ? SPI_FLAG_SET : SPI_FLAG_RESET;

}


void SPI_ReceiveData(SPI_HandleTypedef_t * SPI_Handle,uint8_t *pBuffer, uint16_t sizeOfData){

	if (SPI_Handle->Init.DFF_Format==SPI_DFF_16BITS){

		while(sizeOfData>0){
			if(SPI_GetFlagStatus(SPI_Handle, SPI_RxNE_FLAG)){

				*((uint16_t*)pBuffer) =(uint16_t)SPI_Handle->Instance->DR;
				pBuffer +=sizeof(uint16_t);
				sizeOfData-=2;

			}
		}
	}
	else{

		while(sizeOfData>0){
			if(SPI_GetFlagStatus(SPI_Handle, SPI_RxNE_FLAG)){
				*(pBuffer) =(*(__IO uint8_t*)&SPI_Handle->Instance->DR);
					pBuffer +=sizeof(uint8_t);
					sizeOfData-=1;


			}
		}
	}
}


void SPI_TransMitData_IT(SPI_HandleTypedef_t * SPI_Handle, uint8_t *pData, uint16_t sizeOfData ){

	SPI_BusStatus_t busState = SPI_Handle->busStateTx;

	if(busState != SPI_BUS_BUSY_TX){
		SPI_Handle->ptxDataAddr = (uint8_t*)pData ;
		SPI_Handle->TxDataSize = (uint16_t*)sizeOfData;
		SPI_Handle->busStateTx=SPI_BUS_BUSY_TX;

		if(SPI_Handle->Instance->CR1 & (0x1U <<SPI_CR1_DFF)){
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_16Bits;
		}
		else{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_8Bits;
		}

		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE);


	}




}


