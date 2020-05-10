#define F_CPU 16000000UL
#define SLA1 0x68 //MPU9250
#define SLA2 0x77 //BMP180-BMP280

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdlib.h>
#include "i2cMaster.h"
#include "mpu9250.h"

int main()
{
  int accelData[3];
  int gyroData[3];
  int tempData[1];
  int magData[3];

  while(1)
  {
      accelData = getAccelData();
      gyroData = getGyroData();
      tempData = getTempData();
      magData = getMagData();
  }
}
