#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sendStart(void);

int  main()
{
  while(1)
  {
    
  }
}

void sendStart()
{
  TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN)
]
