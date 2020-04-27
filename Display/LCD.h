#ifndef LCD
#define LCD

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef RS
#define RS 1
#endif

#ifndef RW
#define RW 2
#endif

#ifndef ENABLE
#define ENABLE 4
#endif

#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>

char positionString[4];
#define LcdData PORTD
#define LcdDataDir DDRD
#define LcdCommand PORTB
#define LcdCommandDir DDRB
#define DATA (1==1)
#define COMMAND (!DATA)

char firstColumnPos[4] = {0, 64, 20, 84};

void CheckIfBusy(void);
void Enable(void);
void Send(int mode, unsigned char value);
void SendString(char *string);
void SendInt(uint8_t x, uint8_t y, int IntegerToDisplay, char NumberOfDigits);
void SendStringWithLoc(uint8_t x, uint8_t y, char *StringOfCharacters);
void SendInt(uint8_t x, uint8_t y, int IntegerToDisplay, char NumberOfDigits);
void Init(void);

void Init(){
  LcdCommandDir |= 1<<ENABLE | 1<<RW | 1<<RS;
  _delay_ms(15);
  Send(COMMAND, 0x01); //Clear Screen 0x01 = 00000001
  _delay_ms(2);
  Send(COMMAND, 0x38);
  _delay_us(50);
  Send(COMMAND, 0b00001110);
  _delay_us(50);
}
void CheckIfBusy()
{
  LcdDataDir = 0;
  LcdCommand |= 1<<RW;
  LcdCommand &= ~1<<RS;
  while (LcdData >= 0x80)
  {
    Enable();
  }
  LcdDataDir = 0xFF; //0xFF means 0b11111111
}

void Enable()
{
  LcdCommand |= 1<<ENABLE;
  asm volatile ("nop");
  asm volatile ("nop");
  LcdCommand &= ~1<<ENABLE;
}

void Send(int mode, unsigned char value)
{
  CheckIfBusy();
  LcdData = value;
  LcdCommand &= ~ (1<<RW);
  if (mode == COMMAND)
  {
    LcdCommand &= ~ (1<<RS);
  }
  else
  {
    LcdCommand |= 1<<RS;
  }
  Enable();
  LcdData = 0;
  _delay_ms(1);
}

void SendString(char *string)
{
  while(*string > 0)
  {
    Send(DATA, *string++);
  }
}

void GoToLoc(uint8_t x, uint8_t y)
{
  Send(COMMAND, 0x80 + firstColumnPos[y-1] + (x-1));
}

void SendStringWithLoc(uint8_t x, uint8_t y, char *StringOfCharacters)
{
  GoToLoc(x, y);
  SendString(StringOfCharacters);
}

void SendInt(uint8_t x, uint8_t y, int IntegerToDisplay, char NumberOfDigits)
{
  char StringToDisplay[NumberOfDigits];
  itoa(IntegerToDisplay, StringToDisplay, 10);
  SendStringWithLoc(x, y, StringToDisplay); SendString(" ");
}

#endif
