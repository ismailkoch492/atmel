#include <avr/io.h>
#include <util/delay.h>

#define LcdData PORTC
#define LcdDataDir DDRC
#define LcdCont PORTD
#define LcdContDir DDRD
#define Enable 5
#define ReadWrite 7
#define RegisterSelect 2
#define DATA (1==1)
#define CONTROL (!DATA)

#define Clear 0x01
#define ReturnHome 0x02
#define FourBit_TwoLine_FiveEightDot 0x28
#define EightBit_TwoLine_FiveEightDot 0x38
#define DisplayOn_CursorBlink_CursorOff 0x0E

void CheckIfBusy(void);
void EnableToggle(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);
void Send_A_String(char *string);
void Send(int mode, unsigned char value);

int main(void){
LcdContDir |= 1<<Enable | 1<<ReadWrite | 1<<RegisterSelect;
_delay_ms(15);
Send(CONTROL, Clear);
_delay_ms(2);
Send(CONTROL, EightBit_TwoLine_FiveEightDot);
_delay_us(50);
Send(CONTROL, DisplayOn_CursorBlink_CursorOff);
_delay_us(50);
/*
Send_A_Character(0x4E); //N
Send_A_Character(0x65); //e
Send_A_Character(0x77); //w
Send_A_Character(0x62); //b
Send_A_Character(0x69); //i
Send_A_Character(0x65); //e
Send_A_Character(0x48); //H
Send_A_Character(0x61); //a
Send_A_Character(0x63); //c
Send_A_Character(0x6B); //k
Send_A_Character(0x2E); //.
Send_A_Character(0x63); //c
Send_A_Character(0x6F); //o
Send_A_Character(0x6D); //m
*/
Send(DATA, 0x4E); //N
Send(DATA, 'e');
Send(DATA, 'w');
Send(DATA, 'b');
Send(DATA, 'i');
Send(DATA, 'e');
Send(DATA, 'H');
Send(DATA, 'a');
Send(DATA, 'c');
Send(DATA, 'k');
Send(DATA, '.');
Send(DATA, 'c');
Send(DATA, 'o');
Send(DATA, 'm');
Send_A_String("Patrick");
while(1){}}

void CheckIfBusy(){
LcdDataDir = 0;
LcdCont |= 1<<ReadWrite;
LcdCont &= ~1<<RegisterSelect;

while (LcdData >= 0x80){EnableToggle();}
LcdDataDir = 0xFF;} //0xFF means 0b11111111

void EnableToggle(){
LcdCont |= 1<<Enable;
asm volatile ("nop");
asm volatile ("nop");
LcdCont &= ~1<<Enable;}

void Send(int mode, unsigned char value)
{
  CheckIfBusy();
  LcdData = value;
  LcdCont &= ~ (1<<ReadWrite);
  if (DATA) {
    LcdCont |= 1<<RegisterSelect;
  } else {
    LcdCont &= ~ (1<<RegisterSelect);
  }
  EnableToggle();
  LcdData = 0;
}

void Send_A_String(char *String){}
/*
void Send_A_Command(unsigned char command){
CheckIfBusy();
LcdData = command;
LcdCont &= ~ ((1<<ReadWrite)|(1<<RegisterSelect));
EnableToggle();
LcdData = 0;}

void Send_A_Character(unsigned char character){
CheckIfBusy();
LcdData = character;
LcdCont &= ~ (1<<ReadWrite);
LcdCont |= 1<<RegisterSelect;
EnableToggle();
LcdData = 0;}
*/
