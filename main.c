/*
GVV Sharma, August 19, 2018
Code released under GNU GPL
*/

/*
 * Control Seven Segment Display
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
	 * Enable the PB3-PB9 as a digital output
	 */
	GPIOB->CRL = 0x33333000;
	GPIOB->CRH = 0x00000033;		

	/*
	 * Infinite loop
	 */
	while(1)
	{
		GPIOB->ODR &= ~(0x000003F0);//0
		GPIOB->ODR |= 0x00000008;//0		
//		GPIOB->ODR = 0xFC08;//0		
//		GPIOB->ODR = 0xFE78;//1		
//		GPIOB->ODR = 0xFC90;//2				

	}
}
