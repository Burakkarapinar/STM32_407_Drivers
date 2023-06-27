/*
 * USART.h
 *
 *  Created on: 25 Haz 2023
 *      Author: Burak KARAPINAR
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include "USART.h"
#include "stm32f407xx.h"


typedef enum {
	USART_FLAG_RESET = 0x0U,
	USART_FLAG_SET = ! (USART_FLAG_RESET)

}USART_FlagStatus;

typedef enum{
	USART_BUS_FREE 	=	0x0U,
	USART_BUS_Tx	=	0x1U,
	USART_BUS_Rx	=	0x2U

}USAT_BustState_t;

/*
 * @def_group Mode_Types
 */
#define USART_MODE_Tx			((uint32_t)(0x00000008))
#define USART_MODE_Rx			((uint32_t)(0x00000004))
#define USART_MODE_Tx_Rx		((uint32_t)(0x0000000C))

/*
 * @def_group WordLength
 */
#define USART_WORDLENGTH_8BITS	((uint32_t)(0x00000000))
#define USART_WORDLENGTH_9BITS	((uint32_t)(0x00001000))


/*
 * @def_group Parity_Modes
 */
#define USART_PARITY_NONE	((uint32_t)(0x00000000))
#define USART_PARITY_EVEN	((uint32_t)(0x00000400))
#define USART_PARITY_ODD	((uint32_t)(0x00000600))

/*
 * @def_group Stop_Bits
 */
#define USART_STOPBIT_1				((uint32_t)(0x00000000))
#define USART_STOPBIT_HALF			((uint32_t)(0x00001000))
#define USART_STOPBIT_2				((uint32_t)(0x00002000))
#define USART_STOPBIT_1_HALF		((uint32_t)(0x00003000))


/*
 * @def_group Over_Sampling
 */
#define USART_OVERSAMPLE16			((uint32_t)(0x00000000))
#define USART_OVERSAMPLE8			((uint32_t)(0x00008000))

/*
 * @def_group HardWare_Flow_Control
 */
#define USART_HW_NONE				((uint32_t)(0x00000000))
#define USART_HW_CTS				((uint32_t)(0x00000200))
#define USART_HW_RTS				((uint32_t)(0x00000100))
#define USART_HW_CTS_RTS			((uint32_t)(0x00000300))

typedef struct{
	uint32_t	OverSampling;			/* Over Sampling @def_group Over_Sampling*/
	uint32_t	BaudRate;				/* USART Baudrate Value*/
	uint32_t	WordLength;				/* Word Length @def_group WordLength*/
	uint32_t	Parity;					/* Parity Modes @def_group Parity_Modes*/
	uint32_t	StopBits;				/* Stop Bits @def_group Stop_Bits */
	uint32_t	HardWareFlowControl;	/*HardWare Flow Control @def_group HardWare_Flow_Control*/
	uint32_t 	Mode;					/* Tx and Rx Modes @def_group Mode_Types */


}USART_InitTypedef_t;

typedef struct __USART_HandleTypedef_t{
	USART_Typedef_t *Instance;
	USART_InitTypedef_t Init;
	uint8_t	*pTxBuffer;
	uint16_t TxBufferSize;
	uint8_t TxStatus;
	void (*TxISR_Function)(struct __USART_HandleTypedef_t *USART_Handle);
	uint8_t*pRxBuffer;
	uint16_t RxBufferSize;
	uint8_t RxStatus;
	void (*RxISR_Function)(struct __USART_HandleTypedef_t *USART_Handle);
}USART_HandleTypedef_t;

#define __USART_BRR_OVERSAMPLING_8(__PCLOCK__ , BAUDRATE)		( 25U * (uint32_t)( __PCLOCK__) / (2U * (uint32_t)(BAUDRATE)))
#define __USART_BRR_OVERSAMPLING_16(__PCLOCK__ , BAUDRATE)		( 25U * (uint32_t)( __PCLOCK__) / (4U * (uint32_t)(BAUDRATE)))


void USART_Init(USART_HandleTypedef_t *USART_Handle);
void USART_TransmitData(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t dataSize);
void USART_ReceiveData(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t dataSize);
USART_FlagStatus USART_GetFlagStatus(USART_HandleTypedef_t *USART_Handle,uint16_t flagName);
void USART_PeriphCmd(USART_HandleTypedef_t *USART_Handle, FunctionalState_t stateofUSART);
void USART_TransmitData_IT(USART_HandleTypedef_t *USART_Handle, uint8_t *pData, uint16_t dataSize);
void USART_ReceiveData_IT(USART_HandleTypedef_t *USART_Handle, uint8_t *pBuffer, uint16_t dataSize);
void USART_InterruptHandle(USART_HandleTypedef_t *USART_Handle);
#endif /* INC_USART_H_ */
