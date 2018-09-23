#include "stm32f103xb.h"

// TYPEDEFS
typedef uint8_t byte; // changed the name


// ------------------
//LCD DRIVER ROUTINES
//
// Routines:
// LCD_Init initializes the LCD controller
// LCD_Cmd sends LCD controller command
// LCD_Char sends single ascii character to display
// LCD_Clear clears the LCD display & homes cursor
// LCD_Integer displays an integer value
// LCD_Message displays a string
// PortB is used for data communications with the HD44780-controlled LCD.
// The following defines specify which port pins connect to the controller:
//#define ClearBit(x,y) x &= ~_BV(y) // equivalent to cbi(x,y)
//#define SetBit(x,y) x |= _BV(y) // equivalent to sbi(x,y)
//#define LCD_RS 0 // pin for LCD R/S (eg PB0)
//#define LCD_E 1 // pin for LCD enable
//#define DAT4 2 // pin for d4
//#define DAT5 3 // pin for d5
//#define DAT6 4 // pin for d6
//#define DAT7 5 // pin for d7
//// The following defines are controller commands
#define CLEARDISPLAY 0x01

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
	 * (source is
	 * 1MHz and the time is specified in us)
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

void PulseEnableLine ()
{
// SetBit(PORTB,LCD_E); // take LCD enable line high
GPIOA->BSRR = 2; 
 delay_us(40); // wait 40 microseconds
// ClearBit(PORTB,LCD_E); // take LCD enable line low
GPIOA->BRR = 2;
}
void SendNibble(byte data)
{
 //PORTB &= 0xC3; // 1100.0011 = clear 4 data lines
 //if (data & _BV(4)) SetBit(PORTB,DAT4);
 //if (data & _BV(5)) SetBit(PORTB,DAT5);
 //if (data & _BV(6)) SetBit(PORTB,DAT6);
 //if (data & _BV(7)) SetBit(PORTB,DAT7);
GPIOA->BRR = ~(data << 2) & 0b00111100;
GPIOA->BSRR = (data << 2) & 0b00111100;
 
 PulseEnableLine(); // clock 4 bits into controller
}
void SendByte (byte data)
{

 SendNibble(data >> 4); // send upper 4 bits
 SendNibble(data); // send lower 4 bits
GPIOA->BRR = 5;	
// SendNibble(data); // send upper 4 bits
// SendNibble(data<<4); // send lower 4 bits
 //ClearBit(PORTB,5); // turn off boarduino LED
}
void LCD_Cmd (byte cmd)
{
// ClearBit(PORTB,LCD_RS); // R/S line 0 = command data
 GPIOA->BRR = 1; // R/S line 0 = command data
 SendByte(cmd); // send it
}
void LCD_Char (byte ch)
{
// SetBit(PORTB,LCD_RS); // R/S line 1 = character data
GPIOA->BSRR = 1;
 SendByte(ch); // send it
}
void LCD_Init()
{
	
 LCD_Cmd(0x33); // initialize controller
 LCD_Cmd(0x32); // set to 4-bit input mode
 LCD_Cmd(0x28); // 2 line, 5x7 matrix
 LCD_Cmd(0x0C); // turn cursor off (0x0E to enable)
//LCD_Cmd(0x0E); // turn cursor off (0x0E to enable) 
 LCD_Cmd(0x06); // cursor direction = right
 LCD_Cmd(0x01); // start with clear display
 delay_us(3000); // wait for LCD to initialize
 //_delay_ms(3); // wait for LCD to initialize
}
void LCD_Clear() // clear the LCD display
{
 LCD_Cmd(CLEARDISPLAY);
 delay_us(3000); // wait for LCD to process command
// _delay_ms(3); // wait for LCD to process command 
}

void LCD_Message(const char *text) // display string on LCD
{
 while (*text) // do until /0 character
 LCD_Char(*text++); // send char & update char pointer
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
	SysTick->CTRL = 0x00000001;


	/*
	 * 100ms delay to ensure that the
	 * LCD display is properly powered on 
	 */
	delay_us(100000);

// use PortB for LCD interface
// DDRB = 0xFF; // 1111.1111; set PB0-PB7 as outputs	 
GPIOA->CRL = (GPIOA->CRL & 0xFF000000) | 0x00333333;//set A0-A5 as outputs

 LCD_Init(); // initialize LCD controller

 while(1)
 {
LCD_Clear();
LCD_Message("Mera Bharat Mahan"); 

delay_us(600000);     // set animation speed 600 ms
}
}
