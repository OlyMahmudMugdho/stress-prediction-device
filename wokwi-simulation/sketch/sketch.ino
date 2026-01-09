#include "PulseSensor.h"
#include "ThermometerSensor.h"
#include "GPSModule.h"
#include "Helper.h"
#include "dht22.h"
#include "accelero_gyro.h"


void setup() {
  Serial.begin(9600);  // MUST match GPS baud

  setupPulseSensor();
  setupThermometerSensor();
  initGPS();
  setupDHT22();
  setupAccelGyro();


  Serial.println("All modules initialized.");
}

void loop() {
  // GPS must run first and fast
  readGPSData();
  checkGPSWiring();

  displayPulse();
  displayThermometerValues();

  readDHT22();
  displayDHT22();

  updateAccelGyro();


  delay(100); // keep small
}
