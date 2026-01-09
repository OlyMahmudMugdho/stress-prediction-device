#ifndef PULSE_SENSOR_H
#define PULSE_SENSOR_H

// Declare the ADC pin number as an external constant.
// The main file only needs to know this constant exists.
extern const int PulsePin;

// Function declarations for sensor initialization and pure reading
void setupPulseSensor(); 
int readRawPulseValue();

#endif // PULSE_SENSOR_H