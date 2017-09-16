#include "XBEE.h"

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
	uint16_t cnt=0;
	frame->checksum = 0;
	for(cnt=0 ; cnt < size ; cnt++)
	{
		frame->checksum += dataptr[cnt];
	}
}