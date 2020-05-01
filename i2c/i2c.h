#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Master Transmitter ---> S|SLA+W|a|DATA|a|P

// Slave Transmitter  ---> S|SLA+R|a|data|A|data|~A|P or S

// Master Receiver    ---> S|SLA+R|a|data|A|data|~A|P

// Slave Receiver     ---> S|SLA+W|a|DATA|a|DATA|A|P or S

void sendStart(void);
void startTransmitted(void);
void checkStart(void);
void sendSLA_W(void);
void SLA_W_ACK_NACKreceived(void);
void checkMT_SLA_ACK(void);
void sendData(void);
void dataACK_NACKreceived(void);
void checkMT_DATA_ACK(void);
void stopTransmitted(void);

void sendStart(void)  //1
{
  TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);
}

void startTransmitted(void) //2
{
  while (!(TWCR & (1<<TWINT)));
}
  
void checkStart(void) //3
{
  if((TWSR & 0xF8) != START)
    ERROR();
}

void sendSLA_W(void)  //4
{
  TWDR = SLA_W;
  TWCR = (1<<TWINT) | (1<<TWEN);
}
  
void SLA_W_ACK_NACKreceived(void) //5
{
  while(!(TWCR & (1<<TWINT)));
}

void checkMT_SLA_ACK(void) //6
{
  if ((TWSR & 0xF8) != MT_SLA_ACK)
    ERROR();
}

void sendDAta(void)
{
  TWDR = DATA;
  TWCR = (1<<TWINT) | (1<<TWEN);
}

void dataACK_NACKreceived(void)
{
  while (!(TWCR & (1<<TWINT)));
}

void checkMT_DATA_ACK(void) //9
{
  if ((TWSR & 0xF8) != MT_DATA_ACK)
    ERROR();
}

void stopTransmitted(void)  //10
{
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}
