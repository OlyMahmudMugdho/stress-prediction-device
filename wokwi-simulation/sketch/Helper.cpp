// Helper.cpp

#include "Helper.h"
#include "ThermometerSensor.h" // Need to include this to access read functions
#include "PulseSensor.h"


// Function to read the data and print it to the Serial Monitor
void displayThermometerValues() {
  // 1. Get the data using the ThermometerSensor module
  float objectTempC = readObjectTemperature(); 
  float ambientTempC = readAmbientTemperature();
  
  // 2. Handle the output (Printing)
  Serial.println("--- Temperature Reading ---");
  Serial.print("Object (Target) Temperature: ");
  Serial.print(objectTempC);
  Serial.println(" °C");
  
  Serial.print("Ambient Temperature: ");
  Serial.print(ambientTempC);
  Serial.println(" °C");
  Serial.println("---------------------------");
}

void displayPulse() {
  // Get the raw data from the modular file
  int rawValue = readRawPulseValue(); 
  
  // Handle the output (I/O) in the main file
  Serial.println(rawValue);
}