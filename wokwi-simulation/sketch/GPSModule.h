#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include <Arduino.h>
#include <TinyGPS++.h>

// Use default UART0 pins
#define GPS_BAUDRATE 9600

extern TinyGPSPlus gps;

void initGPS();
bool readGPSData();
void checkGPSWiring();

#endif
