/*

HC4094Write(0b00000000);

pins:
bit7 = nc
bit6 = nc
bit5 = RS (register select)
bit4 = E (clock)
bit3 = D7
bit2 = D6
bit1 = D6
bit0 = D4

documentation:

http://www.microchip.com/forums/m252183-print.aspx
http://web.alfredstate.edu/weimandn/lcd/lcd_initialization/lcd_initialization_index.html
http://www.stanford.edu/class/ee281/handouts/hd44780_lcd_controller_datasheet.pdf
http://www.electronic-engineering.ch/microchip/datasheets/lcd/the_lcd_data_sheet.pdf
http://iamsuhasm.files.wordpress.com/2009/04/aa.png

*/

//Pins and aliases, connected to 4094 shift register
#define D4  0b00000001
#define D5  0b00000010
#define D6  0b00000100
#define D7  0b00001000
#define E   0b00010000
#define RS  0b00100000

extern void LCD_4bit_Init(void);
extern void LCD_Cmd(int cmd);
extern void LCD_4bit_Cmd(int cmd);
extern void LCD_4bit_WriteDDRAM(int cmd);
extern void LCD_Clear(void);
extern void LCD_WriteLongString(char* StringPtr);
extern void LCD_WriteString(char* StringPtr);
extern void LCD_WriteInt(int digit);
extern void LCD_Goto_Position(int line, int position);

