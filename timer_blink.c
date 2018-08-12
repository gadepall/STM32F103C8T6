#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include <stm32f10x_tim.h>
#include <misc.h>
 
void InitializeLEDs()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
 
    GPIO_InitTypeDef gpioStructure;
    gpioStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    gpioStructure.GPIO_Mode = GPIO_Mode_OUT;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpioStructure);
 
    GPIO_WriteBit(GPIOD, GPIO_Pin_12 | GPIO_Pin_13, Bit_RESET);
}
 
void InitializeTimer()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    TIM_TimeBaseInitTypeDef timerInitStructure; 
    timerInitStructure.TIM_Prescaler = 40000;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 500;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_Cmd(TIM2, ENABLE);
}
 
int main()
{
    InitializeLEDs();
    InitializeTimer();
 
    for (;;)
    {
        int timerValue = TIM_GetCounter(TIM2);
        if (timerValue == 400)
            GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);
        else if (timerValue == 500)
            GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);
    }
}
