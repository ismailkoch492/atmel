#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void sendStart(void);
void startTransmitted(void);
void checkTWSR_Start(void);

void SLA_Wtransmitted_ACK_NACKreceived(void);
void checkTWSR_MT_SLA_ACK(void);



void stopTransmitted(void);

void sendStart(void)
{
  TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);
]

void startTransmitted(void)
{
  while (!(TWCR & (1<<TWINT)));
}
  
void checkTWSR_Start(void)
{
  if((TWSR & 0xF8) != START)
    ERROR();
}
  
void SLA_Wtransmitted_ACK_NACKreceived(void);
{
  while(!(TWCR & (1<<TWINT)));
}
  
void checkTWSR_MT_SLA_ACK(void)
{
  if ((TWSR & 0xF8) != MT_SLA_ACK)
    ERROR();
}

void stopTransmitted(void)
{
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}
