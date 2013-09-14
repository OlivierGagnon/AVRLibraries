#define BITDELAY _delay_us(34)
#define RS232_DDR   DDRB
#define TXPIN PINB1

//simple macros to set port to on or off
#define TXPIN_LOW (PORTB &= ~(1<<TXPIN))
#define TXPIN_HIGH (PORTB |= (1<<TXPIN))

extern void TXInit(void);
extern void TXChar(char);
extern void TXCR(void);
extern void TXString(char *);
