// ThermometerSensor.cpp

#include "ThermometerSensor.h"

// Create the sensor object globally in the source file
// The I2C address is usually 0x5A for the MLX90614
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); 

// Function to initialize the MLX90614 sensor
void setupThermometerSensor() {
  // Initialize the I2C communication on ESP32 
  // (Assuming default pins: GPIO 21 SDA, 22 SCL for I2C)
  Wire.begin(21, 22); 

  // Attempt to connect to the sensor
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX90614 sensor. Check wiring.");
    // Halt execution if the sensor is not found
    while (1);
  }
}

// Function to read the object (target) temperature
float readObjectTemperature() {
  return mlx.readObjectTempC(); 
}

// Function to read the ambient (sensor environment) temperature
float readAmbientTemperature() {
  return mlx.readAmbientTempC(); 
}