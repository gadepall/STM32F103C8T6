//Blink LED
//GVV Sharma
//July 30, 2018

#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//Setup GPIO pins
void Init_GPIO(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Initialize LED which connected to PC13 */
  // Enable PORTC Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  //GPIO_SetBits(GPIOC, GPIO_Pin_13); // Set C13 to High level ("1")
  GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")

}//end GPIO pin setup

void delay_time(uint32_t n_time)
{
	int i;
	for(i=0;i<n_time;i++);
}
int main(void)
{
  

Init_GPIO(); //configure gpio pins

//begin blink
  while (1) {

    	/* Toggle LED  connected to PC13*/
    	GPIOC->ODR ^= GPIO_Pin_13; // Invert C13

    	/* delay */
		delay_time(0x100000);
	

    	/* Toggle LED  connected to PC13*/
    	GPIOC->ODR ^= GPIO_Pin_13;

    	/* delay */
    	delay_time(0x100000);

  }//end blink
  
}//end main
