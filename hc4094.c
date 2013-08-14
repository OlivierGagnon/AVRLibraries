/*
*
* 4094 shift register functions
*
*/

#include <avr/io.h>
#include "hc4094.h"

void HC4094Init(void)
{
	//Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output
	HC4094_DDR|=((1<<HC4094_CLOCK_PIN)|(1<<HC4094_STROBE_PIN)|(1<<HC4094_DATA_PIN));
}

//Sends a clock pulse on SH_CP line

void HC4094Pulse(void)
{
	//Pulse the Shift Clock
	HC4094_PORT|=(1<<HC4094_CLOCK_PIN);	//HIGH
	HC4094_PORT&=(~(1<<HC4094_CLOCK_PIN));	//LOW
}

//Sends a clock pulse on ST_CP line
void HC4094Latch(void)
{
	//Pulse the Store Clock
	HC4094_PORT|=(1<<HC4094_STROBE_PIN);//HIGH
	//_delay_loop_1(1);
	HC4094_PORT&=(~(1<<HC4094_STROBE_PIN));//LOW
	//_delay_loop_1(1);
}

void HC4094Write(uint8_t data)
{
	//Send each 8 bits serially
	uint8_t i;
	for(i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data & 0b00000001)
		{
			//MSB is 1 so output high
			HC4094DataHigh();
		}
		else
		{
			//MSB is 0 so output low
			HC4094DataLow();
		}
		HC4094Pulse();  //Pulse the Clock line
		data=data>>1;  //Now bring next bit at MSB position
	}
	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC4094Latch();
}


//Writes two bytes to shift register. Data1 will be the second shift register
void DualHC4094Write(uint8_t data1, uint8_t data2)
{
	//Send each 8 bits serially
	uint8_t i;
	for(i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data1 & 0b00000001)
		{
			//MSB is 1 so output high
			HC4094DataHigh();
		}
		else
		{
			//MSB is 0 so output low
			HC4094DataLow();
		}
		HC4094Pulse();  //Pulse the Clock line
		data1=data1>>1;  //Now bring next bit at MSB position
	}
    i = 0;
	for(i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data2 & 0b00000001)
		{
			//MSB is 1 so output high
			HC4094DataHigh();
		}
		else
		{
			//MSB is 0 so output low
			HC4094DataLow();
		}
		HC4094Pulse();  //Pulse the Clock line
		data2=data2>>1;  //Now bring next bit at MSB position
	}

	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	HC4094Latch();
}
