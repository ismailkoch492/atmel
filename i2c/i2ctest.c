#define F_CPU 16000000UL
#define SLA1 0x68 //MPU9250
#define SLA2 0x77 //BMP180-BMP280

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include "i2cMaster.h"

int main()
{
  while(1)
  {
      //to be completed
  }
}
