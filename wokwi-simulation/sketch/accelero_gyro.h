#ifndef ACCELERO_GYRO_H
#define ACCELERO_GYRO_H

#include <Wire.h>

void setupAccelGyro();
void readAccelGyro(float &ax, float &ay, float &az, float &gx, float &gy, float &gz);
void updateAccelGyro();   // this will read and print inside the cpp

#endif
