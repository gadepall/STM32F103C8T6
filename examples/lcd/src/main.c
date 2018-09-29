/* GVV Sharma 
 * September 24, 2018
 * Adapted from LCD code for AVR-GCC
 * Augusto Fraga Giachero, 2015
 * Display string on 16x2 HD44780-controlled LCD
 * 
 * Released under GNU GPL
 */

#include "stm32f103xb.h"
#include "lcd.h"
#include "stdlib.h"

/*
 * Delay function:
 * Uses the SysTick timer to wait for
 * an abitrary time in microseconds.
 *
 * The clock source is assumed to be
 * the internal 8MHz RC oscilator
 */
void delay_us(unsigned int time)
{
	/*
	 * (source is 1MHz and the time is specified in us)
	 */
	SysTick->LOAD = time;

	/*
	 * Clears the current value and the count flag
	 */
	SysTick->VAL = 0;

	/*
	 * Waits until the count ends
	 */
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}


// MAIN PROGRAM
int main(void)
{

	/*
	 * Enable all ports and Alternate Function clocks
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;


	/*
	 * Enable the SysTick Timer
	 */
	SysTick->CTRL = 0x00000001;// 1 MHz Clock


	/*
	 * 100ms delay to ensure that the
	 * LCD display is properly powered on 
	 */
	delay_us(100000);


GPIOA->CRL = (GPIOA->CRL & 0xFF000000) | 0x00333333;//set A0-A5 as outputs

 LCD_Init(); // initialize LCD controller

 while(1)
 {
LCD_Clear();
LCD_Message("Jai Hind"); 

delay_us(600000);     // set animation speed 600 ms
}
}
