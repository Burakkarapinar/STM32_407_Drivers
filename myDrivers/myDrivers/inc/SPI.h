/*
 * SPI.h
 *
 *  Created on: 22 Haz 2023
 *      Author: Burak KARAPINAR
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f407xx.h"

//@def_group SPI_BaudRate
#define SPI_BAUDRATE_DIV2		((uint32_t)(0X00000000))
#define SPI_BAUDRATE_DIV4		((uint32_t)(0X00000008))
#define SPI_BAUDRATE_DIV8		((uint32_t)(0X00000010))
#define SPI_BAUDRATE_DIV16		((uint32_t)(0X00000018))
#define SPI_BAUDRATE_DIV32		((uint32_t)(0X00000020))
#define SPI_BAUDRATE_DIV64		((uint32_t)(0X00000028))
#define SPI_BAUDRATE_DIV128		((uint32_t)(0X00000030))
#define SPI_BAUDRATE_DIV256		((uint32_t)(0X00000038))


//@def_group SPI_CPHA

#define SPI_CPHA_FIRST 		((uint32_t)(0x00000000))
#define SPI_CPHA_SECOND		((uint32_t)(0x00000001))

//@def_group SPI_CPOL
#define SPI_CPOL_LOW		((uint32_t)(0x00000000))
#define SPI_CPOL_HIGH		((uint32_t)(0x00000002))

//@def_group SPI_DFF
#define SPI_DFF_8BITS		((uint32_t)(0x00000000))
#define SPI_DFF_16BITS		((uint32_t)(0x00000800))

//@def_group SPI_Mode
#define SPI_MODE_MASTER		((uint32_t)(0x00000004))
#define SPI_MODE_SLAVE		((uint32_t)(0x00000000))


//@def_group SPI_FrameFormat
#define SPI_FRAMEFORMAT_MSB ((uint32_t)(0x00000000))
#define SPI_FRAMEFORMAT_LSB ((uint32_t)(0x00000080))

//@def_group SPI_BusConfig
#define SPI_BUS_FULLDUPLEX			((uint32_t)(0x00000000))
#define SPI_BUS_RECEIVEONLY			((uint32_t)(0x00000400))
#define SPI_BUS_HALFDUPLEX_T		((uint32_t)(0x0000C000))
#define SPI_BUS_HALFDUPLEX_R		((uint32_t)(0x00008000))

//@def_group SPI_SSM_Cmd
#define SPI_SSM_DISABLE				((uint32_t)(0x00000000))
#define SPI_SSM_ENABLE				((uint32_t)(0x00000300))


typedef enum{
	SPI_FLAG_RESET = 0X0U,
	SPI_FLAG_SET =!SPI_FLAG_RESET

}SPI_FlagSTatus_t;


typedef struct{
	uint32_t Mode;				//Mode Values @def_group SPI_Mode
	uint32_t CPHA;				//CPHA Values @def_group SPI_CPHA
	uint32_t CPOL;				//CPOL Values @def_group SPI_CPOL
	uint32_t BaudRate;			//Baudrate Values @def_group SPI_BaudRate
	uint32_t SSM_Cmd;			//SSM_Cmd Values @def_group SPI_SSM_Cmd
	uint32_t DFF_Format;		//DFF Values @def_group SPI_DFF
	uint32_t BusConfig;			//BusConfig Values @def_group SPI_BusConfig
	uint32_t FrameFormat;		//FrameFormat Values @def_group SPI_FrameFormat

}SPI_InitTypedef_t;





typedef struct __SPI_HandleTypedef_t{

	SPI_Typedef_t *Instance;
	SPI_InitTypedef_t Init;
	uint8_t *ptxDataAddr;
	uint16_t TxDataSize;
	uint8_t busStateTx;
	void(*TxISRFunction)(struct __SPI_HandleTypedef_t *SPI_Handle);

}SPI_HandleTypedef_t;

void SPI_Init(SPI_HandleTypedef_t * SPI_Handle);
void SPI_PeriphCmd(SPI_HandleTypedef_t * SPI_Handle, FunctionalState_t stateOfSPI);
void SPI_TransmitData(SPI_HandleTypedef_t * SPI_Handle, uint8_t *pData, uint16_t sizeOfData );
SPI_FlagSTatus_t SPI_GetFlagStatus(SPI_HandleTypedef_t * SPI_Handle, uint16_t SPI_Flag);
void SPI_ReceiveData(SPI_HandleTypedef_t * SPI_Handle,uint8_t *pBuffer, uint16_t sizeOfData);
void SPI_InterruptHandler(SPI_HandleTypedef_t *SPI_Handle);
void SPI_TransMitData_IT(SPI_HandleTypedef_t * SPI_Handle, uint8_t *pData, uint16_t sizeOfData );

#endif /* INC_SPI_H_ */
