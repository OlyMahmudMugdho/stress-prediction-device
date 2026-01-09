// ThermometerSensor.h

#ifndef THERMOMETERSENSOR_H
#define THERMOMETERSENSOR_H

#include <Wire.h> 
#include <Adafruit_MLX90614.h> 

// Function Prototypes
void setupThermometerSensor(); 
float readObjectTemperature(); 
float readAmbientTemperature();

#endif // THERMOMETERSENSOR_H