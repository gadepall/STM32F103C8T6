// TYPEDEFS
typedef uint8_t byte; // changed the name

void delay_us(unsigned int time);
void PulseEnableLine (void);
void SendNibble(byte data);
void SendByte (byte data);
void LCD_Cmd (byte cmd);
void LCD_Char (byte ch);
void LCD_Init(void);
void LCD_Clear(void) ;
void LCD_Message(const char *text);

