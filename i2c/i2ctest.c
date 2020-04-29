#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sendStart(void);
void startTransmitted(void);
void stopTransmitted(void);

int  main()
{
  while(1)
  {
    
  }
}

void sendStart(void)
{
  TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);
]

void startTransmitted(void)
{
    while (!(TWCR & (1<<TWINT)));
} 

void stopTransmitted(void)
{
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}
