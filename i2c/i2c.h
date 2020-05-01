#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Master Transmitter ---> S|SLA+W|a|DATA|a|P

// Master Receiver ---> S|SLA+R|a|data|A|data|~A|P

void sendStart(void);
void startTransmitted(void);
void checkTWSR_Start(void);

void SLA_W_ACK_NACKreceived(void);
void checkMT_SLA_ACK(void);


void sendDataTWDR(void);
void dataACK_NACKreceived(void);
void checkTWST_MT_DATA_ACK(void);
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
  
void SLA_W_ACK_NACKreceived(void);
{
  while(!(TWCR & (1<<TWINT)));
}
  
void checkMT_SLA_ACK(void)
{
  if ((TWSR & 0xF8) != MT_SLA_ACK)
    ERROR();
}

void stopTransmitted(void)
{
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}
