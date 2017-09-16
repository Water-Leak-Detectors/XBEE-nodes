/************************
Developer: Mohammad Hussein Tavakoli Bina
*/

#ifndef XBEE_H
#define XBEE_H

/* Includes----------------------------------------*/
#include "stdint.h"

/* Variables---------------------------------------*/
const uint8_t trans_req_ID = 0x10;
const uint8_t modem_stat = 0x8A;
const uint8_t trans_stat = 0x8B;

/* Typedefs----------------------------------------*/
typedef struct
{
	const uint8_t start_delimiter;
	uint8_t length[2];
	uint8_t cmdID;
	uint8_t checksum;
}	xbee_frame;

/* Function Prototypes-----------------------------*/
void calc_checksum(xbee_frame*, uint8_t*, uint16_t);


#endif