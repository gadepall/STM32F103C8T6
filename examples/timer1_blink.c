/* GVV Sharma 
 * August 31, 2018
 * 
 * Blink a LED using HSI clock and Timer1
 */
#include "stm32f103xb.h"

int main()
{
	/*
	 * Enable all Ports and Alternate Function clocks
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // enable Timer1
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	/*
	 * Enable the SysTick Timer with
	 * the CPU clock divided by 8
	 */
	TIM1->SMCR  = 0;	//Internal clock, 8MHz	
	TIM1->PSC	= 3999;	//Prescalar, dividing clock by 4000
	TIM1->CR1 	= TIM_CR1_CEN;	//enable Timer1
	TIM1->ARR 	= 999;	//Load Count


	/*
	 * Enable the PA1 as a digital output
	 */
	GPIOA->CRL = 0x00000020;

	/*
	 * Infinite loop
	 */
	while(1)
	{
		//half second on, half second off
	if(TIM1->SR & TIM_SR_UIF)//check if ARR count complete
  {
  TIM1->SR &= ~TIM_SR_UIF;//clear status register SR
		GPIOA->ODR ^= (1 << 1);//blink LED through PA1
  }
	}
}

