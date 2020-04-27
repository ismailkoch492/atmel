#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD.h"

void FirstPrint(void);
void SecondPrint(void);
void Position(void);

int main(void)
{
  Init();
//  char positionString[4];
  while(1)
  {
    FirstPrint();
    SecondPrint();
    Position();
  }
}

void FirstPrint(void)
{
  Send(DATA, 0x4E); //N
  Send(DATA, 0x65); //e
  Send(DATA, 0x77); //w
  Send(DATA, 0x62); //b
  Send(DATA, 0x69); //i
  Send(DATA, 0x65); //e
  Send(DATA, 0x48); //H
  Send(DATA, 0x61); //a
  Send(DATA, 0x63); //c
  Send(DATA, 0x6B); //k
  Send(DATA, 0x2E); //.
  Send(DATA, 0x63); //c
  Send(DATA, 0x6F); //o
  Send(DATA, 0x6D); //m
  _delay_ms(1000);
  Send(COMMAND, 0x01);
  _delay_ms(1000);
}

void SecondPrint(void)
{
  SendString("_NewbieHack.com_");
  _delay_ms(1000);
  Send(COMMAND, 0x01);
  _delay_ms(1000);
}

void Position(void)
{
  for(int y = 1; y<=2; y++)
  {
    for(int x = 1;x<=16;x++)
    {
      itoa(x, positionString, 10);
      GoToLoc(10, 1);
      SendString("X = ");
      SendString(positionString);

      itoa(y, positionString, 10);
      GoToLoc(10, 2);
      SendString("Y = ");
      SendString(positionString);

      GoToLoc(x, y);
      SendString("x");

      _delay_ms(50);

      GoToLoc(x, y);
      SendString(" ");

      itoa(x, positionString, 10);
      GoToLoc(14, 1);
      SendString("   ");
      itoa(y, positionString, 10);
      GoToLoc(14, 2);
      SendString("   ");
    }
  }
  Send(COMMAND, 0x01);
  _delay_ms(1000);
}
