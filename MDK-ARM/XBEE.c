#include "XBEE.h"

/* Definitions ------------------------------------------------*/
#define payloadSize 14

/* Variables---------------------------------------------------*/
const uint8_t trans_req_ID = 0x10;
const uint8_t modem_stat = 0x8A;
const uint8_t trans_stat = 0x8B;

/* Function Definitions----------------------------------------*/
/**
  * @brief  This function calculates checksum and puts it in your frame
	* @param  frame: pointer to xbee frame
	*	@paran	dataptr: pointer to sending data
	* @param 	size: size of sending data
  * @retval None
  */	
void calc_checksum(xbee_frame* frame, uint8_t* dataptr, uint16_t size)
{
	frame->checksum = 0;
	for(uint16_t cnt=0 ; cnt < size ; cnt++)
	{
		frame->checksum += dataptr[cnt];
	}
}
/**
  * @brief  This function sends a XBEE Transmit Request
	* @param  frame: pointer to xbee frame
	*	@param	trans_rq: pointer to trans-RQ specific frame
	* @param 	size: size of sending data
  * @retval None
  */	
void send_handler(xbee_frame* frame, transmit_rq* trans_rq, uint8_t* data, uint16_t data_size,
																UART_HandleTypeDef* UARTx)
{
	/* Frame length for transmit request frame
		 is 14(Payload) + size of data */
	frame->length[0] = (payloadSize + data_size)/255;
	frame->length[1] = (payloadSize + data_size)%255;
	/* Set frame type */
	frame->cmd_id = trans_req_ID;
	/* Out stream array to be sent over UART*/
	uint8_t out_stream[payloadSize + data_size + 4]; //+ 4 is for start delimiter,
																									 //checksum and length 
	out_stream[0] = frame->start_delimiter;
	out_stream[1] = frame->length[0];
	out_stream[2] = frame->length[1];
	out_stream[3] = frame->cmd_id;
	out_stream[4] = trans_rq->frame_id;
	
	/* Set 64 bit address*/
	for(uint8_t i=0 ; i < 8 ; i++)
	{
		out_stream[5+i] = trans_rq->addr64[i];
	}
}
