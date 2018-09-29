#include "stm32f103xb.h"
#include "lcd.h"

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
// LCD_Message displays a string
// GPIOA is used for data communications with the HD44780-controlled LCD.
//// The following defines are controller commands
#define CLEARDISPLAY 0x01

void PulseEnableLine ()
{
GPIOA->BSRR = 2; // take LCD enable line high
 delay_us(40); // wait 40 microseconds
GPIOA->BRR = 2; // take LCD enable line low
}
void SendNibble(byte data)
{
GPIOA->BRR = ~(data << 2) & 0b00111100;
GPIOA->BSRR = (data << 2) & 0b00111100;
 
 PulseEnableLine(); // clock 4 bits into controller
}
void SendByte (byte data)
{

 SendNibble(data >> 4); // send upper 4 bits
 SendNibble(data); // send lower 4 bits
//GPIOA->BRR = 5;	
}
void LCD_Cmd (byte cmd)
{
 GPIOA->BRR = 1; // R/S line 0 = command data
 SendByte(cmd); // send it
}
void LCD_Char (byte ch)
{
GPIOA->BSRR = 1;// R/S line 1 = character data
 SendByte(ch); // send it
}
void LCD_Init()
{
	
 LCD_Cmd(0x33); // initialize controller
 LCD_Cmd(0x32); // set to 4-bit input mode
 LCD_Cmd(0x28); // 2 line, 5x7 matrix
 LCD_Cmd(0x0C); // turn cursor off (0x0E to enable)
 LCD_Cmd(0x06); // cursor direction = right
 LCD_Cmd(0x01); // start with clear display
 delay_us(3000); // wait for LCD to initialize

}
void LCD_Clear() // clear the LCD display
{
 LCD_Cmd(CLEARDISPLAY);
 delay_us(3000); // wait for LCD to process command

}

void LCD_Message(const char *text) // display string on LCD
{
 while (*text) // do until /0 character
 LCD_Char(*text++); // send char & update char pointer
}
