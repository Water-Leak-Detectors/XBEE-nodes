/*********************************************
Developer: Mohammad Hussein Tavakoli Bina(MHTB)
**********************************************/

#ifndef __XBEE_H
#define __XBEE_H

/* Includes----------------------------------------*/
#include "stdint.h"
#include "stm32f0xx_hal.h"

/* Typedefs----------------------------------------*/
enum NODE_TYPE
{
	fsr,
	flow,
	pressure
};
/* Transmit Request Specific Fields*/
typedef struct
{
	uint8_t start_delimiter;
	uint8_t length[2];
	uint8_t frame_type;
	uint8_t checksum;
	uint8_t frame_id;
	uint8_t addr64[8];
	uint8_t addr16[2];
	uint8_t brdcast_rad;
	uint8_t opt;
} transmit_frame;

/* Function Prototypes-----------------------------*/
void calc_checksum(transmit_frame*, uint8_t*, uint16_t);
HAL_StatusTypeDef transmit_rq(transmit_frame*, uint8_t*, uint16_t,
																UART_HandleTypeDef* UARTx);
void frame_generator(uint8_t*, uint16_t, enum NODE_TYPE, uint8_t, uint16_t);

#endif
