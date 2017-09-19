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
	*	@param	data: pointer to sending data
	* @param 	size: size of sending data
  * @retval None
  */	
void calc_checksum(transmit_frame* frame, uint8_t* data, uint16_t data_size)
{
	frame->checksum = 0;
	frame->checksum += frame->frame_type;
	frame->checksum += frame->frame_id;
	/* Add 64 bit address*/
	for(uint8_t i=0 ; i < 8 ; i++)
	{
		frame->checksum += frame->addr64[i];
	}
	frame->checksum += frame->addr16[0];
	frame->checksum += frame->addr16[1];
	frame->checksum += frame->brdcast_rad;
	frame->checksum += frame->opt;
	/* Add data bytes to checksum*/
	for(uint8_t i=0 ; i < data_size ; i++)
	{
		frame->checksum += data[i];
	}
	/* Finalizing checksum value*/
	frame->checksum = 0xFF - frame->checksum;
}
/**
  * @brief  This function sends a XBEE Transmit Request
	* @param  frame: pointer to xbee frame
	*	@param	trans_rq: pointer to trans-RQ specific frame
	* @param 	size: size of sending data
  * @retval UART status
  */	
HAL_StatusTypeDef transmit_rq(transmit_frame* trans_rq, uint8_t* data, uint16_t data_size,
																UART_HandleTypeDef* UARTx)
{
	trans_rq->start_delimiter = 0x7E;
	/* Frame length for transmit request frame
		 is 14(Payload) + size of data */
	trans_rq->length[0] = (payloadSize + data_size)/255;
	trans_rq->length[1] = (payloadSize + data_size)%255;
	/* Set frame type */
	trans_rq->frame_type = trans_req_ID;
	/* Out stream array to be sent over UART*/
	uint8_t out_stream[payloadSize + data_size + 4]; //+ 4 is for start delimiter,
																									 //checksum and length 
	out_stream[0] = trans_rq->start_delimiter;
	out_stream[1] = trans_rq->length[0];
	out_stream[2] = trans_rq->length[1];
	out_stream[3] = trans_rq->frame_type;
	out_stream[4] = trans_rq->frame_id;
	/* Set 64 bit address*/
	for(uint8_t i=0 ; i < 8 ; i++)
	{
		out_stream[5+i] = trans_rq->addr64[i];
	}
	/* Set 16 bit address*/
	out_stream[13] = trans_rq->addr16[0];
	out_stream[14] = trans_rq->addr16[1];
	out_stream[15] = trans_rq->brdcast_rad;
	out_stream[16] = trans_rq->opt;
	/* Set user's RF data*/
	for(uint8_t i=0 ; i < data_size ; i++)
	{
		out_stream[17+i] = data[i];
	}
	/* Calculate checksum for data */
	calc_checksum(trans_rq, data, data_size);
	out_stream[17+data_size] = trans_rq->checksum;
	/* Sending Data over UART*/
	HAL_StatusTypeDef status;
	status = HAL_UART_Transmit(UARTx, out_stream, sizeof(out_stream), 250);
	return status;
}
