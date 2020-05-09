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
  int accelData[6];
  int gyroData[6];
  int magData[6];

  while(1)
  {
      accelData[0] = SingleMRST(SLA1, ACCEL_XOUT_H);
      gyroData[0] = SingleMRST(SLA1, GYRO_XOUT_H);
      magData[0] = SingleMRST(SLA1, HXL);
  }
}
