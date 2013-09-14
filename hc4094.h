#define HC4094_PORT	PORTD
#define HC4094_DDR	DDRD
#define HC4094_DATA_PIN	PORTD1	//Data pin pin
#define HC4094_CLOCK_PIN	PORTD2	//Clock pin
#define HC4094_LATCH_PIN	PORTD0	//Latch pin

//macros to toggle data port
#define HC4094DataHigh() (HC4094_PORT|=(1<<HC4094_DATA_PIN))
#define HC4094DataLow() (HC4094_PORT&=(~(1<<HC4094_DATA_PIN)))

extern void HC4094Init(void);
extern void HC4094Pulse(void);
extern void HC4094Latch(void);
extern void HC4094Write(int);
