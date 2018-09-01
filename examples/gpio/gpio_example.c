/*
GVV Sharma, August 19, 2018
Code released under GNU GPL
*/

/*
 * Turn LED ON/OFF
 */
#include "stm32f103xb.h"	

int main()
{
	/*
	 * Enable all Ports and Alternate Function clocks
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	/*
	 * Enable the PB4 as a digital output
	 */
	GPIOB->CRL = 0x00030000;	

	/*
	 * Infinite loop
	 */
	while(1)
	{
//		GPIOB->BSRR = GPIO_BSRR_BS4; //PB4 = 1 (Led OFF)
//		GPIOB->BSRR = (1<<4); //PB4 = 1 (Led OFF)		
//		GPIOB->BSRR = GPIO_BSRR_BR4; //PB4 = 0 (Led ON)		
		GPIOB->BRR = (1<<4); //PB4 = 0 (Led ON)		

	}
}
