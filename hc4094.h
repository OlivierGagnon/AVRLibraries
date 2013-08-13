#define HC4094_PORT	PORTB
#define HC4094_DDR	DDRB
#define HC4094_DATA_PIN	PB1	//Data pin (DS) pin location
#define HC4094_CLOCK_PIN	PB0	//Shift Clock (SH_CP) pin location
#define HC4094_STROBE_PIN	PB2	//Store Clock (ST_CP) pin location

//Low level macros to change data (DS)lines
#define HC4094DataHigh() (HC4094_PORT|=(1<<HC4094_DATA_PIN))
#define HC4094DataLow() (HC4094_PORT&=(~(1<<HC4094_DATA_PIN)))

void HC4094Init(void);
void HC4094Pulse(void);
void HC4094Latch(void);
void HC4094Write(uint8_t);
