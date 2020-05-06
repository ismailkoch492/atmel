#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Single Byte Write Sequence (MTSR)
// Master Transmitter      S|SLA+W|-|DATA|-|DATA|-|P or S               sendStart();   |sendSLA_W();   |receiveSLA_W_ACK_NACK();|sendData();   |receiveDataACK_NACK();|sendData();|receiveDataACK_NACK();|sendStop();
// Slave Receiver          -|-----|a|----|a|----|a|------               receiveStart();|receiveSLA_W();|sendSLA_W_ACK_NACK();   |receiveData();|sendDataACK_NACK();|receiveData();|sendDataACK_NACK();   |receiveStop();

// Burst Write Sequence (MTSR)
// Master Transmitter      S|SLA+W|-|DATA|-|DATA|-|DATA|-|P or S        sendStart();   |sendSLA_W();   |receiveSLA_W_ACK_NACK();|sendData();   |receiveDataACK_NACK();|sendData();   |receiveDataACK_NACK();|sendData();   |receiveDataACK_NACK();|sendStop();
// Slave Receiver          -|-----|a|----|a|----|a|----|a|------        receiveStart();|receiveSLA_W();|sendSLA_W_ACK_NACK();   |receiveData();|sendDataACK_NACK();   |receiveData();|sendDataACK_NACK();   |receiveData();|sendDataACK_NACK();   |receiveStop();

// Single Byte Read Sequence (MRST)
// Master Transmitter      S|SLA+W|-|DATA|-|S|SLA+R|-|----|~A|P         sendStart();   |sendSLA_W();   |receiveSLA_W_ACK_NACK();|sendData();   |receiveDataACK_NACK();|sendStart();   |sendSLA_R();   |receiveSLA_R_ACK_NACK();|receiveData();|sendDataNACK();       |sendStop();
// Slave Receiver          -|-----|a|----|a|-|-----|a|data|--|-         receiveStart();|receiveSLA_W();|sendSLA_W_ACK_NACK();   |receiveData();|sendDataACK_NACK();   |receiveStart();|receiveSLA_R();|sendSLA_R_ACK_NACK();   |sendData();   |receiveDataACK_NACK();|receiveStop();

// Burst Read Sequence (MRST)
// Master Transmitter      S|SLA+W|-|DATA|-|S|SLA+R|-|----|A|----|~A|P  sendStart();   |sendSLA_W();   |receiveSLA_W_ACK_NACK();|sendData();   |receiveDataACK_NACK();|sendStart();   |sendSLA_R();   |receiveSLA_R_ACK_NACK();|receiveData();|sendDataACK_NACK();   |receiveData();|sendDataNACK();       |sendStop();
// Slave Receiver          -|-----|a|----|a|-|-----|a|data|-|data|--|-  receiveStart();|receiveSLA_W();|sendSLA_W_ACK_NACK();   |receiveData();|sendDataACK_NACK();   |receiveStart();|receiveSLA_R();|sendSLA_R_ACK_NACK();   |sendData();   |receiveDataACK_NACK();|sendData();   |receiveDataACK_NACK();|receiveStop();

//
//
//
//


void sendStart(void);//1
void receiveStart(void);//1
void startTransmitted(void);//2
void checkStart(void);//3
void sendSLA_W(int SLA_W);//4
void sendSLA_R(int SLA_R);//4
void receiveSLA_W(void);//4
void receiveSLA_R(void);//4
void sendSLA_W_ACK_NACK(void);
void sendSLA_R_ACK_NACK(void);
void receiveSLA_W_ACK_NACK(void);//5
void receiveSLA_R_ACK_NACK(void);//5
void checkMT_SLA_ACK(void);//6
void checkMR_SLA_ACK(void);//6
void sendData(int DATA);//7
void receiveData(int DATA);//7
void sendDataACK_NACK(void);//8
void sendDataNACK(void);//8
void receiveDataACK_NACK(void);//8
void checkMT_DATA_ACK(void);//9
void checkMR_DATA_ACK(void);//9
void sendStop(void);//10
void receiveStop(void);//10

void sendStart(void)  //1
{
  TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);
  startTransmitted(); //2
  checkStart(); //3
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

void sendSLA_W(int SLA_W)  //4
{
  SLA_W = (SLA_W<<1);
  TWDR = SLA_W;
  TWCR = (1<<TWINT) | (1<<TWEN);
}

void sendSLA_R(int SLA_R)  //4
{
  SLA_R = (SLA_R<<1) | (1<<0);
  TWDR = SLA_R;
  TWCR = (1<<TWINT) | (1<<TWEN);
}

void receiveSLA_W_ACK_NACK(void) //5
{
  while(!(TWCR & (1<<TWINT)));
  checkMT_SLA_ACK();
}

void receiveSLA_R_ACK_NACK(void) //5
{
  while(!(TWCR & (1<<TWINT)));
  checkMR_SLA_ACK();
}

void checkMT_SLA_ACK(void) //6
{
  if ((TWSR & 0xF8) != MT_SLA_ACK)
    ERROR();
}

void checkMR_SLA_ACK(void) //6
{
  if ((TWSR & 0xF8) != MR_SLA_ACK)
    ERROR();
}

void sendData(int DATA) //7
{
  TWDR = DATA;
  TWCR = (1<<TWINT) | (1<<TWEN);
}

void receiveData(int DATA) //7
{
  DATA = TWDR;
  //TWCR  change
}

void receiveDataACK_NACK(void) //8
{
  while (!(TWCR & (1<<TWINT)));
  checkMR_DATA_ACK();
}

void sendDataACK_NACK(void) //8
{
  //send ack bit when master receive data from slave.
  checkMT_DATA_ACK();
}

void checkMT_DATA_ACK(void) //9
{
  if ((TWSR & 0xF8) != MT_DATA_ACK)
    ERROR();
}

void checkMR_DATA_ACK(void) //9
{
  if ((TWSR & 0xF8) != MR_DATA_ACK)
    ERROR();
}

void sendStop(void)  //10
{
  TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
}
