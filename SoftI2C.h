#define SCLPORT	PORTB	//TAKE PORTD as SCL OUTPUT WRITE
#define SCLDDR	DDRB	//TAKE DDRB as SCL INPUT/OUTPUT configure

#define SDAPORT	PORTB	//TAKE PORTD as SDA OUTPUT WRITE
#define SDADDR	DDRB	//TAKE PORTD as SDA INPUT configure

#define SDAPIN	PINB	//TAKE PORTD TO READ DATA
#define SCLPIN	PINB	//TAKE PORTD TO READ DATA

#define SCL	PB4		//PORTb.0 PIN AS SCL PIN
#define SDA	PB3		//PORTb.3 PIN AS SDA PIN

#define SOFT_I2C_SDA_LOW	SDADDR|=((1<<SDA)) //Macros to toggle the ports
#define SOFT_I2C_SDA_HIGH	SDADDR&=(~(1<<SDA))

#define SOFT_I2C_SCL_LOW	SCLDDR|=((1<<SCL))
#define SOFT_I2C_SCL_HIGH	SCLDDR&=(~(1<<SCL))

#define Q_DEL _delay_loop_2(3) //Some delay functions
#define H_DEL _delay_loop_2(5)

extern void SoftI2CInit(void);
extern void SoftI2CStart(void);
extern void SoftI2CStop(void);
extern uint8_t SoftI2CWriteByte(uint8_t);
extern uint8_t SoftI2CReadByte(uint8_t);

