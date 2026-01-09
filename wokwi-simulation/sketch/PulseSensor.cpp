#include "Arduino.h"
#include "PulseSensor.h"

// Define the ADC pin number here (implementation)
const int PulsePin = 34; // ADC pin on the microcontroller

// Function to set up the sensor pin
void setupPulseSensor() {
  pinMode(PulsePin, INPUT);
}

// Function to read the raw sensor value (pure hardware interaction)
int readRawPulseValue() {
  return analogRead(PulsePin);
}