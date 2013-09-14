#include <avr/io.h>
#include <util/delay.h>
#include "hc4094.h"
#include <stdlib.h>
#include "hd44780.h"

// LCD Control commands

void LCD_4bit_Init(void)
{
    LCD_Cmd(D5+D4); //starting 4 bit mode init
    _delay_ms(5); //wait at least 4.1ms
    LCD_Cmd(D5+D4);
    _delay_us(101); //wait at least 100 usec
    LCD_Cmd(D5+D4);
    _delay_us(40); //wait at least 37 usec
    LCD_Cmd(D5);
    //in 4 bit mode, send next cmd in two nibbles
    LCD_4bit_Cmd(0b00101000); //f=0, 5x8. n=1, 2 lines
    LCD_4bit_Cmd(0b00000110); //entry mode set, increment 1, no shift
    LCD_4bit_Cmd(0b00001100); //display on
}

void LCD_Cmd(int cmd)
{
    HC4094Write(cmd+E); //take 4 bit cmd, add E pin, write to shift register
    HC4094Write(cmd); // write 4 bit cmd normal, taking E low, but keeping cmd on
}

void LCD_4bit_Cmd(int cmd)
{
    int high, low; //initialize variables for the two nibbles
    high = (cmd >> 4); //shift right so bits 0 to 3 are the upper nibble
    low = (cmd & 0b00001111); //clear high nibble, keep lower
    HC4094Write(high+E); //take 4 bit cmd, add E pin, write to shift register
    HC4094Write(high); //write 4 bit cmd normal, taking E low, but keeping cmd on
    HC4094Write(low+E);//take 4 bit cmd, add E pin, write to shift register
    HC4094Write(low); //write 4 bit cmd normal, taking E low, but keeping cmd on, sending a clock
}

void LCD_4bit_WriteDDRAM(int cmd) //same as cmd, but have RS on to write RAM
{
    int high, low; //initialize variables for the two nibbles
    high = (cmd >> 4); //shift right so bits 0 to 3 are the upper nibble
    low = (cmd & 0b00001111); //clear high nibble, keep lower
    HC4094Write(high+E+RS); //take 4 bit cmd, add E and RS pin, write to shift register
    HC4094Write(high+RS); //write 4 bit cmd normal, taking E low, but keep RS and cmd on
    HC4094Write(low+E+RS); //take 4 bit cmd, add E pin and RS, write to shift register
    HC4094Write(low+RS); //write 4 bit cmd normal, taking E low, but keeping cmd and RS on, sending a clock
    _delay_us(45); //delay for writing the DDRAM
}

void LCD_WriteLongString(char* StringPtr)
{
	//sends a string, but wraps to the second line
	//first, go to position 0
    int counter = 0;
    LCD_4bit_Cmd(0b10000000); //DDRAM address = 0x00
	while(*StringPtr != 0x00)
	{
		LCD_4bit_WriteDDRAM(*StringPtr);
		StringPtr++;
		counter++;
		if (counter == 16) //if end of first line
        {
            //goto position 0, line 2
            LCD_4bit_Cmd(0b10101000); //DDRAM address = 0x40
        }
	}
}

void LCD_Clear(void)
{
    LCD_4bit_Cmd(0b00000001);
    _delay_ms(2);
}

void LCD_WriteString(char* StringPtr)
{
	//sends a string
	while(*StringPtr != 0x00)
	{
		LCD_4bit_WriteDDRAM(*StringPtr);
		StringPtr++;
	}
}

void LCD_Goto_Position(int line, int position)
{
    if (line == 1)
    {
        //Line1
        LCD_4bit_Cmd(0b10000000 + (position-1));
    }
    else
    {
        //Line2
        LCD_4bit_Cmd(0b10000000 + 0x40 + (position-1));
    }
}

void LCD_WriteInt(int digit)
{
    char buffer[10]; //10 digits is a good value for now
    itoa(digit, buffer, 10);
    LCD_WriteString(buffer);
}
