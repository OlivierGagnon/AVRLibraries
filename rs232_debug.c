////////////////////////////////////////////////////////////////////////////

//start rs232 communication functions

//delay per bit = 1sec/38400bps = 26 useconds per bit
//(1 start bit, 8 data bits, and 1 stop bit)
#include <avr/io.h>
#include <util/delay.h>
#include "rs232_debug.h"

void TXInit(void)
{
	DDRB |= (1<<TXPIN); //portb0 as output
	TXPIN_LOW; //TXPIN to low. meaning rs232 to HIGH state = idle.
}

void SendChar(char data)
{
	TXPIN_HIGH; //TXPIN to high. meaning rs232 to low = start bit.
	BITDELAY; //delay after start bit

	//apply NOT to reverse the bits
	data = ~data;
	int i;

	//loop to send the bits
	for (i=0;i<8;i++)
	{
		//lsb so check the 0th bit
		if (data & 0x01)
		{
			TXPIN_HIGH;
		}
		else
		{
			TXPIN_LOW;
		}
		//then shift right
		data >>= 1;
		//then bit delay
		BITDELAY;
	}

	//sent all 8 bits
	//sending stop bit
	TXPIN_LOW; //portb to low, meaning rs232 high. stop bit & back to idle
	BITDELAY;
	//back to idle
}


//sends a string formatted like: char String1[]="This is string 1"
void SendString(char* StringPtr)
{
	//sends a string
	while(*StringPtr != 0x00)
	{
		SendChar(*StringPtr);
		StringPtr++;
	}
}

// sends a carriage return, to look nice on the display when using strings
void SendCR(void)
{
	SendChar(0x0d);
}
