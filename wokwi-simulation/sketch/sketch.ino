#include "PulseSensor.h"
#include "ThermometerSensor.h"
#include "GPSModule.h"
#include "Helper.h"

void setup() {
  Serial.begin(9600);  // MUST match GPS baud

  setupPulseSensor();
  setupThermometerSensor();
  initGPS();

  Serial.println("All modules initialized.");
}

void loop() {
  // GPS must run first and fast
  readGPSData();
  checkGPSWiring();

  displayPulse();
  displayThermometerValues();

  delay(100); // keep small
}