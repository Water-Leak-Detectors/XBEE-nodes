/*********************************************
Developer: Mohammad Hussein Tavakoli Bina(MHTB)
**********************************************/

#ifndef XBEE_H
#define XBEE_H

/* Includes----------------------------------------*/
#include "stdint.h"
#include "stm32f0xx_hal.h"

/* Typedefs----------------------------------------*/

/* Base Frame Structure*/
typedef struct
{
	uint8_t start_delimiter;
	uint8_t length[2];
	uint8_t cmd_id;
	uint8_t checksum;
}	xbee_frame;

/* Transmit Request Specific Fields*/
typedef struct
{
	uint8_t frame_id;
	uint8_t addr64[8];
	uint8_t addr16[2];
	uint8_t brdcast_rad;
	uint8_t opt;
} transmit_rq;

/* Function Prototypes-----------------------------*/
void calc_checksum(xbee_frame*, uint8_t*, uint16_t);
void send_handler(xbee_frame*, transmit_rq*, uint8_t*, uint16_t,
																UART_HandleTypeDef* UARTx);

#endif
